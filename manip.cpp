#include "manip.h"

/**
 * Redirect movement angle away from obstacles.
 * 
 * @param pose Measured LiDAR pose.
 * @param intentAngle Angle which the vehicle would prefer to follow.
 * @return Redirected angle, or intentAngle if there was no obstacle.
 */
float redirect(Pose pose, float intentAngle) {
    for (Shape s : pose) {
        if (s.minAngle < s.maxAngle && s.maxAngle > intentAngle && s.minAngle < intentAngle) {
            // s is obstructing intent.
            if (abs(s.maxAngle - intentAngle) < abs(s.minAngle - intentAngle))
                return s.maxAngle;
            return s.minAngle;
        } else if (s.minAngle > s.maxAngle && (s.maxAngle > intentAngle || s.minAngle < intentAngle)) {
            // Origin is on s and s is obstructing intent.
            if (abs(s.maxAngle - intentAngle) < abs(s.minAngle - M_TAU - intentAngle)) 
                return s.maxAngle;
            return s.minAngle;
        }
    }
    return intentAngle;
}

/**
 * Estimate movement vector between two poses based on movement of masses.
 * 
 * Ideally, the poses originated from two measurements taken back to back.
 * 
 * @param pose1 Older pose.
 * @param pose2 Younger pose.
 * @return Estimated vector. 
 */
Vector estimateMovement(Pose pose1, Pose pose2) {
    Cloud massCloud1, massCloud2;
    for (Shape s : pose1) massCloud1.push_back(s.mass);
    for (Shape s : pose2) massCloud2.push_back(s.mass);
    return mass(massCloud1) - mass(massCloud2);
}

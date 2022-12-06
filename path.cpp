#include "path.h"


float leastIntrusiveRedirect(std::list<Shape> scape, float intentAngle) {
    for (Shape s : scape) {
        if (s.minAngle < s.maxAngle && s.maxAngle > intentAngle && s.minAngle < intentAngle) {
            // s is obstructing intent.
            if (abs(s.maxAngle - intentAngle) < abs(s.minAngle - intentAngle))
                return s.maxAngle;
            return s.minAngle;
        } else if (s.minAngle > s.maxAngle && (s.maxAngle > intentAngle || s.minAngle < intentAngle)) {
            if (abs(s.maxAngle - intentAngle) < abs(s.minAngle - M_TAU - intentAngle)) 
                return s.maxAngle;
            return s.minAngle;
        }
    }
    return intentAngle;
}

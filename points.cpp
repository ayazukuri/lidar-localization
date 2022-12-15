#include "points.h"
#include <math.h>
#include <stdio.h>

/**
 * Convert from polar to cartesian system.
 * 
 * @param p Point in polar system.
 * @return Point in cartesian system.
 */
Cartesian fromPolar(Polar p) {
    return {
        cos(p.a) * p.r,
        sin(p.a) * p.r
    };
}


/**
 * Calculate square amount of a vector. Avoids root (slow).
 * 
 * @param p Vector.
 * @return |p|^2
 */
float squareAmount(Vector p) {
    return pow(p.x, 2) + pow(p.y, 2);
}

/**
 * Calculate amount of a vector.
 * 
 * @param p Vector.
 * @return |p|
 */
float amount(Vector p) {
    return sqrt(squareAmount(p));
}

/**
 * Calculate squared distance between two points. Avoids root (slow).
 * 
 * @param p1 Point 1.
 * @param p2 Point 2.
 * @return Square distance between point 1 and point 2.
 */
float squareDistance(Cartesian p1, Cartesian p2) {
    return squareAmount(p2 - p1);
}

/**
 * Calculate distance between two points.
 * 
 * @param p1 Point 1.
 * @param p2 Point 2.
 * @return Distance between point 1 and point 2.
 */
float distance(Cartesian p1, Cartesian p2) {
    return amount(p2 - p1);
}

/**
 * Calculate mass point of a cloud.
 * 
 * @param c Point cloud.
 * @return Mass.
 */
Cartesian mass(Cloud c) {
    Cartesian m = { 0, 0 };
    for (Cartesian p : c) { 
        m = m + p;
    }
    m = m / c.size();
    return m;
}

/**
 * Rotate a point cloud around an angle.
 * 
 * @param c Point cloud.
 * @param a Rotation angle.
 * @return Rotated cloud.
 */
Cloud rotate(Cloud c, float a) {
    Cloud cr;
    for (Cartesian p : c) {
        cr.push_back(p ^ a);
    }
    return cr;
}

/**
 * Normalizes a given angle to between 0 and 2pi.
 * 
 * @param angle Input angle.
 * @return Normalized angle.
 */
float normalize(float angle) {
    return angle - floor(angle / M_TAU) * M_TAU;
}

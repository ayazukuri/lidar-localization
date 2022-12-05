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

std::list<Shape> broadScape(std::list<Shape> scape, float d) {
    std::list<Shape> newScape = {};
    for (Shape s : scape) {
        Shape newShape = {
            s.identifier,
            normalize(s.minAngle - asin(d / amount(s.c.front()))),
            normalize(s.maxAngle + asin(d / amount(s.c.back()))),
            s.rDist,
            s.lDist,
            s.mDist,
            s.mass,
            s.c
        };
        newScape.push_back(newShape);
    }
    return newScape;
}

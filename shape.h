#include "points.h"

struct Shape {
    int identifier;
    float lAngle;
    float rAngle;
    float mAngle;
    float lDistance;
    float rDistance;
    float mDistance;
    Cartesian mass;
    Cloud c;
};

std::list<Shape> shapes(std::list<Polar> measurement);

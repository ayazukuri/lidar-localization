#include "shape.h"

struct Correction {
    float angle;
    float deviation;
};

Correction correction(std::list<Shape> obstructions, float intentAngle);

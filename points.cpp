#include "points.h"
#include <math.h>
#include <stdio.h>

Cartesian fromPolar(Polar p) {
    return {
        cos(p.a) * p.r,
        sin(p.a) * p.r
    };
}

// Avoid root if not needed.
float squareAmount(Cartesian p) {
    return pow(p.x, 2) + pow(p.y, 2);
}

float amount(Cartesian p) {
    return sqrt(squareAmount(p));
}

float squareDistance(Cartesian p1, Cartesian p2) {
    return squareAmount(p2 - p1);
}

float distance(Cartesian p1, Cartesian p2) {
    return amount(p2 - p1);
}

Cartesian mass(Cloud c) {
    Cartesian m = { 0, 0 };
    for (Cartesian p : c) { 
        m = m + p;
    }
    m = m / c.size();
    return m;
}

Cloud rotate(Cloud c, float a) {
    Cloud cr;
    for (Cartesian p : c) {
        cr.push_back(p ^ a);
    }
    return cr;
}

#include "points.h"
#include "math.h"

float amount(Cartesian p) {
    return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

float distance(Cartesian p1, Cartesian p2) {
    return amount(p2 - p1);
}

Cartesian mass(Cloud c) {
    Cartesian m;
    for (Cartesian p : c) {
        m = m + p;
    }
    m = m / c.size();
    return m;
}

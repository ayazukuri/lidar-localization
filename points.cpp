#include "points.h"
#include <math.h>

inline int sgn(float x) {
    return x < 0 ? -1 : 1;
}

float sinacos(float x) {
    return sqrt(1 - pow(x, 2));
}

Point fromCartesian(float x, float y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Point fromPolar(float r, float a) {
    Point p;
    p.x = cos(a) * r;
    p.y = sin(a) * r;
    return p;
}

float amount(Vector v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

float product(Vector v, Vector u) {
    return v.x * u.x + v.y * u.y;
}

float rotSimple(PointVector pv) {
    return pv.point.x * pv.vector.y - pv.point.y * pv.vector.x;
}

float rotLever(PointVector pv) {
    float pava = amount(pv.point) * amount(pv.vector);
    return sgn(rotSimple(pv)) * sinacos(product(pv.point, pv.vector) / pava) * pava;
}

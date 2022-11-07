#include "classification.h"
#include <math.h>
#include <stdio.h>

int main() {
    Cartesian p0 = { 1, 0 };
    Cartesian p1 = { 0, 1 };
    float angle = atan2(p0 & p1, p0 * p1);
    printf("%fpi\n", angle / M_PI);
    Cartesian p2 = p0 + p1;
    printf("%fx %fy\n", p2.x, p2.y);
    float r = p0 & p1;
    printf("%f\n", r);
    return 0;
}

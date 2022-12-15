#include "manip.h"
#include <math.h>
#include <stdio.h>

int main() {
    PCloud p = {
        { 1, 0 },
        { 1, 0.02 },
        { 1, 0.04 },
        { 1, 0.06 },
        { 1, 0.08 },
        { 1, 0.10 },
        { 1, 0.12 },
        { 1, 0.14 },
        { 1, 0.16 },
        { 1, M_TAU - 0.12 },
        { 1, M_TAU - 0.10 },
        { 1, M_TAU - 0.08 },
        { 1, M_TAU - 0.06 },
        { 1, M_TAU - 0.04 },
        { 1, M_TAU - 0.02 }
    };
    float angle = 0;
    Pose shapers = pose(p);
    printf("%iamount\n", shapers.size());
    for (Shape s : shapers) {
        printf("NEW SHAPE\n");
        printf("minAngle: %fpi\n", s.minAngle / M_PI);
        printf("maxAngle: %fpi\n", s.maxAngle / M_PI);
    }
    float c = redirect(shapers, angle);
    printf("Corrected Angle: %fpi\n", c / M_PI);
    // TODO: broaden angle
    printf("Corrected Angle + Broaden: %fpi\n", c / M_PI);
    return 0;
}

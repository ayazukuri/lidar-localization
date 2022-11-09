#include "classification.h"
#include <math.h>
#include <stdio.h>

int main() {
    Polar p0, p1, p2, p3;
    p0 = { 20, 0 };
    p1 = { 20, 0.01 };
    p2 = { 20, M_PI - 0.03 };
    p3 = { 20, M_PI };
    std::list<Polar> c = { p0, p1, p2, p3 };
    std::list<Shape> s = shapes(c);
    printf("%i\n", s.size());
    int k = 0;
    for (Shape a : s) {
        printf("Shape %i\n", k);
        for (Cartesian c : a.measure) {
            printf("%fx %fy\n", c.x, c.y);
        }
        k++;
    }
    return 0;
}

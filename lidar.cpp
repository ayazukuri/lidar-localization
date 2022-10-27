#include <iostream>
#include "points.h"
#include "icp.h"

int main() {
    Point p1, p2, p3, p4;
    BinNode l, r;
    r.p.x = 2;
    r.p.y = 0;
    l.p.x = -1;
    l.p.y = 0;
    l.left = nullptr;
    l.right = &r;
    r.left = nullptr;
    r.right = nullptr;
    Cloud c = {
        p3, p4
    };
    PointVectorField pvs = minDistVectors(l, c);
    printf("%f", rotLever(pvs.front()));
    return 0;
}
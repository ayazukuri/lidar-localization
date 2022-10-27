#include "points.h"
#include "icp.h"

Point mass(Cloud measurement) {
    int l = measurement.size();
    float sumX, sumY;
    sumX = 0;
    sumY = 0;
    for (Point p : measurement) {
        sumX += p.x;
        sumY += p.y;
    }
    Point m;
    m.x = sumX / l;
    m.y = sumY / l;
    return m;
}

PointVectorField minDistVectors(Tree map, Cloud measurement) {
    PointVectorField f;
    for (Point p : measurement) {
        int d = 0;
        BinNode* n = &map;
        while (n) {
            bool takeLeft = d == 0 ? n->p.x > p.x : n->p.y > p.y;
            n = takeLeft ? n->left : n->right;
            d = (d + 1) % 2;
        }
        PointVector distV;
        distV.vector.x = n->p.x - p.x;
        distV.vector.y = n->p.y - p.y;
        distV.point.x = p.x;
        distV.point.y = p.y;
        f.push_back(distV);
    }
    return f;
};

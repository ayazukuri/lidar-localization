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

Point closest(Tree root, Point p, bool x) {
    bool takeLeft = x ? p.x < root.p.x : p.y < root.p.y;
    BinNode* n = takeLeft ? root.left : root.right;
    if (n) {
        Point m = closest(*n, p, !x);
        return distance(p, m) < distance(p, root.p) ? m : root.p;
    }
    return root.p;
}

Point closest(Tree root, Point p) {
    return closest(root, p, true);
}

PointVectorField minDistVectors(Tree map, Cloud measurement) {
    PointVectorField f;
    for (Point p : measurement) {
        Point c = closest(map, p);
        PointVector distV;
        distV.vector.x = c.x - p.x;
        distV.vector.y = c.y - p.y;
        distV.point.x = p.x;
        distV.point.y = p.y;
        f.push_back(distV);
    }
    return f;
};

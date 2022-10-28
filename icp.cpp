#include <limits>
#include <tuple>
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

std::tuple<Point, float> closest(Tree root, Point p, bool x) {
    // Which direction is the point we are looking for relative to root?
    bool takeLeft = x ? p.x < root.p.x : p.y < root.p.y;
    BinNode* n = takeLeft ? root.left : root.right;
    if (!n) return std::make_tuple(root.p, squareDistance(root.p, p));
    std::tuple<Point, float> ntup = closest(*n, p, !x);
    float tb = std::get<1>(ntup);
    if (tb < squareDistance(p, root.p)) return ntup;
    BinNode* m = takeLeft ? root.right : root.left;
    std::tuple<Point, float> mtup = closest(*m, p, !x);
    float sb = std::get<1>(mtup);
    if (tb < sb) return ntup;
    return mtup;
}

Point closest(Tree root, Point p) {
    return std::get<0>(closest(root, p, true));
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

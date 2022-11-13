#include "shape.h"
#include <math.h>
#include <list>
#include <limits>

const int SAMPLES_PER_MEASUREMENT = 600;
const int DIST_TOLERANCE = 2;
const float squareRadiusFactor = pow(sin((2*M_PI) / SAMPLES_PER_MEASUREMENT) * DIST_TOLERANCE, 2);

std::list<Shape> shapes(std::list<Polar> measurement) {
    Polar lastp = measurement.front();
    Cartesian lastc = fromPolar(lastp);
    float a = lastp.a;
    std::list<Tuple<Cloud, PCloud>> cs = { { {}, {} } };
    for (Polar p : measurement) {
        Cartesian c = fromPolar(p);
        if (squareDistance(c, lastc) > pow(p.r, 2) * squareRadiusFactor) {
            // Start of new shape detected.
            cs.push_back({ {}, {} });
        }
        cs.back().fst.push_back(c);
        cs.back().snd.push_back(p);
        lastp = p;
        lastc = c;
    }
    Tuple<Cloud, PCloud> firstC = cs.front();
    Tuple<Cloud, PCloud> lastC = cs.back();
    // If first and last point are close enough, consider them part of the same shape (merge first and last shape).
    if (squareDistance(firstC.fst.front(), lastC.fst.back()) < pow(lastp.r, 2) * squareRadiusFactor) {
        // Add all elements of last shape in front of the first shape.
        firstC.fst.splice(firstC.fst.begin(), lastC.fst);
        firstC.snd.splice(firstC.snd.begin(), lastC.snd);
        // Remove last virtual shape.
        cs.pop_back();
    }
    std::list<Shape> res;
    int k = 0;
    for (Tuple<Cloud, PCloud> c : cs) {
        Cartesian m = mass(c.fst);
        float r = amount(m);
        res.push_back({
            k,
            c.snd.front().a,
            c.snd.back().a,
            acos(m.x / r),
            amount(c.fst.front()),
            amount(c.fst.back()),
            r,
            m,
            c.fst
        });
    }
    return res;
}

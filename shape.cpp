#include "shape.h"
#include <math.h>
#include <list>
#include <limits>
#include <stdio.h>

const int SAMPLES_PER_MEASUREMENT = 600;
const int DIST_TOLERANCE = 2;
const float SQUARE_R_FACTOR = pow(sin(M_TAU / SAMPLES_PER_MEASUREMENT) * DIST_TOLERANCE, 2);

Tuple<Cloud, PCloud> carPolSep(RawShape rs) {
    Cloud c;
    PCloud p;
    for (Tuple<Polar, Cartesian> pc : rs) {
        p.push_back(pc.fst);
        c.push_back(pc.snd);
    }
    return { c, p };
}

std::list<Shape> shapes(std::list<Polar> measurement) {
    Polar lastp = measurement.front();
    Cartesian lastc = fromPolar(lastp);
    std::list<RawShape> pcs = { {} };
    for (Polar p : measurement) {
        Cartesian c = fromPolar(p);
        if (squareDistance(c, lastc) > pow(p.r, 2) * SQUARE_R_FACTOR) {
            pcs.push_back({});
        }
        pcs.back().push_back({ p, c });
        lastp = p;
        lastc = c;
    }

    Cartesian firstP = pcs.front().front().snd;
    Cartesian lastP = pcs.back().back().snd;

    // If first and last point are close enough, consider them part of the same shape (merge first and last shape).
    if (squareDistance(firstP, lastP) < pow(lastp.r, 2) * SQUARE_R_FACTOR) {
        pcs.front().splice(pcs.front().begin(), pcs.back());
        // Remove last virtual shape.
        pcs.pop_back();
    }

    std::list<Shape> res;
    int k = 0;
    for (RawShape rawShape : pcs) {
        Tuple<Cloud, PCloud> sep = carPolSep(rawShape);
        Cartesian m = mass(sep.fst);
        float minAngle, maxAngle;
        res.push_back({
            k,
            sep.snd.front().a,
            sep.snd.back().a,
            amount(sep.fst.front()),
            amount(sep.fst.back()),
            amount(m),
            m,
            sep.fst
        });
    }
    return res;
}

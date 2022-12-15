#include "pose.h"
#include <math.h>
#include <list>
#include <limits>
#include <stdio.h>

const float HC_TOLERANCE_FACTOR = 2;

const int SAMPLES_PER_MEASUREMENT = 600;
const float SQUARE_R_FACTOR = pow(sin(M_TAU / SAMPLES_PER_MEASUREMENT) * HC_TOLERANCE_FACTOR, 2);

/**
 * Separate intermediate shapes for processing.
 * 
 * @param rs Raw shape used in pose calculation.
 * @return Cloud contained in shape in polar and cartesian systems.
 */
Tuple<Cloud, PCloud> carPolSep(RawShape rs) {
    Cloud c;
    PCloud p;
    for (Tuple<Polar, Cartesian> pc : rs) {
        p.push_back(pc.fst);
        c.push_back(pc.snd);
    }
    return { c, p };
}

/**
 * Calculate pose from LiDAR measurement.
 * 
 * @param measurement LiDAR measurement.
 * @return Calculated pose.
 */
Pose pose(PCloud measurement) {
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

    Pose res;
    int k = 0;
    for (RawShape rawShape : pcs) {
        Tuple<Cloud, PCloud> sep = carPolSep(rawShape);
        Cartesian m = mass(sep.fst);
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

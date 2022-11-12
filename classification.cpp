#include "classification.h"
#include <math.h>
#include <list>

const int SAMPLES_PER_MEASUREMENT = 600;
const int DIST_TOLERANCE = 2;
const float squareRadiusFactor = pow(sin((2*M_PI) / SAMPLES_PER_MEASUREMENT) * DIST_TOLERANCE, 2);

std::list<Shape> shapes(std::list<Polar> measurement) {
    Polar lastp = measurement.front();
    Cartesian lastc = fromPolar(lastp);
    float a = lastp.a;
    std::list<Tuple<Cloud, float>> cs = { { {}, a } };
    for (Polar p : measurement) {
        Cartesian c = fromPolar(p);
        if (squareDistance(c, lastc) > pow(p.r, 2) * squareRadiusFactor) {
            // Start of new shape detected.
            cs.push_back({ {}, p.a });
        }
        cs.back().fst.push_back(c);
        lastp = p;
        lastc = c;
    }
    Tuple<Cloud, float> firstC = cs.front();
    Tuple<Cloud, float> lastC = cs.back();
    // If first and last point are close enough, consider them part of the same shape (merge first and last shape).
    if (squareDistance(firstC.fst.front(), lastC.fst.back()) < pow(lastp.r, 2) * squareRadiusFactor) {
        // Add all elements of last shape in front of the first shape.
        firstC.fst.splice(firstC.fst.begin(), lastC.fst);
        // Adjust angle of first shape to angle of last, as last shape is now the front.
        firstC.snd = lastC.snd;
        // Remove last virtual shape.
        cs.pop_back();
    }
    std::list<Shape> res;
    for (Tuple<Cloud, float> t : cs)
        res.push_back(
            toShape(
                t.fst,
                t.snd
            )
        );
    return res;
}

Shape toShape(Cloud c, float angle) {
    // Rotate cloud t.fst back by its offset angle t.snd.
    c = rotate(c, -angle);

    Cartesian p0, pn;
    p0 = c.front();
    pn = c.back();
    Cartesian m = mass(c);
    float innerAngle = atan2(p0 & pn, p0 * pn);

    float minX, minY, maxX, maxY, dMassMax, dMassMean, dMassMin;
    minX = p0.x;
    minY = p0.y;
    maxX = p0.x;
    maxX = p0.y;
    
    for (Cartesian p : c) {
        if (p.x < minX) minX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.x > maxX) maxX = p.x;
        if (p.y > maxY) maxY = p.y;
        float dMass = distance(m, p);
        if (dMass < dMassMin) dMassMin = dMass;
        if (dMass > dMassMax) dMassMax = dMass;
        dMassMean += dMass;
    }
    dMassMean /= c.size();

    return {
        maxX - minX,
        maxY - minY,
        dMassMax,
        dMassMean,
        dMassMin,
        innerAngle,
        c,
        angle
    };
}

float likeness(ClassConfig conf, Shape s1, Shape s2) {
    float score = conf.alpha   * pow(s1.width - s2.width, 2)
                + conf.beta    * pow(s1.height - s2.height, 2)
                + conf.gamma   * pow(s1.dMassMax - s2.dMassMax, 2)
                + conf.delta   * pow(s1.dMassMean - s2.dMassMean, 2)
                + conf.epsilon * pow(s1.dMassMin - s2.dMassMin, 2)
                + conf.zeta    * pow(s1.innerAngle - s2.innerAngle, 2);
    return 1 / score;
}

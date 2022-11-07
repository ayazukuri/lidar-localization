#include "classification.h"
#include "math.h"

Shape toShape(Cloud c) {
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
        if (p.x < minX)      minX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.x > maxX)      maxX = p.x;
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
        innerAngle
    };
}

float likeness(ClassConfig conf, Shape s1, Shape s2) {
    float score = conf.alpha * pow(s1.width - s2.width, 2)
                + conf.beta  * pow(s1.height - s2.height, 2)
                + conf.gamma * pow(s1.dMassMax - s2.dMassMax, 2)
                + conf.delta * pow(s1.dMassMean - s2.dMassMean, 2)
                + conf.epsilon * pow(s1.dMassMin - s2.dMassMin, 2)
                + conf.zeta * pow(s1.innerAngle - s2.innerAngle, 2);
    return 1 / score;
}

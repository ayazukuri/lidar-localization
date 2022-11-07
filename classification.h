#include "points.h"

struct ClassConfig {
    float alpha;
    float beta;
    float gamma;
    float delta;
    float epsilon;
    float zeta;
};

struct Shape {
    float width;
    float height;
    float dMassMax;
    float dMassMean;
    float dMassMin;
    float innerAngle;
    Cloud measure;
};


Shape toShape(Cloud c);
float likeness(ClassConfig conf, Shape s1, Shape s2);

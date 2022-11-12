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
    float angle;
};

Shape toShape(Cloud c, float angle);
std::list<Shape> shapes(std::list<Polar> measurement);
float likeness(ClassConfig conf, Shape s1, Shape s2);

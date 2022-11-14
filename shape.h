#include "points.h"

struct Shape {
    int identifier;
    float minAngle;
    float maxAngle;
    float rDist;
    float lDist;
    float mDist;
    Cartesian mass;
    Cloud c;
};

std::list<Shape> shapes(std::list<Polar> measurement);
using RawShape = std::list<Tuple<Polar, Cartesian>>;
Tuple<Cloud, PCloud> carPolSep(RawShape rs);

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

using Pose = std::list<Shape>;
Pose pose(PCloud measurement);
using RawShape = std::list<Tuple<Polar, Cartesian>>;
Tuple<Cloud, PCloud> carPolSep(RawShape rs);

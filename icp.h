#include <tuple>

Point closest(Tree map, Point p);
std::tuple<Point, float> closest(Tree map, Point p, bool x);
Point mass(Cloud measurement);
PointVectorField minDistVectors(Tree map, Cloud measurement);

Vector massTranslation(Point m);
Vector minDistTranslation(PointVectorField minDistVs, float (*kernel)(float));

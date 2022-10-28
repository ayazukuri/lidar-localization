#include <list>

struct Point {
    float x;
    float y;
};

using Vector = Point;
using Cloud = std::list<Point>;
using VectorField = std::list<Vector>;

struct PointVector {
    Point point;
    Vector vector;
};

using PointVectorField = std::list<PointVector>;

struct BinNode {
    Point p;
    BinNode* left;
    BinNode* right;
};

using Tree = BinNode;

Point fromCartesian(float x, float y);
Point fromPolar(float r, float a);

float amount(Vector v);
float squaredAmount(Vector v);
float distance(Point p1, Point p2);
float squareDistance(Point p1, Point p2);
float product(Vector v, Vector u);

float rotSimple(PointVector pv);
float rotLever(PointVector pv);

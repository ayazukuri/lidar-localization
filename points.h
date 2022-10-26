#include <list>

struct Point {
    float x;
    float y;
};

struct PointVector {
    Point point;
    Vector vector;
};

struct BinNode {
    Point p;
    BinNode* left;
    BinNode* right;
};

typedef Point Vector;
typedef std::list<Point> Cloud;
typedef std::list<Vector> VectorField;
typedef std::list<PointVector> PointVectorField;
typedef BinNode Tree;

Point fromCartesian(float x, float y);
Point fromPolar(float r, float a);

float amount(Vector v);
float product(Vector v, Vector u);

float rotSimple(PointVector pv);
float rotLever(PointVector pv);

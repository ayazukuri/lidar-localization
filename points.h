#include <list>
#include <math.h>

struct Polar {
    float r;
    float a;
};

struct Cartesian {
    float x;
    float y;

    Cartesian operator+(const Cartesian &a) {
        return { x + a.x, y + a.y };
    }

    Cartesian operator-(const Cartesian &a) {
        return { x - a.x, y - a.y };
    }

    float operator*(const Cartesian &a) {
        return x * a.x + y * a.y;
    }

    // Cross product
    float operator&(const Cartesian &a) {
        return x * a.y - a.x * y;
    }

    // Rotation
    Cartesian operator^(const float &a) {
        return {
            x * cos(a) - y * sin(a),
            x * sin(a) + y * cos(a)
        };
    }

    Cartesian operator*(const float &s) {
        return { x * s, y * s };
    }

    Cartesian operator/(const float &s) {
        return { x / s, y / s };
    }
};

using Vector = Cartesian;
using Cloud = std::list<Cartesian>;

float amount(Cartesian p);
float distance(Cartesian p1, Cartesian p2);
Cartesian mass(Cloud c);

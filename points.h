#include <list>
#include <math.h>

const float M_TAU = 2 * M_PI;

template <typename T, typename Y>
struct Tuple {
    T fst;
    Y snd;
};

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
using PCloud = std::list<Polar>;

Cartesian fromPolar(Polar p);
float squareAmount(Cartesian p);
float amount(Cartesian p);
float squareDistance(Cartesian p1, Cartesian p2);
float distance(Cartesian p1, Cartesian p2);
Cartesian mass(Cloud c);
Cloud rotate(Cloud c, float a);
float normalize(float angle);

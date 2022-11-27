#ifndef TECHARENA_CHALLENGE_POINT_H
#define TECHARENA_CHALLENGE_POINT_H

#include "util.h"

struct Point {
    Point() : x(), y() {}
    Point(T x, T y) : x(x), y(y) {}

    T scalar(const Point &o) const {
        return x * o.x + y * o.y;
    }

    T pseudoVector(const Point &o) const {
        return x * o.y + y * o.x;
    }

    bool operator< (const Point & p) const {
        return x < p.x-EPS || abs(x-p.x) < EPS && y < p.y - EPS;
    }

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << point.x << ' ' << point.y;
        return os;
    }

    bool isNonInf() const {
        return !isinf(x) && !isinf(y);
    }

    T x, y;
};

#endif

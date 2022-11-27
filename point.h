#ifndef TECHARENA_CHALLENGE_POINT_H
#define TECHARENA_CHALLENGE_POINT_H

#include "bits/stdc++.h"

using namespace std;
using T = long double;

struct Point {
    Point() : x(), y() {}
    Point(T x, T y) : x(x), y(y) {}

    T scalar(const Point &o) const {
        return x * o.x + y * o.y;
    }

    T pseudoVector(const Point &o) const {
        return x * o.y + y * o.x;
    }

    T x, y;
};

#endif

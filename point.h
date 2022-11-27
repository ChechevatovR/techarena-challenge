#ifndef TECHARENA_CHALLENGE_POINT_H
#define TECHARENA_CHALLENGE_POINT_H

#include <ostream>
#include "bits/stdc++.h"

using namespace std;
using T = long double;
static const int EPS = 1e-6;

const T INF = numeric_limits<T>::infinity();

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

    T x, y;
};

#endif

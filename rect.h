#ifndef TECHARENA_CHALLENGE_RECT_H
#define TECHARENA_CHALLENGE_RECT_H

#include "point.h"

struct Rect {
    const Point a, b;

    Rect(const Point &a, const Point &b) : a(a), b(b) {}

    T area() const {
        return abs(a.x - b.x) * abs(a.y - b.y);
    }
};

#endif //TECHARENA_CHALLENGE_RECT_H

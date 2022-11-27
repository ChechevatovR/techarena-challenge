#ifndef TECHARENA_CHALLENGE_RECT_H
#define TECHARENA_CHALLENGE_RECT_H

#include "point.h"

struct rect {
    Point a, b;

    rect(const Point &a, const Point &b) : a(a), b(b) {}
};

#endif //TECHARENA_CHALLENGE_RECT_H

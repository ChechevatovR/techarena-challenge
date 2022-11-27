//
// Created by peton on 27.11.22.
//

#ifndef TECHARENA_CHALLENGE_LINE_H
#define TECHARENA_CHALLENGE_LINE_H

#include "point.h"

struct line {
    long double a, b, c;

    line(Point p, Point q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
    }
};


#endif //TECHARENA_CHALLENGE_LINE_H

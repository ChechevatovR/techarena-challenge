//
// Created by peton on 27.11.22.
//

#ifndef TECHARENA_CHALLENGE_LINE_H
#define TECHARENA_CHALLENGE_LINE_H

#include "point.h"

struct line {
    long double a, b, c;

    line() {}
    line (Point p, Point q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = - a * p.x - b * p.y;
        norm();
    }

    void norm() {
        double z = sqrt (a*a + b*b);
        if (abs(z) > EPS)
            a /= z,  b /= z,  c /= z;
    }

    double dist (Point p) const {
        return a * p.x + b * p.y + c;
    }
};


#endif //TECHARENA_CHALLENGE_LINE_H

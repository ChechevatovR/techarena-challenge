#ifndef TECHARENA_CHALLENGE_PILYGON_H
#define TECHARENA_CHALLENGE_PILYGON_H

#include "rect.h"

struct Polygon {
    int n;
    vector<Point> points;

    Polygon(istream &in, int n): n(n) {
        for (int _ = 0; _ < n; ++_) {
            T x, y;
            in >> x >> y;
            points.emplace_back(Point(x, y));
        }
    }

    vector<Polygon> cutX(T x);
    vector<Polygon> cutY(T y);

    vector<Rect> cover() {

    }
};

#endif //TECHARENA_CHALLENGE_PILYGON_H

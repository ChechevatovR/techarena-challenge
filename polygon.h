#ifndef TECHARENA_CHALLENGE_PILYGON_H
#define TECHARENA_CHALLENGE_PILYGON_H

#include "rect.h"

struct Polygon {
    int n;
    vector<Point> points;

    Polygon(): n{0}, points() {}

    Polygon(istream &in, int n): n(n) {
        for (int _ = 0; _ < n; ++_) {
            T x, y;
            in >> x >> y;
            points.emplace_back(Point(x, y));
        }
    }

    vector<Polygon> cutX(T x) const {
    }

    vector<Polygon> cutY(T y) const;

    Rect BB() const {
        T xMin = INF;
        T yMin = INF;
        T xMax = -INF;
        T yMax = -INF;

        for (const Point &p : points) {
            xMin = min(xMin, p.x);
            yMin = min(yMin, p.y);
            xMax = max(xMax, p.x);
            yMax = max(yMax, p.y);
        }
        return Rect(Point(xMin, yMin), Point(xMax, yMax));
    }

    vector<Rect> cover() const;
};

#endif //TECHARENA_CHALLENGE_PILYGON_H

#ifndef TECHARENA_CHALLENGE_PILYGON_H
#define TECHARENA_CHALLENGE_PILYGON_H

#include "rect.h"
#include "line.h"

int random(int max) {
    return rand() % max;
}

struct Polygon {
    int n;
    vector<Point> points;
    static const int EPS = 1e-6;

    Polygon() : n{0}, points() {}

    Polygon(istream &in, int n) : n(n) {
        for (int _ = 0; _ < n; ++_) {
            T x, y;
            in >> x >> y;
            points.emplace_back(Point(x, y));
        }
    }

    static long double det(double a, double b, double c, double d) {
        return a * d - b * c;
    }

    static bool betw(double l, double r, double x) {
        return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
    }

    static bool intersect_1d(double a, double b, double c, double d) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return max(a, c) <= min(b, d) + EPS;
    }

    static bool isIntersect(Point a, Point b, Point c, Point d) {
        Point left;
        Point right;
        if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
            return false;
        line m(a, b);
        line n(c, d);
        double zn = det(m.a, m.b, n.a, n.b);
        if (abs(zn) < EPS) {
            if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
                return false;
            if (b < a) swap(a, b);
            if (d < c) swap(c, d);
            left = max(a, c);
            right = min(b, d);
            return true;
        } else {
            left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
            left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
            return betw(a.x, b.x, left.x)
                   && betw(a.y, b.y, left.y)
                   && betw(c.x, d.x, left.x)
                   && betw(c.y, d.y, left.y);
        }
    }


    vector<Polygon> cut() const {
        int indA;
        int indB;

        while (true) {
            indA = random(n);
            indB = random(n);
            if (indA == 0 && indB == n - 1) continue;
            if (abs(indA - indB) <= 1) continue;

            Point A = points[indA];
            Point B = points[indB];

            bool goodEdge = true;
            for (int i = 0; i < n; i++) {
                Point X = points[i];
                Point Y = points[(i + 1) % n];
                if (isIntersect(A, B, X, Y)) {
                    goodEdge = false;
                    break;
                }
            }
            if (goodEdge) break;
        }
        Polygon a, b;

        for (int i = indA; i != indB; i = (i + 1) % n) {
            a.points.push_back(points[i]);
        }
        a.points.push_back(points[indB]);

        for (int i = indB; i != indA; i = (i + 1) % n) {
            b.points.push_back(points[i]);
        }
        b.points.push_back(points[indA]);

        a.n = a.points.size();
        b.n = b.points.size();

        vector<Polygon> res;
        res.push_back(a);
        res.push_back(b);
        return res;
    }

    vector<Polygon> cutY(T y) const;

    Rect BB() const {
        T xMin = INF;
        T yMin = INF;
        T xMax = -INF;
        T yMax = -INF;

        for (const Point &p: points) {
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

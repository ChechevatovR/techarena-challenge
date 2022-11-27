#ifndef TECHARENA_CHALLENGE_PILYGON_H
#define TECHARENA_CHALLENGE_PILYGON_H

#include "rect.h"
#include "line.h"

#define F first
#define S second

int random(int max) {
    return rand() % max;
}

struct Polygon {
    int n;
    vector<Point> points;

    Polygon() : n{0}, points() {}

    Polygon(istream &in, int n) : n(n) {
        for (int _ = 0; _ < n; ++_) {
            T x, y;
            in >> x >> y;
            points.emplace_back(Point(x, y));
        }
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

    pair<Polygon, Polygon> cutByEdge(int indA, int indB) const {
//        cerr << "Cutting" << '\n';
        pair<Polygon, Polygon> res;

        for (int i = indA; i != indB; i = (i + 1) % n) {
            res.F.points.push_back(points[i]);
        }
        res.F.points.push_back(points[indB]);
        res.F.n = res.F.points.size();

        for (int i = indB; i != indA; i = (i + 1) % n) {
            res.S.points.push_back(points[i]);
        }
        res.S.points.push_back(points[indA]);
        res.S.n = res.S.points.size();

        return res;
    }

    pair<int, int> findCutEdgeRandom() const {
//        cerr << "finding good edge" << '\n';
        int indA;
        int indB;

        while (true) {
            indA = random(n);
            indB = random(n);
            if (isNeighbourIndexes(indA, indB, n)) continue;

            Point A = points[indA];
            Point B = points[indB];

            bool goodEdge = true;
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                Point X = points[i];
                Point Y = points[j];
                if (i == indA || j == indA || i == indB || j == indB) continue;
                if (isIntersect(A, B, X, Y)) {
//                    cerr << "Edge " << A << ' ' << B << "   is bad because intersects with   " << X << ' ' << Y << '\n';
                    goodEdge = false;
                    break;
                }
            }
            if (goodEdge) {
                return {indA, indB};
            }
        }
    }

    pair<int, int> findBestEdge() {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isNeighbourIndexes(i, j, n)) continue;
            }
        }
    }

    vector<Polygon> cut() const {
        auto [indA, indB] = findCutEdgeRandom();
        auto res = cutByEdge(indA, indB);
        return vector<Polygon>({res.F, res.S});
    }

    Point intersectLines(Point a1, Point a2, Point b1, Point b2) {
        Point res;
        line m(a1, a2), n(b1, b2);
        long double zn = det(m.a, m.b, n.a, n.b);
        res.x = -det1(m.c, m.b, n.c, n.b) / zn;
        res.y = -det1(m.a, m.c, n.a, n.c) / zn;
        return res;
    }

    void addCutPoints(T x) {
        for (int i = 0; i < points.size(); i++) {
            Point a = points[i];
            Point b = points[(i + 1) % n];
            if ((a.x < x && b.x > x) || (a.x > x && b.x < x)) {
                Point inter = intersectLines(a, b, Point(x, 0), Point(x, 100));
                points.push_back(inter);
            }
        }
        n = points.size();
    }

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

    Rect BB(T left, T right) const {
        assert(left < right);
        T xMin = INF;
        T yMin = INF;
        T xMax = -INF;
        T yMax = -INF;

        for (const Point &p: points) {
            if (left - EPS <= p.x && p.x <= right + EPS) {
                xMin = min(xMin, p.x);
                yMin = min(yMin, p.y);
                xMax = max(xMax, p.x);
                yMax = max(yMax, p.y);
            }
        }
        return Rect(Point(xMin, yMin), Point(xMax, yMax));
    }

    vector<Rect> cover() const;
};

#endif //TECHARENA_CHALLENGE_PILYGON_H

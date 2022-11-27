#ifndef TECHARENA_CHALLENGE_PILYGON_H
#define TECHARENA_CHALLENGE_PILYGON_H

#include "rect.h"
#include "line.h"

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

    long double det (double a, double b, double c, double d) {
        return a * d - b * c;
    }

    Point intersect(Point a1, Point a2, Point b1, Point b2) {
        Point res;
        line m(a1, a2), n(b1, b2);
        long double zn = det(m.a, m.b, n.a, n.b);
        res.x = -det(m.c, m.b, n.c, n.b) / zn;
        res.y = -det(m.a, m.c, n.a, n.c) / zn;
        return res;
    }

    pair<vector<Polygon>, vector<Polygon>> cutX(T x) {
        vector<Polygon> ansl, ansr;
        Point first;
        Polygon cur;
        int start = 0;
        for (int i = 0; i++; i < n) {
            Point a = points[i];
            Point b = points[(i + 1) % n];
            if (a.x == b.x && a.x == x) continue;
            if (a.x <= x && b.x >= x) {
                start = (i + 1) % n;
                first = intersect(a, b, Point(x, 0), Point(x, 100));
                break;
            }
        }
        int cur_pologenie = 1;
        cur.points.push_back(first);
        for(int i = 0; i < n; i++) {
            int id = (i + start) % n;
            if(cur_pologenie == 0) {
                if(points[id].x <= x) {
                    cur.points.push_back(points[id]);
                } else {
                    Point inter = intersect(cur.points.back(), points[id], Point(x, 0), Point(x, 100));
                    cur.points.push_back(inter);
                    ansl.push_back(cur);
                    cur.points.clear();
                    cur.points.push_back(inter);
                    cur_pologenie = 1;
                }
            } else {
                if(points[id].x >= x) {
                    cur.points.push_back(points[id]);
                } else {
                    Point inter = intersect(cur.points.back(), points[id], Point(x, 0), Point(x, 100));
                    cur.points.push_back(inter);
                    ansr.push_back(cur);
                    cur.points.clear();
                    cur.points.push_back(inter);
                    cur_pologenie = 0;
                }
            }
        }
    }

    vector<Polygon> cutY(T y);

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

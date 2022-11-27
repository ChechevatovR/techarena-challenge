#include "bits/stdc++.h"

#include "point.h"
#include "polygon.h"
#include "rect.h"

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;
typedef long double ld;

static const int CUT_ITERS = 4; // O(2^CUT_ITERS)

#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define MT make_tuple
#define MP make_pair


T getCutX(const Polygon &p) {
    const Rect BB = p.BB();
    return (BB.b.x + BB.a.x) / 2;
}

T getCutY(const Polygon &p) {
    const Rect BB = p.BB();
    return (BB.b.y + BB.a.y) / 2;
}

ld get_ans(vector<Polygon> &x) {
    ld ans = 0;
    for (Polygon &cur: x) {
        Rect q = cur.BB();
        ans += abs(q.a.x - q.b.x) * abs(q.a.y - q.b.y);
    }
    return ans;
}

void solvePetya(ifstream &in, ostream &out) {
    int n;
    ld c1, c2;
    in >> n >> c1 >> c2;
    Polygon p(in, n);

    vector<Polygon> best_ans;
    ld cur_ans = 1e10;

    for (int i = 0; i < 10000; i++) {
        vector<Polygon> res = p.cut();
        ld cur_res = get_ans(res);
        if (cur_res < cur_ans) {
            cur_ans = cur_res;
            best_ans = res;
        }
    }

    assert(best_ans.size() <= 3000);
    out << setprecision(10) << fixed;
    out << best_ans.size() << '\n';
    for (const Polygon &p: best_ans) {
        out << p.BB() << '\n';
    }
}

void solveRoma(ifstream &in, ostream &out) {
    int n;
    ld c1, c2;
    in >> n >> c1 >> c2;
    Polygon p(in, n);

    Rect BB = p.BB();
    T startX = BB.a.x;
    T endX = BB.b.x;
    T lenX = BB.b.x - BB.a.x;

    cerr << BB <<'\n';

    int CUTS = 10;
    for (int i = 1; i < CUTS; i++) {
        T cutPoint = startX + (lenX / CUTS) * i;
        p.addCutPoints(cutPoint);
        cerr << cutPoint << '\n';
        cerr << p.points.size() << '\n';
    }

    vector<Rect> ans;
    for (int i = 0; i < CUTS; i++) {
        T left = startX + (lenX / CUTS) * i;
        T right = startX + (lenX / CUTS) * (i + 1);
        assert(left < right);
        assert(startX <= left);
        assert(right <= endX);
        Rect BB = p.BB(left, right);
        const T EPS_OUT = 1e-6;
        BB.a.x -= EPS_OUT;
        BB.b.x += EPS_OUT;
//        assert(BB.a.x <= left + EPS);
//        assert(BB.b.x >= right - EPS);
        if (BB.isNonInf()) {
            ans.PB(BB);
        } else {
            assert(false);
        }
    }

    assert(ans.size() <= 3000);
    out << setprecision(10) << fixed;
    out << ans.size() << '\n';
    for (const Rect &r : ans) {
        out << r << '\n';
    }
}


int main(int argc, char *argv[]) {
    cerr << argc << '\n';
    ifstream fin;
    ofstream fout;
    if (argc == 2) {
        cerr << std::filesystem::current_path() << '\n';
        string filename = argv[1];
        fin = ifstream(filename + ".txt");
        fout = ofstream(filename + ".out");
    } else {
        cerr << "Expected input filename as argument" << '\n';
        return -1;
    }
    solveRoma(fin, fout);
    return 0;
}

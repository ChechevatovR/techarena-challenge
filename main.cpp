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

void solve(ifstream &in, ostream &out) {
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
/*
void solve(ifstream &in, ostream &out) {
    int n;
    ld c1, c2;
    in >> n >> c1 >> c2;
    Polygon p(in, n);
    vector<Polygon> cutPrev;
    vector<Polygon> cutCur;

    cutPrev.PB(p);

    for (int _ = 0; _ < CUT_ITERS; _++) {
        cerr << "CUT ITER " << _ << '\n';
        for (const Polygon &p : cutPrev) {
            if (p.n <= 4) {
                cutCur.PB(p);
                continue;
            }
//            auto x = getCutX(p);
            const vector<Polygon> toInsert = p.cut();
            cutCur.insert(cutCur.end(), toInsert.begin(), toInsert.end());
        }
        swap(cutCur, cutPrev);
        if (cutPrev.size() > 3000) {
            swap(cutCur, cutPrev);
            break;
        }
    }

    assert(cutPrev.size() <= 3000);
    out << setprecision(10) << fixed;
    out << cutPrev.size() << '\n';
    for (const Polygon &p : cutPrev) {
        out << p.BB() << '\n';
    }
}
*/

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
    solve(fin, fout);
    return 0;
}

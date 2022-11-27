#include "bits/stdc++.h"

#include "point.h"
#include "polygon.h"
#include "rect.h"

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;
typedef long double ld;

static const int CUT_ITERS = 0; // O(2^CUT_ITERS)

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

void solve(ifstream &in, ostream &out) {
    int n;
    ld c1, c2;
    in >> n >> c1 >> c2;
    Polygon p(in, n);
    vector<Polygon> cutPrev;
    vector<Polygon> cutCur;

    cutPrev.PB(p);

    for (int _ = 0; _ < CUT_ITERS; _++) {
        for (const Polygon &p : cutPrev) {
            auto x = getCutX(p);
            const vector<Polygon> toInsert = p.cutX(x);
            cutCur.insert(cutCur.end(), toInsert.begin(), toInsert.end());
        }
        swap(cutCur, cutPrev);
        if (cutPrev.size() > 3000) {
            swap(cutCur, cutPrev);
            break;
        }
    }

    /*
    // Do not store output - just print it
    vector<Rect> ans;
    for (const Polygon &p : cutPrev) {
        ans.PB(p.BB());
    }
     */

    assert(cutPrev.size() <= 3000);
    out << setprecision(10) << fixed;
    out << cutPrev.size() << '\n';
    for (const Polygon &p : cutPrev) {
        out << p.BB() << '\n';
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
    solve(fin, fout);
    return 0;
}

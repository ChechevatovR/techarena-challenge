#include "bits/stdc++.h"

#include "point.h"
#include "polygon.h"
#include "rect.h"

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;
typedef long double ld;

#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define MT make_tuple
#define MP make_pair


void solve() {
    int n;
    ld c1, c2;
    cin >> n >> c1 >> c2;
    Polygon in(, n);
    vector<Rect> ans = get_covering(in);
    cout << rect_ans(ans) << '\n';
    for (Rect &x: ans) {
        cout << x.a.x << ' ' << x.a.y << ' ' << x.b.x << ' ' << x.b.y << '\n';
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
    int n;
    fin >> n;
    fout << n;
    return 0;
}

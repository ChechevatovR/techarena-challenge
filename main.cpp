#include "bits/stdc++.h"

#include "point.h"

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

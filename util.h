#ifndef TECHARENA_CHALLENGE_UTIL_H
#define TECHARENA_CHALLENGE_UTIL_H

#include "bits/stdc++.h"

using namespace std;
using T = long double;
const T EPS = 1e-6;

const T INF = numeric_limits<T>::infinity();

bool floatEq(T a, T b) {
    return abs(a - b) < EPS;
}

bool isNeighbourIndexes(int indA, int indB, int n) {
    if (indA == 0 && indB == n - 1) return true;
    if (abs(indA - indB) <= 1) return true;
    return false;
}

static long double det(double a, double b, double c, double d) {
    return a * d - b * c;
}

static bool betw(double l, double r, double x) {
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

long double det1(double a, double b, double c, double d) {
    return a * d - b * c;
}

static bool intersect_1d(double a, double b, double c, double d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

#endif //TECHARENA_CHALLENGE_UTIL_H

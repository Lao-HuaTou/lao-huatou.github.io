#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
struct Point {
    double x, y;
};
Point A, B, C, D;
double p, q, r;
double dist(Point p1, Point p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y - p2.y) * (p1.y - p2.y));
}
double dist2(Point E) {
    Point L = C, R = D;
    for (int i = 0; i < 100; ++i) {
        Point m1, m2;
        m1.x = L.x + (R.x - L.x) / 3.0;
        m1.y = L.y + (R.y - L.y) / 3.0;
        m2.x = R.x - (R.x - L.x) / 3.0;
        m2.y = R.y - (R.y - L.y) / 3.0;
        double t1 = dist(E, m1) / r + dist(m1, D) / q;
        double t2 = dist(E, m2) / r + dist(m2, D) / q;
        if (t1 < t2) R = m2;
        else L = m1;
    }
    return dist(E, L) / p + dist(L, D) / q;
}
int main() {
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y >> p >> q >> r;
    Point L = A, R = B;
    for (int i = 0; i < 100; ++i) {
        Point m1, m2;
        m1.x = L.x + (R.x - L.x) / 3.0;
        m1.y = L.y + (R.y - L.y) / 3.0;
        m2.x = R.x - (R.x - L.x) / 3.0;
        m2.y = R.y - (R.y - L.y) / 3.0;
        double t1 = dist(A, m1) / p + dist2(m1);
        double t2 = dist(A, m2) / p + dist2(m2);
        if (t1 < t2) R = m2;
        else L = m1;
    }
    printf("%.2f\n", dist(A, L) / p + dist2(L));
    return 0;
}
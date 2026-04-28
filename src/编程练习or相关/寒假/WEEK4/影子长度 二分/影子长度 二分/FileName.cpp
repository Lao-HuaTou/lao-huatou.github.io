#include<vector>
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
double cal(double H,double h,double d,double x) {
	return d + H - x - d * (H - h) / x;
}
int main()
{
	int T; cin >> T;
	while (T--) {
		double H, h, d;
		cin >> H >> h >> d;
		double l = d*(H-h)/H, r = d;
		double m1, m2;
		for (int kk = 0; kk < 100; kk++) {
			m1 = l + (r - l) / 3;
			m2 = r - (r - l) / 3;
			double cur1 = cal(H, h, d, m1), cur2 = cal(H, h, d, m2);
			if (cur1 <= cur2) l = m1;
			else r = m2;
		}
		printf("%.3lf\n", cal(H, h, d, l));
	}
	return 0;
}
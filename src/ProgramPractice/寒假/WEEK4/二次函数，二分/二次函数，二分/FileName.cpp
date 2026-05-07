#include<vector>
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
struct F {
	int a, b, c;
};
double cal(double x, int n, const vector<F>& f) {
	double back = -1e18;
	for (int i = 0; i < n; i++) {
		double val = f[i].a * x * x + f[i].b * x + f[i].c;
		if (val > back) back = val;
	}
	return back;
}
int main() {

	int T; cin >> T;
	while (T--)
	{
		double ans=1e10;
		int n; cin >> n;
		vector<F>f(n);
		for (int i = 0; i < n; i++)cin >> f[i].a >> f[i].b >> f[i].c;
		double l = 0, r = 1000;
		double m1, m2;
		for (int kk = 0; kk < 100; kk++) {
			m1 = l + (r - l) / 3;
			m2 = r - (r - l) / 3;
			double cur1 = cal(m1, n, f), cur2 = cal(m2, n, f);
			if (cur1 <= cur2) r = m2;
			else l = m1;
		}
		printf("%.4lf\n", cal(l,n,f));

	}
	return 0;
}
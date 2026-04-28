#include<iostream>
#include<numbers>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iomanip>
using namespace std;
const double PI = acos(-1);
double dot[100005][3];
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> dot[i][0] >> dot[i][1] >> dot[i][2];
	}
	vector<pair<double,double>>line;
	for (int i = 1; i <= n; i++) {
		double x = dot[i][0];
		double y = dot[i][1];
		double r = dot[i][2];
		double l = sqrt(x * x + y * y);
		double thi = atan2(y , x);
		double del = asin(r / l);
		double L = thi - del, R = thi + del;
		line.push_back({ L , R });
	}
	sort(line.begin(), line.end());
	double res = 0.0, now = 0.0;
	for (auto &[l,r]:line) {
		now = max(now, l);
		res += max(0.0, r - now);
		now = max(now, r);
	}
	double ans = (PI / 2 - res) / (PI / 2);
	cout << fixed << setprecision(3) << ans;
	return 0;

}
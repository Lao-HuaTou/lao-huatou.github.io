#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

double dp1[100005], dp2[1000005];
int n;
double a[1000005];
double ans;
int main() {
	cin >> n; for (int i = 0; i < n; i++)cin >> a[i];
	ans = a[0];
	dp1[0] = dp2[0] = a[0];
	for (int i = 1; i < n; i++) {
		double curmin = min(a[i], min(dp1[i - 1] * a[i], dp2[i - 1] * a[i]));
		double curmax = max(a[i], max(dp1[i - 1] * a[i], dp2[i - 1] * a[i]));
		dp1[i] = curmax;//max=curmax
		dp2[i] = curmin;//min=curmin
		ans = max(ans, dp1[i]);//ans,max
	}
	cout << ans;
	return 0;
}
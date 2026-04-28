#include "head.cpp"
using namespace std;
//递归
int day[N],cost[N];
int dur[3] = { 1,7,30 };
const int MAX = 2e9;

int f1(vector<int>day,  int i) {//已经到了第day[i]
	int ans = 1e9;
	if (i == day.size()) {
		return 0;
	}
	for (int k = 0,j=i; k < 3; k++) {
		while (j<day.size() && i + dur[k]>day[j]) {
			j++;
		}
		ans = min(ans, cost[k] + f1(day, j));
	}
	cout << ans;

}
int dp[N];
int f2(vector<int >day,int i) {
	vector<int>dp(day.size());
	if (i == day.size())return 0;
	if (dp[i] != MAX) {
		return dp[i];
	}
	int ans=MAX;
	for (int k = 0, j = i; k < 3; k++) {
		while (j<day.size() && i + dur[k]>day[j]) {
			j++;
		}
		ans = min(ans, cost[k] + f1(day, j));
	}
	dp[i] = ans;
	cout << ans;
}



int f3() {
	int n;
	for (int i = 0; i <= n; i++)dp[i] = 0;
	dp[n] = 0;
	for (int i = n - 1; i >= 0; i--) {
		for (int k = 0, j = i; k < 3; k++) {
			while (j<n && day[i] + dur[k]>day[j]) {
				j++;
			}
			dp[i] = min(dp[i], cost[k] + dp[j]);
		}

	}

	return dp[0];
}
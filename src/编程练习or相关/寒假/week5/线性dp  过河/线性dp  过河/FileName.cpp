#include<iostream>
#include<vector>
#include<deque>
#define int long long
using namespace std;
int n, m, k, d;
int getrow(vector<int>&ar) {
	vector<int>dp(m + 1, 0);
	deque<int>q;
	dp[1] = 1;
	q.push_back(1);
	for (int i = 2; i <= m; i++) {
		if (!q.empty() && i - q.front() > d + 1) {
			q.pop_front();
		}
		dp[i] = ar[i] + 1 + dp[q.front()];
		while (!q.empty() && dp[i] <= dp[q.back()]) {
			q.pop_back();
		}
		q.push_back(i);
	}
	return dp[m];
}
void solve() {
	cin >> n >> m >> k >> d;
	vector<int>row(n + 1, 0);
	vector<int>ar(m + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> ar[j];
		}
		row[i] = getrow(ar);
	}
	int tem = 0;
	for (int i = 1; i <= k; i++) tem += row[i];
	int ans = tem;
	for (int i = k + 1; i <= n; i++) {
		tem = tem - row[i - k] + row[i];
		ans = min(ans, tem);
	}
	cout << ans << endl;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin >> T;
	while (T--) {
		solve();
	}
}

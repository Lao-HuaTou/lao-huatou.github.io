#include<iostream>
#include<vector>
#include<algorithm>
typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7;
int n, m;
ll dp[2][55];

int main() {
	cin >> n >> m;
	int t = 0;
	dp[0][0] = dp[0][1] = 1;
	for (int c = 1; c <= n; c++,t^=1) {
		for (int r = 1; r <= m; r++) {
			dp[c][r] = 0;
			for (int k = 0; k < c; k++) {
				dp[c][r] = (dp[c][r] + dp[k][r - 1] * dp[c - k - 1][r - 1] % MOD) % MOD;
			}
		}
		
	}
	cout << dp[n][m];
	return 0;
}

int main() {
	cin >> n >> m;
	int* dp = new int[n+1];
	dp[0] = 1;
	for (int i = 1; i <= n; i++)dp[i] = 0;
	for (int c = 1; c <= m; c++) {
		for (int j = n; j >= 1; j--) {
			dp[j] = 0;
			for (int k = 0; k < j; k++) {
				dp[j] = (dp[j] + dp[k] * dp[j - k - 1] % MOD) % MOD;
			}
		}
	}
	cout << dp[n];
	return 0;
}

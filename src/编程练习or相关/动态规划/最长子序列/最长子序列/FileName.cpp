#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
string s, t;
int dp[1004][1004];

int main() {
	cin >> s >> t;
	int n = s.length(), m = t.length();
	for (int i = 0; i <= n; i++)dp[i][0] = 1;
	for (int i = 1; i <= m; i++) {//t
		for (int j = 1; j <= n; j++) {//s
			dp[j][i] = dp[j - 1][i];
			if (s[j - 1] == t[i - 1]) {
				dp[j][i] += dp[j - 1][i - 1];
			}
		}
	}
	//rabbbit rabbit
	//	1  0  0  0  0  0
	//	1  1  0  0  0  0
	//	1  1  1  0  0  0
	//	1  1  2  1  0  0
	//	1  1  3  3  0  0
	//	1  1  3  3  3  0
	//	1  1  3  3  3  3
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << dp[i][j] << "  ";
		}
		cout << endl;
	}
	return 0;
}
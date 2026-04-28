#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
int dp[2][5001];

//int main()
//{
//	string s; cin >> s;
//	int n = s.length();
//	int t = 0;
//	for (int i = n - 1; i >= 0; i--, t ^= 1) {
//		dp[t][i] = 1;
//		if (i + 1 < n)dp[t][i + 1] = s[i] == s[i + 1] ? 2 : 1;
//		for (int j = i + 2; j < n; j++) {
//			if (s[i] == s[j]) {
//				dp[t ^ 1][j] = 2 + dp[t][j - 1];
//			}
//			else {
//				dp[t ^ 1][j] = max(dp[t ^ 1][j - 1], dp[t][j]);
//			}
//		}
//	}
//	cout << dp[t][n - 1];
//	return 0;
//}
//

int main()
{
	string s; cin >> s;
	int n = s.length();
	int* d = new int[n];
	for (int l = n - 1, leftdown = 0, down; l >= 0; l--) {
		d[l] = 1;
		if (l + 1 < n) {
			leftdown = d[l+1];
			d[l + 1] = s[l] == s[l + 1] ? 2 : 1;
			for (int r = l + 2; r < n; r++) {
				down = d[r];
				if (s[r] == s[l]) {
					d[r] = 2 + leftdown;
				}
				else {
					d[r] = max(d[r - 1], d[r]);
				}
				leftdown = down;
			}
		}
	}
	cout << d[n - 1];
	return 0;
}
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;
string s, t;
int dp[35][35][35];

int main() {
	cin >> s >> t;
	int n = s.length();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j][1] = s[i] == t[j];;
		}
	}
	for (int len = 2; len <= n; len++) {
		for (int i = 0; i <= n - len ; i++) {
			for (int j = 0; j <= n - len ; j++) {
				int f = 0;
				for (int k = 1; k < len; k++) {
					if (dp[i][j][k] && dp[i + k][j + k][len - k]) {
						dp[i][j][len] = 1;
						f = 1;
						break;
					}
				
					if (dp[i][j+len-k][k] && dp[i+k][j][len-k]) {
						dp[i][j][k] = 1;
						break;
					}
				}

			}
		}
	}
	if (dp[0][0][n])cout << "true";
	else cout << "false";
	return 0;
}
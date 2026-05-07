#include<iostream>
#include<algorithm>
#include<string>
typedef long long ll;
using namespace std;
ll Mod = 100000000;
int dp[2][5001];
ll num[2][5001];
string s1, s2;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> s1 >> s2;
	int len1 = s1.length() - 1, len2 = s2.length() - 1;
	int ans = 0;
	ll cnt = 0;
	for (int i = 0; i <= len2; i++)num[0][i] = 1;
	num[1][0] = 1;
	int t = 0;
	for (int i = 1; i <= len1; i++, t ^= 1) {

		for (int j = 1; j <= len2; j++) {
			num[t ^ 1][j] = 0;
			if (s1[i - 1] == s2[j - 1])
			{
				dp[t ^ 1][j] = dp[t][j - 1] + 1;
				num[t ^ 1][j] += num[t][j - 1];
			}
			else
			{
				dp[t ^ 1][j] = max(dp[t][j], dp[t ^ 1][j - 1]);
			}

			if (dp[t ^ 1][j] == dp[t ^ 1][j - 1])
			{
				num[t ^ 1][j] += num[t ^ 1][j - 1];
			}
			if (dp[t ^ 1][j] == dp[t][j])
			{
				num[t ^ 1][j] += num[t][j];
			}
			if (s1[i - 1] != s2[j - 1] && dp[t ^ 1][j] == dp[t][j - 1])
			{
				num[t ^ 1][j] -= num[t][j - 1];
			}
			num[t ^ 1][j] = num[t ^ 1][j] % Mod;
			

		}
	}


	cout << dp[t][len2] << endl << (num[t][len2] + Mod) % Mod;
	return 0;
}



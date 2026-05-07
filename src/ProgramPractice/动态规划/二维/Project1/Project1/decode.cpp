#include "head.cpp"
string s;
int dp[N] = {MAX};
int f1(int i) {
	if (i == s.length()) {
		return 1;
	}
	if (dp[i] != MAX) return dp[i];
	int ans;
	if (s[i] == '0') {
		ans = 0;
	}
	else {
		ans = f1(i + 1);
		if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
			ans += f1(i + 2);
		}
	}
	dp[i] = ans;
	return ans;
}

int f2() {
	int n = s.length();
	dp[n] = 1;
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == '0') {
			dp[i] = 0;

		}
		else {
			dp[i] = dp[i + 1];
			if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
				dp[i] += dp[i+2];
			}
		}
	}
	return dp[0];

}


int nxt = 1, nxtnxt = 0;
int f3() {
	int n = s.length();
	for (int i = n - 1,cur; i >= 0; i--) {
		if (s[i] == '0') {
			cur = 0;
		}
		else {
			cur = nxt;
			if (i + 1 < s.length() && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
				cur += nxtnxt;
			}
		}
		nxtnxt = nxt;
		nxt = cur;
	}
	return nxt;
}
#include"head.cpp"
//解决 “环绕字符串中唯一的子字符串”（类似 LeetCode 467）
int f1() {
	string str;
	int n = str.length();
	vector<int>s(n);
	for (int i = 0; i < n; i++) {
		s[i] = str[i] - 'a';
	}
	int len = 1;
	int dp[26];
	dp[s[0]] = 1;
	for (int i = 1; i < n; i++) {
		int cur = s[i];
		int pre = s[i - 1];
		if ((pre == 25 && cur == 0) || pre + 1 == cur) {
			len++;
		}
		else len = 1;
		dp[cur] = max(dp[cur],len);
	}
	int ans = 0;
	for (int i = 0; i < 26; i++) {
		ans += dp[i];
	}
	return ans;

}
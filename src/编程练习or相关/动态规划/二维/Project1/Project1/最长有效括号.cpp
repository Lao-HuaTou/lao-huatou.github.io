#include "head.cpp"
int f1() {
    string s;
    cin >> s;
    int n = s.length();
    if (n == 0) return 0;

    vector<int> dp(n, 0); // 严格以 s[i] 结尾的最长有效括号
    int ans = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            // 找到与当前 ')' 匹配的潜在左括号位置
            int p = i - dp[i - 1] - 1;

            // 检查 p 是否合法，且 s[p] 是否真的是左括号
            if (p >= 0 && s[p] == '(') {
                // 基础长度：内部匹配长度 dp[i-1] + 当前这对 () 的长度 2
                dp[i] = dp[i - 1] + 2;

                // 关键：加上匹配成功的左括号“之前”的那个有效长度
                if (p - 1 >= 0) {
                    dp[i] += dp[p - 1];
                }
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}
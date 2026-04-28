#include"head.cpp"
int dp[N];
int n;

int f1() {
    dp[1] = 1; // 第一个丑数是 1
    int ia = 1, ib = 1, id = 1; // 指向 dp 数组的指针
    int a = 2, b = 3, d = 5;

    for (int i = 2; i <= n; i++) {
        // 1. 计算候选值：用之前的丑数乘以因子
        int next_a = a * dp[ia];
        int next_b = b * dp[ib];
        int next_d = d * dp[id];

        // 2. 取三者中的最小值作为下一个丑数
        int next_val = min(next_a, min(next_b, next_d));
        dp[i] = next_val;

        // 3. 关键：更新指针。这里用多个 if 而不是 else if，为了去重
        if (next_val == next_a) ia++;
        if (next_val == next_b) ib++;
        if (next_val == next_d) id++;
    }
    return dp[n];
}
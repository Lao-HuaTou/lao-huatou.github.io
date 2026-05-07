#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 盈利计划
 * n : 员工额度上限
 * minProfit : 利润额度下限
 * group : 项目人数
 * profit : 项目利润
 */

 // 方法 3：三维动态规划 (严格对应 Java 原版逻辑)
int profitableSchemes3(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    int m = group.size();
    int mod = 1000000007;
    // dp[i][r][s]
    // i : 当前处理到第几个工作
    // r : 剩余员工额度
    // s : 尚需达标的利润额度
    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, 0)));

    // 初始化：当工作耗尽 (i == m) 时
    // 只要利润已经达标 (s == 0)，无论剩下多少人，都算 1 种有效方案
    for (int r = 0; r <= n; r++) {
        dp[m][r][0] = 1;
    }

    // 从后往前遍历工作
    for (int i = m - 1; i >= 0; i--) {
        for (int r = 0; r <= n; r++) {
            for (int s = 0; s <= minProfit; s++) {
                // 可能性 1：不要当前工作
                long p1 = dp[i + 1][r][s];

                // 可能性 2：要当前工作
                long p2 = 0;
                if (group[i] <= r) {
                    // 核心：利润减到 0 以下统一看作 0（代表已达标）
                    p2 = dp[i + 1][r - group[i]][max(0, s - profit[i])];
                }

                dp[i][r][s] = (int)((p1 + p2) % mod);
            }
        }
    }
    return dp[0][n][minProfit];
}

// 方法 4：空间压缩版 (严格对应 Java 原版逻辑)
int profitableSchemes4(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    int mod = 1000000007;
    int m = group.size();

    // 压缩掉第一维 i，只剩 [员工][利润]
    vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));

    // 初始化边界：对应 i == m 的情况
    for (int r = 0; r <= n; r++) {
        dp[r][0] = 1;
    }

    // 遍历每一个工作
    for (int i = m - 1; i >= 0; i--) {
        // 0/1 背包空间压缩必须倒序遍历员工额度 r
        for (int r = n; r >= 0; r--) {
            // 遍历利润额度 s
            for (int s = minProfit; s >= 0; s--) {
                int p1 = dp[r][s];
                int p2 = 0;
                if (group[i] <= r) {
                    p2 = dp[r - group[i]][max(0, s - profit[i])];
                }
                dp[r][s] = (p1 + p2) % mod;
            }
        }
    }
    return dp[n][minProfit];
}
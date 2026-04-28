#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 全局变量记录当前字符串的 0 和 1
int curZeros, curOnes;

void getZerosOnes(const string& str) {
    curZeros = 0; curOnes = 0;
    for (char c : str) {
        if (c == '0') curZeros++;
        else curOnes++;
    }
}

// 方法 3：三维 DP (从后往前填表)
int findMaxForm3(vector<string>& strs, int m, int n) {
    int len = strs.size();
    // dp[i][z][o] 表示从第 i 个字符串开始到最后，在限量为 z 和 o 时的最大数量
    // 维度：[字符串数量 + 1][m + 1][n + 1]
    vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

    for (int i = len - 1; i >= 0; i--) {
        getZerosOnes(strs[i]);
        for (int z = 0; z <= m; z++) {
            for (int o = 0; o <= n; o++) {
                // 可能性 1：不要当前字符串
                int p1 = dp[i + 1][z][o];
                // 可能性 2：要当前字符串（前提是容量够）
                int p2 = 0;
                if (curZeros <= z && curOnes <= o) {
                    p2 = 1 + dp[i + 1][z - curZeros][o - curOnes];
                }
                dp[i][z][o] = max(p1, p2);
            }
        }
    }
    return dp[0][m][n];
}


// 方法 4：空间压缩 (二维 DP)
int findMaxForm4(vector<string>& strs, int m, int n) {
    // dp[z][o] 代表当前限量下的最优解
    // 初始全是 0
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (const string& s : strs) {
        getZerosOnes(s);

        // 【核心重点】：必须从大到小遍历 (Reverse Iteration)
        // 这样可以保证你在更新 dp[z][o] 时，用到的 [z - curZeros] 还是上一轮的结果
        // 从而保证每个字符串只被选取一次
        for (int z = m; z >= curZeros; z--) {
            for (int o = n; o >= curOnes; o--) {
                // 状态转移：max(保持现状, 选入当前字符串后+1)
                dp[z][o] = max(dp[z][o], 1 + dp[z - curZeros][o - curOnes]);
            }
        }
    }
    return dp[m][n];
}
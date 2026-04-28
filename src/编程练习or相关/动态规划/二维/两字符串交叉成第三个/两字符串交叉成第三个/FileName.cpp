#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成

// 方法1：标准动态规划
bool isInterleave1(string str1, string str2, string str3) {
    if (str1.length() + str2.length() != str3.length()) {
        return false;
    }
    int n = str1.length();
    int m = str2.length();

    // dp[i][j]: s1的前i个和s2的前j个，能否交错组成s3的前i+j个
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;

    // 初始化第一列：只用s1能否组成s3的前缀
    for (int i = 1; i <= n; i++) {
        if (str1[i - 1] != str3[i - 1]) break;
        dp[i][0] = true;
    }

    // 初始化第一行：只用s2能否组成s3的前缀
    for (int j = 1; j <= m; j++) {
        if (str2[j - 1] != str3[j - 1]) break;
        dp[0][j] = true;
    }

    // 填表
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 两种情况：
            // 1. s3的最后一个字符来自s1：s1[i-1] == s3[i+j-1] 且 前面的部分(dp[i-1][j])也是对的
            // 2. s3的最后一个字符来自s2：s2[j-1] == s3[i+j-1] 且 前面的部分(dp[i][j-1])也是对的
            dp[i][j] = (str1[i - 1] == str3[i + j - 1] && dp[i - 1][j]) ||
                (str2[j - 1] == str3[i + j - 1] && dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

// 方法2：空间压缩
bool isInterleave2(string str1, string str2, string str3) {
    if (str1.length() + str2.length() != str3.length()) {
        return false;
    }
    int n = str1.length();
    int m = str2.length();
    vector<bool> dp(m + 1, false);

    dp[0] = true;
    for (int j = 1; j <= m; j++) {
        if (str2[j - 1] != str3[j - 1]) break;
        dp[j] = true;
    }

    for (int i = 1; i <= n; i++) {
        // 更新这一行的第0列
        dp[0] = (str1[i - 1] == str3[i - 1] && dp[0]);
        for (int j = 1; j <= m; j++) {
            // dp[j] 在更新前代表 dp[i-1][j] (来自上方)
            // dp[j-1] 在更新后代表 dp[i][j-1] (来自左方)
            dp[j] = (str1[i - 1] == str3[i + j - 1] && dp[j]) ||
                (str2[j - 1] == str3[i + j - 1] && dp[j - 1]);
        }
    }
    return dp[m];
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// 编辑距离
// 给你两个单词 word1 和 word2
// 请返回将 word1 转换成 word2 所使用的最少代价
// 你可以对一个单词进行如下三种操作：
// 插入一个字符，代价a
// 删除一个字符，代价b
// 替换一个字符，代价c
// 测试链接 : https://leetcode.cn/problems/edit-distance/

// 原初尝试版
// a : str1中插入1个字符的代价
// b : str1中删除1个字符的代价
// c : str1中改变1个字符的代价
// 返回从str1转化成str2的最低代价
static int editDistance1(string str1, string str2, int a, int b, int c) {
    int n = str1.length();
    int m = str2.length();
    // dp[i][j] :
    // s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i * b;
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = j * a;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int p1 = INT_MAX;
            if (str1[i - 1] == str2[j - 1]) {
                p1 = dp[i - 1][j - 1];
            }
            int p2 = INT_MAX;
            if (str1[i - 1] != str2[j - 1]) {
                p2 = dp[i - 1][j - 1] + c;
            }
            int p3 = dp[i][j - 1] + a;
            int p4 = dp[i - 1][j] + b;
            dp[i][j] = min({ p1, p2, p3, p4 });
        }
    }
    return dp[n][m];
}

// 枚举小优化版
static int editDistance2(string str1, string str2, int a, int b, int c) {
    int n = str1.length();
    int m = str2.length();
    // dp[i][j] :
    // s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i * b;
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = j * a;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                // 插入、删除、替换三者取最小值
                dp[i][j] = min({ dp[i - 1][j] + b, dp[i][j - 1] + a, dp[i - 1][j - 1] + c });
            }
        }
    }
    return dp[n][m];
}

// 空间压缩版 (非常适合竞赛，节省内存)
static int editDistance3(string str1, string str2, int a, int b, int c) {
    int n = str1.length();
    int m = str2.length();
    vector<int> dp(m + 1);
    for (int j = 1; j <= m; j++) {
        dp[j] = j * a;
    }
    for (int i = 1; i <= n; i++) {
        int leftUp = (i - 1) * b; // 记录左上角的值
        dp[0] = i * b;
        for (int j = 1; j <= m; j++) {
            int backUp = dp[j]; // 备份当前位置，作为下一个位置的左上角
            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = leftUp;
            }
            else {
                dp[j] = min({ dp[j] + b, dp[j - 1] + a, leftUp + c });
            }
            leftUp = backUp;
        }
    }
    return dp[m];
}

// LeetCode 接口入口
int minDistance(string word1, string word2) {
    // 题目默认代价均为 1
    return editDistance3(word1, word2, 1, 1, 1);
}
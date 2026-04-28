#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 矩阵中和能被 K 整除的路径
 * 答案对 1000000007 取模
 */
class Code04_PathsDivisibleByK {
public:
    static const int mod = 1000000007;

    // 方法 1：纯递归版
    static int numberOfPaths1(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        return f1(grid, n, m, k, 0, 0, 0);
    }

    static int f1(vector<vector<int>>& grid, int n, int m, int k, int i, int j, int r) {
        if (i == n - 1 && j == m - 1) {
            return (grid[i][j] % k == r) ? 1 : 0;
        }
        // 后续需要凑出来的余数 need
        int need = (k + r - (grid[i][j] % k)) % k;
        int ans = 0;
        if (i + 1 < n) {
            ans = f1(grid, n, m, k, i + 1, j, need);
        }
        if (j + 1 < m) {
            ans = (ans + f1(grid, n, m, k, i, j + 1, need)) % mod;
        }
        return ans;
    }

    // 方法 2：记忆化搜索版
    static int numberOfPaths2(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        // dp[n][m][k] 初始化为 -1
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, -1)));
        return f2(grid, n, m, k, 0, 0, 0, dp);
    }

    static int f2(vector<vector<int>>& grid, int n, int m, int k, int i, int j, int r, vector<vector<vector<int>>>& dp) {
        if (i == n - 1 && j == m - 1) {
            return (grid[i][j] % k == r) ? 1 : 0;
        }
        if (dp[i][j][r] != -1) {
            return dp[i][j][r];
        }
        int need = (k + r - (grid[i][j] % k)) % k;
        int ans = 0;
        if (i + 1 < n) {
            ans = f2(grid, n, m, k, i + 1, j, need, dp);
        }
        if (j + 1 < m) {
            ans = (ans + f2(grid, n, m, k, i, j + 1, need, dp)) % mod;
        }
        dp[i][j][r] = ans;
        return ans;
    }

    // 方法 3：严格位置依赖的动态规划版
    static int numberOfPaths3(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        // dp[n][m][k]
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, 0)));

        // 终点位置初始化
        dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;

        // 填最后一步是向下的（最后一列）
        for (int i = n - 2; i >= 0; i--) {
            for (int r = 0; r < k; r++) {
                int need = (k + r - (grid[i][m - 1] % k)) % k;
                dp[i][m - 1][r] = dp[i + 1][m - 1][need];
            }
        }

        // 填最后一步是向右的（最后一行）
        for (int j = m - 2; j >= 0; j--) {
            for (int r = 0; r < k; r++) {
                int need = (k + r - (grid[n - 1][j] % k)) % k;
                dp[n - 1][j][r] = dp[n - 1][j + 1][need];
            }
        }

        // 填剩余网格
        for (int i = n - 2; i >= 0; i--) {
            for (int j = m - 2; j >= 0; j--) {
                for (int r = 0; r < k; r++) {
                    int need = (k + r - (grid[i][j] % k)) % k;
                    int ans = dp[i + 1][j][need];
                    ans = (ans + dp[i][j + 1][need]) % mod;
                    dp[i][j][r] = ans;
                }
            }
        }
        return dp[0][0][0];
    }
};
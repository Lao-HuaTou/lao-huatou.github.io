//#include<cstdio>
//#include<algorithm>
//using namespace std;
//int n, m;
//inline void read(int& x) {
//	x = 0; char c;
//	c = getchar();
//	while (c < '0' || c>'9')c = getchar();
//	while (c >= '0' || c <= '9') {
//		x = x * 10 + c - '0';
//		c = getchar();
//	}
//
//}
//int ar[25][45];
//int dp[25];//行 第一线的列 第二线的列
//int main() {
//	read(n), read(m);
//	int ans = 0;
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= m - 1 + i; j++) {
//			read(ar[i][j]);
//		}
//	}
//	for (int row = 1; row <= n; row++) {
//		int res = 0;
//		for (int i = 1; i <= m - 1 + row; i++) {
//			for (int j = i + 1; j <= m - 1 + row; j++) {
//				res = max(res, ar[row][i] + ar[row][j]);
//			}
//		}
//		dp[row] = dp[row - 1] + res;
//	}
//	printf("%d", dp[n]);
//	return 0;
//}





#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

// 静态分配，45 足够覆盖 m+n 的范围
int grid[25][45];
int dp[2][45][45];

inline void fast_read(int& x) {
    x = 0; int f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;

    // 初始化第一行
    memset(dp, -0x3f, sizeof(dp)); // 初始化为负无穷
    for (int j = 1; j <= m; ++j) fast_read(grid[1][j]);

    for (int j1 = 1; j1 <= m; ++j1) {
        for (int j2 = j1 + 1; j2 <= m; ++j2) {
            dp[1][j1][j2] = grid[1][j1] + grid[1][j2];
        }
    }

    // DP 过程
    for (int i = 2; i <= n; ++i) {
        int cur = i & 1;
        int pre = (i - 1) & 1;
        int row_w = m + i - 1;

        for (int j = 1; j <= row_w; ++j) fast_read(grid[i][j]);

        // 每一行重置当前层
        for (int j1 = 0; j1 <= row_w; ++j1)
            for (int j2 = 0; j2 <= row_w; ++j2)
                dp[cur][j1][j2] = -1e9;

        for (int j1 = 1; j1 <= row_w; ++j1) {
            for (int j2 = j1 + 1; j2 <= row_w; ++j2) {
                // 手动展开 4 种可能的来源 (j1, j1-1) x (j2, j2-1)
                int v1 = dp[pre][j1][j2];
                int v2 = dp[pre][j1 - 1][j2];
                int v3 = dp[pre][j1][j2 - 1];
                int v4 = dp[pre][j1 - 1][j2 - 1];

                int best_pre = max({ v1, v2, v3, v4 });
                if (best_pre > -1e8) { // 合法状态
                    dp[cur][j1][j2] = best_pre + grid[i][j1] + grid[i][j2];
                }
            }
        }
    }

    // 统计最后一行结果
    int ans = 0;
    int last_w = m + n - 1;
    for (int j1 = 1; j1 <= last_w; ++j1) {
        for (int j2 = j1 + 1; j2 <= last_w; ++j2) {
            ans = max(ans, dp[n & 1][j1][j2]);
        }
    }
    printf("%d\n", ans);

    return 0;
}
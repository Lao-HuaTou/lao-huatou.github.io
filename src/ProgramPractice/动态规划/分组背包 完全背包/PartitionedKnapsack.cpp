// 分组背包(模版)
// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1757

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 防溢出流派：统一使用 long long
#define int long long

// 全局静态化：避免指针分配开销与爆栈风险
const int MAXN = 1001;
const int MAXM = 1001;


struct Item {
    int v; // 体积
    int w; // 价值
    int g; // 组号
    bool operator<(const Item& o)const{
        return g < o.g;
    }
};

// 全局变量严格声明在所有自定义函数上方
Item arr[MAXN];
int dp[MAXM];
int dp1_table[MAXN][MAXM]; // 用于 compute1 的全局静态空间，防多组数据污染与爆栈
int m, n;

// 解法一：严格位置依赖的动态规划 
int compute1() {
    int teams = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[i - 1].g != arr[i].g) {
            teams++;
        }
    }

    // 多组数据防污染：手动重置当前需要用到的二维 DP 状态空间
    for (int i = 0; i <= teams; i++) {
        for (int j = 0; j <= m; j++) {
            dp1_table[i][j] = 0;
        }
    }

    for (int start = 1, end = 2, i = 1; start <= n; i++) {
        while (end <= n && arr[end].g == arr[start].g) {
            end++;
        }
        // start ... end-1 -> i组
        for (int j = 0; j <= m; j++) {
            dp1_table[i][j] = dp1_table[i - 1][j];
            for (int k = start; k < end; k++) {
                // k是组内的一个商品编号
                if (j - arr[k].v >= 0) {
                    dp1_table[i][j] = max(dp1_table[i][j], dp1_table[i - 1][j - arr[k].v] + arr[k].w);
                }
            }
        }
        // start去往下一组的第一个物品
        // 继续处理剩下的组
        start = end++;
    }
    return dp1_table[teams][m];
}


int compute2() {
    // 多组数据防污染：利用 std::fill 快速清空上一组残留数据
    fill(dp, dp + m + 1, 0);
    
    for (int start = 1, end = 2; start <= n;) {
        while (end <= n && arr[end].g == arr[start].g) {
            end++;
        }
        // start....end-1
        for (int j = m; j >= 0; j--) {
            for (int k = start; k < end; k++) {
                if (j - arr[k].v >= 0) {
                    dp[j] = max(dp[j], arr[k].w + dp[j - arr[k].v]);
                }
            }
        }
        start = end++;
    }
    return dp[m];
}

signed main() {
    // 极致 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> m >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> arr[i].v >> arr[i].w >> arr[i].g;
        }
        sort(arr + 1, arr + n + 1);
        cout << compute1() << "\n";
    }

    return 0;
}
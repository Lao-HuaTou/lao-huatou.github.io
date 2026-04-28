//lower_bound可以代替连续比大小 nb
#include <iostream>
using namespace std;

const int M = 1e5 + 5, INF = 1e9;
int a[M], f1[M], f2[M], g[M], len, ans = -INF;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    len = 0;
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(g + 1, g + len + 1, a[i]) - g;
        f1[i] = pos;
        g[pos] = a[i];
        len = max(len, pos);
    }
    len = 0;
    memset(g, 0, sizeof g);
    for (int i = n; i >= 1; i--) {
        int pos = lower_bound(g + 1, g + len + 1, a[i]) - g;
        f2[i] = pos;
        g[pos] = a[i];
        len = max(len, pos);
    }
    for (int i = 1; i <= n; i++) ans = max(ans, f1[i] + f2[i] - 1);
    cout << n - ans;
    return 0;
}













//dp法

using namespace std;

int n, ans = -1; // 定义变量
int a[1007]; // 定义身高数组
int dp1[1007]; // 最长上升子序列的dp数组
int dp2[1007]; // 最长下降子序列的dp数组

int main() {
    cin >> n; // 读入同学总数

    for (int i = 1; i <= n; i++) {
        cin >> a[i]; // 读入身高
    }

    // 求最长上升子序列长度
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) { // 如果满足递增要求就更新
                dp1[i] = max(dp1[i], dp1[j] + 1); // 判断拼接转移后长度是否更长
            }
        }
    }

    // 求最长下降子序列长度，我们可以反着找
    for (int i = n; i > 0; i--) {
        for (int j = n + 1; j > i; j--) {
            if (a[j] < a[i]) {
                dp2[i] = max(dp2[i], dp2[j] + 1); // 判断拼接转移后长度是否更长
            }
        }

        for (int i = 1; i <= n; i++) {
            ans = max(dp1[i] + dp2[i] - 1, ans); // 找符合要求的最长队形长度
        }
    }

    cout << n - ans; // 注意题目问的是出列人数

    return 0;
}

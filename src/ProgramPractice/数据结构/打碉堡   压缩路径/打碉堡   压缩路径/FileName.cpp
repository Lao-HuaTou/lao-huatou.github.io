#include<iostream>
#include <vector>

using namespace std;

const int MAXN = 2e6 + 5; // 多开几位防止 n+1 越界
int n, m;
int p[MAXN];

// 标准路径压缩 find 函数
int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

struct Node {
    int l, r;
} at[MAXN];

void solve() {
    int dead = 0;
    if (!(cin >> n >> m)) return;

    // 初始化并查集，注意要初始化到 n + 1
    // p[i] 表示 i 后面第一个（包含i自己）还没被“杀掉”的位置
    for (int i = 1; i <= n + 1; i++) p[i] = i;

    for (int i = 1; i <= m; i++) {
        cin >> at[i].l >> at[i].r;
    }

    for (int i = 1; i <= m; i++) {
        int l = at[i].l;
        int r = at[i].r;

        // 核心逻辑：利用 find(l) 直接跳到左边界以后第一个活着的点
        for (int cur = find(l); cur <= r; cur = find(cur)) {
            dead++;
            // 将当前点指向下一个位置，相当于在逻辑上“删掉”了 cur
            p[cur] = find(cur + 1);
        }

        // 输出剩余人数
        cout << n - dead << (i == m ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
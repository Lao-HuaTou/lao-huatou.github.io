#include <iostream>
#include <algorithm>
using namespace std;

// 树上倍增 LCA - ACM 风格
// MAXN 为最大节点数，LIMIT 为倍增表最大深度 (2^19 > 500000)
const int MAXN = 500005;
const int LIMIT = 20;

int n, m, root_node, power;
int head[MAXN];
int nxt[MAXN << 1]; // 双向边，数组开两倍
int to[MAXN << 1];
int cnt;

int deep[MAXN];
int stjump[MAXN][LIMIT];

// 计算倍增最大步数
int log2_custom(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void build(int n) {
    power = log2_custom(n);
    cnt = 1;
    for (int i = 0; i <= n; i++) {
        head[i] = 0;
        deep[i] = 0;
    }
}

void addEdge(int u, int v) {
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt++;
}

// dfs递归版，C++可以稳过
void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        // 节点u向上跳2^p步 = 先跳2^(p-1)步，再跳2^(p-1)步
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e != 0; e = nxt[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
    }
}

int lca(int a, int b) {
    // 始终让 a 处于更深的一层
    if (deep[a] < deep[b]) {
        swap(a, b);
    }
    // 1. 先跳到同一高度
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    // 2. a和b一起向上跳，直到跳到LCA的下一层
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    // 返回他们的父节点即为LCA
    return stjump[a][0];
}

int main() {
    // 极致 I/O 优化，应对 5*10^5 数据量
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (!(cin >> n >> m >> root_node)) return 0;

    build(n);

    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }

    // 根节点的父亲设为 0，防止越界
    dfs(root_node, 0);

    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }

    return 0;
}
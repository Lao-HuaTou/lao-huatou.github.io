#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

// N 是点数，M 是边数
const int N = 1505, M = 50005;
const int INF = 0x3f3f3f3f;

// 链式前向星
int h[N], e[M], ne[M], w[M], idx;
int in[N];    // 入度
int dist[N];  // 最长路距离
int n, m;

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void topsort() {
    // 1. 初始化距离为极小值
    // 注意：如果是 long long，建议 memset 为 0xcf 或手动循环赋值
    for (int i = 1; i <= n; i++) dist[i] = -INF;

    // 2. 起点 1 的距离初始化为 0
    dist[1] = 0;

    queue<int> q;
    // 3. 将所有入度为 0 的点入队（不管是不是 1）
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];

            // 只有当起点 1 能够到达当前点 u 时，才更新后续节点 v
            // 否则 dist[u] 是 -INF，加了权值也是没意义的无效路径
            if (dist[u] != -INF) {
                if (dist[v] < dist[u] + w[i]) {
                    dist[v] = dist[u] + w[i];
                }
            }

            // 无论是否更新，入度都要减 1（这是拓扑排序的核心）
            if (--in[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    // 提高读入效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;

    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add(u, v, c);
        in[v]++; // 统计入度
    }

    topsort();

    // 如果 dist[n] 依然是 -INF，说明从 1 根本走不到 n
    if (dist[n] < -INF / 2) cout << -1 << endl;
    else cout << dist[n] << endl;

    return 0;
}
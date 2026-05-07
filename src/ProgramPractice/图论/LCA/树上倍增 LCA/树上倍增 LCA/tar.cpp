#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// tarjan算法解法 - ACM 风格
// MAXN 为最大节点数，注意边和查询都是双向存储，所以 Next/To 数组开两倍
const int MAXN = 500005;

// 链式前向星建图
int headEdge[MAXN];
int edgeNext[MAXN << 1];
int edgeTo[MAXN << 1];
int tcnt;

// 每个节点有哪些查询，也用链式前向星方式存储
int headQuery[MAXN];
int queryNext[MAXN << 1];
int queryTo[MAXN << 1];
// 问题的编号，一旦有答案可以知道填写在哪
int queryIndex[MAXN << 1];
int qcnt;

// 某个节点是否访问过
bool visited[MAXN];

// 并查集
int father[MAXN];

// 收集的答案
int ans[MAXN];

int n, m, root_node;

void build(int n) {
    tcnt = qcnt = 1;
    for (int i = 1; i <= n; i++) {
        headEdge[i] = 0;
        headQuery[i] = 0;
        visited[i] = false;
        father[i] = i;
    }
}

void addEdge(int u, int v) {
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    headEdge[u] = tcnt++;
}

void addQuery(int u, int v, int i) {
    queryNext[qcnt] = headQuery[u];
    queryTo[qcnt] = v;
    queryIndex[qcnt] = i;
    headQuery[u] = qcnt++;
}

// 并查集找头节点递归版
// 一般来说都这么写，但是本题附加的测试数据很毒
// java这么写就会因为递归太深而爆栈，C++这么写就能通过
int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// tarjan算法递归版
// 一般来说都这么写，但是本题附加的测试数据很毒
// java这么写就会因为递归太深而爆栈，C++这么写就能通过
void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = headEdge[u]; e != 0; e = edgeNext[e]) {
        int v = edgeTo[e];
        if (v != f) {
            tarjan(v, u);
            // 关键：子树处理完后，将子树根节点指向当前父节点
            father[v] = u;
        }
    }
    // 处理关于 u 的所有离线查询
    for (int e = headQuery[u]; e != 0; e = queryNext[e]) {
        int v = queryTo[e];
        if (visited[v]) {
            // 如果查询的另一个节点 v 已经访问过并回溯到了某个祖先
            // 那么 u 和 v 的 LCA 就是 v 在并查集中的代表元
            ans[queryIndex[e]] = find(v);
        }
    }
}

int main() {
    // 极致 I/O 优化
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

    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        addQuery(u, v, i);
        addQuery(v, u, i);
    }

    tarjan(root_node, 0);

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
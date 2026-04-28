#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define int long long
const int INF = 1e18;

signed main() {
    int n, m;
    cin >> n >> m;

    // 使用邻接表存储图
    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({ b, c });
        // 如果是无向图，加上下面这行：
        // graph[b].push_back({a, c});
    }

    // 从节点0开始
    vector<int> dist(n + 1, INF);
    dist[0] = 0;

    // 优先队列：存储(距离, 节点)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, 0 });

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // 如果这个距离已经不是最短的，跳过
        if (d > dist[u]) continue;

        // 遍历所有邻居
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }

    // 输出从0到1-n的最短距离
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            cout << -1 << endl;
        }
        else {
            cout << dist[i] << endl;
        }
    }

    return 0;
}
struct Edge {
    int to, nxt, w;
};
struct Node {
    int to, w;
    int dist;
    bool operator < (const Node& a)const {
        return w < a.w;
    }
};
vector<Edge>edge;
int cnt = 0;
int head[2005];
void add(int u, int v, int w) {
    edge[++cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}
int n, m;//dot edge
int vis[2005];
void dij() {
    cin >> n >> m;
    edge.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w);
    }
    priority_queue<Node>q;
    q.push({});
}


(1) : 求父子节点 :
    父(i) = > (i - 1) / 2;
左子(i) = > i * 2 + 1
右子(i) = > i * 2 + 2
大根上滤(i) {
    while (堆[i] > 堆[父(i)])
    {
        交换(i, 父(i));
        j = 父(i);
    }
}
// 注: 这里大根下滤使用递归方式
// 插入堆首
大根下滤(i) {
    j = i;
    if (左子(i) < 总 && 堆[左子(i)] > 堆[j])
    {
        j = 左子(i);
    }
    if (右子(i) < 总 && 堆[右子(i)] > 堆[j])
    {
        j = 右子(i);
    }
    if (i != j)
    {
        交换(i, j);
        大根下滤(j);
    }
}
(2 - 1) ﻿
04:49
自顶向下建堆法﻿
大根上滤建堆法::O(NlogN)
for (i) {
    上滤(i);
}
(2 - 2) ﻿
06:02
自下而上建堆法
﻿::O(N)
从倒数第二层开始大根下滤 :
    for (i = 父(总 - 1); i倒序)
    {
        下滤(i);
    }
(3)﻿
堆的具体应用
(3 - 1)应用1:
最小优先队列(个人已 : 常用于一些类贪心路径搜索算法的 * **优化, 如A * 算法, dj算法) :
    弹出最小元素() {
    output = 堆[0];
    堆[0] = 堆[总 - 1];
    下滤(0);
    return output;
}
插入(input) {
    堆[总] = input;
    上滤(总);
    总++;
}
(3 - 2)应用2: 堆排
堆排序
小根堆排升序(output数组) {
    j = 总 - 1;
    for (i)
    {
        output[i] = 堆[0];
        堆[0] = 堆[j];
        j--;
        下滤(0);
    }
}
优化堆排序 : 大根堆排序
大根堆排升序()::O(NlogN) {
    for (i = 总 - 1)
    {
        交换(0, i);
        总--;
        下滤(0);
    }
}



缩写备注:

for (i) = > for (i = 0; i < 总; i++)


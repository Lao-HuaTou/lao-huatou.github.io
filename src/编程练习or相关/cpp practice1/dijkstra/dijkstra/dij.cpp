#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 100005; // 点数
const int MAXM = 200005; // 边数（无向图开2倍）

// 链式前向星结构
int head[MAXN], cnt;
struct Edge {
    int to, weight, nxt;
} edge[MAXM];

void add(int u, int v, int w) {
    edge[++cnt].to = v;
    edge[cnt].weight = w;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}
int n, m;
int dis[MAXN] = {INF};
bool vis[MAXN] = { false };
void dij(int start) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>q;
    //按first来升序 得到小根堆
    //dis  dot
    q.push({ 0,start }); vis[start] = true;
    while (!q.empty()) {
        int cur = q.top().second;
        q.pop();
        vis[cur] = true;
        for (int i = head[cur]; i; i = edge[i].nxt) {
            
            
            int v = edge[i].to;
            int w = edge[i].weight;
            
            if (dis[cur] + w < dis[v]) {
                dis[v] = dis[cur] + w;
                q.push({ dis[v],v });
            }
        }
    }
}
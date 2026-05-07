#include<iostream>
#include<vector>
#include<queue>
#define int long long
using namespace std;
int n, m, s;
const int M = 1e6 + 10;
const int MM = 1e15;
struct Edge {
	int to, w, nxt;
}edge[M];
struct node {
	int id, dist;
	bool operator > (const node&b)const {
		return dist > b.dist;
	}
};
int cnt = 1;
int head[M];
void add(int u,int v,int w){
	edge[cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].nxt = head[u];
	head[u] = cnt++;
}
int dist[M];
bool visit[M]={false};
void dij() {
	// 1. 初始化：全设为无穷大，起点设为 0
	for (int i = 1; i <= n; i++) {
		dist[i] = MM;
	}
	dist[s] = 0;

	// 2. 优先队列：小根堆，存储 {点编号, 到起点的距离}
	priority_queue<node, vector<node>, greater<node>> q;
	//小根堆：最短的距离已经确定，就是最终结果，可用于计算其他点，非最短的距离会被更新，直到最终确定最短距离

	q.push({ s, 0 });

	while (!q.empty()) {
		// 3. 找最小：从堆顶取出当前距离最小的点
		node cur = q.top();
		q.pop();
		int u = cur.id;

		// 如果该点已经确定最短路，跳过
		if (visit[u]) continue;
		visit[u] = true;

		// 4. 松弛：通过点 u 尝试更新它的所有邻居 v
		for (int i = head[u]; i != 0; i = edge[i].nxt) {
			int v = edge[i].to;
			int w = edge[i].w;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				q.push({ v, dist[v] });
			}
		}
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> s;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c);
	}
	dij();
	for (int i = 1; i <= n; i++) {
		if(dist[i]!=MM)cout << dist[i] << " ";
		else cout << "-1 ";
	}
	return 0;
}
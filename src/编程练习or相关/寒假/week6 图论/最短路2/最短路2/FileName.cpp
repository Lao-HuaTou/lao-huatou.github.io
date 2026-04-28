#include<iostream>
#include<queue>
#define int long long
#include<vector>
using namespace std;
int n, m, s;
const int M = 3e5 + 10;
const int MM = 1e18;
struct Edge {
	int to, w, nxt;
}edge[M];
struct node {
	int id, dist;
	bool operator>(node& b)const {
		return dist > b.dist;
	}
};
int head[M], cnt=1;
void add(int u, int v, int w) {
	edge[cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].nxt = head[u];
	head[u] = cnt++;
}
int dist[M];
int upcnt[M];
bool enter[M] = { false };
void spfa() {
	for (int i = 1; i <= n; i++) {
		dist[i] = MM;
	}
	queue<int>q;
	q.push(s);
	dist[s] = 0;
	upcnt[s] = 1;
	enter[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		enter[u]=false;
		for (int i = head[u]; i != 0; i = edge[i].nxt) {
			int v = edge[i].to;
			int w = edge[i].w;
			if (dist[u] == -MM) {// 如果当前点已经是负无穷，直接传播给邻居
				if (dist[v] != -MM) {
					dist[v] = -MM;
					if (!enter[v]) { q.push(v); enter[v] = true; }
				}
				continue;
			}
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!enter[v]) {
					upcnt[v]++;
					q.push(v);
					enter[v] = true;
					if (upcnt[v] >= n) dist[v] = -MM;
				}
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
		int a, b, c; cin >> a >> b >> c;
		add(a, b, c);
	}
	spfa();
	for (int i = 1; i <= n; i++) {
		if (dist[i] == MM) cout << "N/A ";
		else if (dist[i] == -MM) cout << "-inf ";
		else cout << dist[i] << " ";
	}
	return 0;
}
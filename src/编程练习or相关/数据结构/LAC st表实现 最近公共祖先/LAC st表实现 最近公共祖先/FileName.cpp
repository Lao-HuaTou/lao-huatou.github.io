#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int lg[500005];
int dn;//时间戳
int dfn[500005];//dfs时每个点的先后顺序
vector<int>adj[500005];//无向图
int st[19][500005];//记录区间内最浅的时间戳
int n, m, r;
int get(int u, int v) {//该算法中，dfn最少说明深度最浅
	return dfn[u] < dfn[v] ? u : v;
}
void dfs(int x, int f) {//x is cur node       f is the father node
	st[0][dfn[x] = ++dn] = f;// init the st and dfn 记录父亲
	for (auto id : adj[x]) {
		if (id != f) {//无向边，防走回头路
			dfs(id, x);
		}

	}

}
int lca(int u, int v) {
	if (u == v)return u;
	if ((u = dfn[u]) > (v = dfn[v]))swap(u, v);
	u++;
	int dis = v - u + 1;//要查询的时间戳范围内，并不存在lca 最浅的那个点是lca的一个亲儿子
	int g = lg[dis];
	return get(st[g][u], st[g][v - (1 << g) + 1]);
}
int main() {
	lg[1] = 0;

	cin >> n >> m >> r;
	for (int i = 2; i <= n; i++) {
		lg[i] = lg[i / 2] + 1;
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(r, 0);
	for (int i = 1; i < 19; i++) {
		for (int j = 1; j + (1 << i) - 1 <= n; j++) {
			st[i][j] = get(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		}
	}
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		cout << lca(u, v) << endl;
	}
	return 0;
}

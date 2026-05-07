#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
const int M = 1e5 + 10;
struct Edge {
	int to, nxt,adj;
}edge[M];
int ecnt = 1;
int head[M];
void add(int u,int v) {
	edge[ecnt].to = v;
	edge[ecnt].adj = u;
	edge[ecnt].nxt = head[u];
	head[u] = ecnt++;
}
int cnt[M];//cnt for father
int ans[M];
void solve() {
	ecnt = 1;
	for (int i = 0; i <= n + 1; i++) {
		head[i] = 0;
		cnt[i] = 0;
		ans[i] = 0;
	}
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		add(y, x); cnt[x]++;
		if (y == x) {
			cout << "Impossible!\n";
			return;
		}
	}
	int tot = 0;
	priority_queue<int>q;
	for (int i = 1; i <= n; i++) {
		if (!cnt[i])q.push(i);
	}
	while (!q.empty()) {
		int u = q.top(); q.pop(); tot++;
		ans[tot] = u;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			cnt[v]--;
			if (!cnt[v])q.push(v);
		}
	}
	if (tot < n)cout << "Impossible!\n";
		else {
		for (int i = n; i; i--) {
			cout << ans[i] << " ";
		}
		cout << "\n";
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
#include<algorithm>
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;
const int N = 2e5 + 5;
int n;
int deg[N];
int ans[N];
struct edge {
	int to,nxt;
}e[N];
int c, head[N];
void add(int u, int v) {
	e[++c] = {v,head[u]};
	head[u] = c;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(0);
	int T;cin >> T;
	while (T--) {
		c = 0;
		cin >> n;
		for (int i = 0;i <= n;i++) {
			deg[i] = 0;
			e[i] = { 0,0 };
			head[i] = -1;
		}

		int u, v, x, y;
		for (int i = 1;i < n;i++) {
			cin >> u >> v >> x >> y;
			if (x >= y) {
				deg[v]++;
				add(u, v);
			}
			else {
				deg[u]++;
				add(v, u);
			}
		}
		queue<int>q,q2;
		for (int i = 1;i <= n;i++) {
			if (deg[i] == 0)q.push(i);
		}
		int cnt = n;
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			ans[cur] = cnt--;
			for (int i = head[cur];i != -1;i = e[i].nxt) {
				int v = e[i].to;
				deg[v]--;
				if (deg[v] == 0) {
					q.push(v);
				}
			}
		}
		
		for (int i = 1;i <= n;i++) {
			cout << ans[i] << " ";
		}
		cout << endl;

	}
}

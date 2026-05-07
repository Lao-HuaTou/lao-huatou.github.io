#include<vector>
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
struct road {
	int b, e, t;
};
bool cmp(const road& x, const road& y) {
	return x.e < y.e;
}
int main() {
	int n, m; cin >> n >> m;
	vector<road>r(m);
	for (int i = 0; i < m; i++)cin >> r[i].b >> r[i].e >> r[i].t;
	sort(r.begin(), r.end(),cmp);
	int ans = 0;
	vector<bool>line(n + 1, false);
	for (int i = 0; i < m; i++) {
		int c = 0;
		for (int j = r[i].b; j <= r[i].e; j++) {
			if (line[j]) c++;
		}
		if (c < r[i].t) {
			int left = r[i].t - c;
			int tem = r[i].e;
			while (left > 0 && tem >= r[i].b) {
				if (!line[tem]) {
					line[tem] = true;
					left--;
					ans++;
				}
				tem--;
			}
		}
	}
	cout << ans;
	return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int tree[30005], n;

// 树状数组标准操作
void update(int i, int val) {
	for (; i <= n; i += i & -i) tree[i] += val;
}
int query(int i) {
	int sum = 0;
	for (; i > 0; i -= i & -i) sum += tree[i];
	return sum;
}

struct road { int b, e, t; };
bool cmp(const road& x, const road& y) { return x.e < y.e; }

int main() {
	int m; cin >> n >> m;
	vector<road> r(m);
	vector<bool> hasTree(n + 1, false);
	for (int i = 0; i < m; i++) cin >> r[i].b >> r[i].e >> r[i].t;
	sort(r.begin(), r.end(), cmp);

	int ans = 0;
	for (int i = 0; i < m; i++) {
		// 使用树状数组快速求和：query(e) - query(b-1)
		int current = query(r[i].e) - query(r[i].b - 1);
		if (current < r[i].t) {
			int need = r[i].t - current;
			for (int j = r[i].e; j >= r[i].b && need > 0; j--) {
				if (!hasTree[j]) {
					hasTree[j] = true;
					update(j, 1); // 更新树状数组
					ans++;
					need--;
				}
			}
		}
	}
	cout << ans;
	return 0;
}



#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge { int to, weight; };
vector<Edge> adj[30005];
int dist[30005];
bool inQue[30005];

int main() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		adj[i - 1].push_back({ i, 0 });    // s[i] >= s[i-1] + 0
		adj[i].push_back({ i - 1, -1 });   // s[i-1] >= s[i] - 1
	}
	for (int i = 0; i < m; i++) {
		int b, e, t; cin >> b >> e >> t;
		adj[b - 1].push_back({ e, t });    // s[e] >= s[b-1] + t
	}

	// SPFA 跑最长路
	for (int i = 0; i <= n; i++) dist[i] = -1e9;
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	inQue[0] = true;

	while (!q.empty()) {
		int u = q.front(); q.pop();
		inQue[u] = false;
		for (auto& edge : adj[u]) {
			if (dist[edge.to] < dist[u] + edge.weight) {
				dist[edge.to] = dist[u] + edge.weight;
				if (!inQue[edge.to]) {
					q.push(edge.to);
					inQue[edge.to] = true;
				}
			}
		}
	}
	cout << dist[n];
	return 0;
}
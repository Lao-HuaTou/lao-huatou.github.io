#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int n, m;
vector<int>adj1[200005], adj2[200005];
int t1[200005], t2[200005];
bool vis_1[200005], vis_2[200005];
bool cmp1(const int& a, const int& b) {
	return t1[a] < t1[b];
}
bool cmp2(const int& a, const int& b) {
	return t2[a] < t2[b];
}
struct info {
	int id1, id2, dp;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> t1[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> t2[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		adj1[u].push_back(v);
		adj1[v].push_back(u);
	}
	for (int i = 1; i < m; i++) {
		int p, q;
		cin >> p >> q;
		adj2[p].push_back(q);
		adj2[q].push_back(p);
	}
	for (vector<int>&a : adj1) {
		sort(a.begin(), a.end(), cmp1);
	}
	for (vector<int>&a : adj2) {
		sort(a.begin(), a.end(), cmp2);
	}
	int ans = 0;
	queue<info>q;
	if (t1[1] != t2[1]) {
		cout << 0; return 0;
	}
	q.push({ 1,1,1 });
	while (!q.empty()) {
		auto now = q.front();
		q.pop();
		vis_1[now.id1] = 1;
		vis_2[now.id2] = 1;
		ans = max(ans, now.dp);
		int i = 0, j = 0;
		while (i < adj1[now.id1].size() && j < adj2[now.id2].size()) {
			if (t1[adj1[now.id1][i]] < t2[adj2[now.id2][j]]) {
				i++;
			}
			else if(t1[adj1[now.id1][i]] > t2[adj2[now.id2][j]]) {
				j++;
			}
			else {
				if (vis_1[adj1[now.id1][i]] == 0 && vis_2[adj2[now.id2][j]] == 0) {
					q.push({ adj1[now.id1][i],adj2[now.id2][j],now.dp + 1 });
				}
				i++; j++;
			}
		}
	}
	cout << ans;
	return 0;
}
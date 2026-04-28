#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 5005;
const int M = 20005;
struct Edge {
	int u, v, w;
	bool operator<(const Edge& o)const {
		return w < o.w;
	}
};
vector<Edge>edge(2 * M);
//0 u  1   v   2  w
int p[N];
int n;
void build(int n) {
	for (int i = 0; i <= n; i++)p[i] = i;
}
int ans = 0;
int find(int x) {
	return (x == p[x] ? x : p[x] = find(p[x]));
}
void merge(int x, int y) {
	int rx = find(x); int ry = find(y);
	if (rx != ry) p[rx] = ry;
}
int well[N];
void solve() {
	ans = 0;
	int cnt = 0;
	for (int i = 1; i <= n; i++) edge.push_back({0,i,well[i]});
	sort(edge.begin(), edge.end());
	for (int i = 0; i < edge.size(); i++) {
		if (find(edge[i].u) != find(edge[i].v)) {
			ans += edge[i].w;
			cnt++;
			if (cnt == n - 1) {
				cout << ans;
				return;
			}
		}
	}
	cout << "orz";
}


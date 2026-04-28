
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 2e5;
int p[N];
struct Node {
	int id, v;
};
struct Edge {
	int u, v, w;
	bool operator<(const Edge& a)const {
		return w < a.w;
	}
};
int maxCnt[N];
int val[N];//value of dots or group
void build(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		maxCnt[i] = 1;

	}
}
int find(int x) {
	return x == p[x] ? x : p[x] = find(p[x]);
}
int merge(int x, int y) {
	int rx = find(x);
	int ry = find(y);
	int path = 0;
	if (val[rx] > val[ry]) {
		p[ry] = rx;
		
	}
	else if (val[rx] < val[ry]) {
		p[rx] = ry;
	}
	else {
		path += maxCnt[rx] * maxCnt[ry];
		p[rx] = ry;
		maxCnt[ry] += maxCnt[rx];
	}
	return path;
}
int main() {
	int n, m;
	cin >> n >> m;
	build(n);
	vector<Node>d(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}
	vector<Edge>edge;
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		int w;
		w = max(val[x], val[y]);
		edge.push_back({ x,y,w });
	}
	sort(edge.begin(), edge.end());
	for (auto i : edge) {
		ans+=merge(i.u, i.v);
	}
	cout << ans+n;
	return 0;
}
 //13 12  1 2 2 3 1 2 2 1 1 3 3 3 3  1 2  1 3 1 4 2 5 5 8 5 9 4 6 4 7 7 10 7 11 7 12 10 13

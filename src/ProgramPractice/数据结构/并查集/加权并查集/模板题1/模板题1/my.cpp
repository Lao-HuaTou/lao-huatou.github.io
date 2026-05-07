#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int N = 1e5 + 5;
int dis[N], p[N];

int find(int x) {
	if (x != p[x]) {
		int tem = p[x];//每一个根节点在合并时更新，其他节点在find时更新
		p[x] = find(p[x]);
		dis[x] += dis[tem];
	}
	return p[x];
}
void merge(int x, int y, int v) {
	int rx = find(x), ry = find(y);
	if (rx == ry)return;
	p[rx] = ry;
	dis[rx] = v - dis[x] + dis[y];
	return;
}
int query(int x, int y) {
	return dis[x] - dis[y];
}
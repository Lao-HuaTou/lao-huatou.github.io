#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

int n, k;
const int N = 5e4 + 5;
int p[N], d[N];
void build(int x) {
	for (int i = 0;i < x;i++) {
		p[i] = i;
		d[i] = 1;
	}
}
int find(int x) {
	if (x = p[x])return x;
	int tem = find(p[x]);
	d[x] =(d[x] + d[tem])%3;
	return p[x]=tem;
}
void same(int x, int y) {
	int rx = find(x);int ry = find(y);
	if (rx == ry)return ;
	p[rx] = ry;
	d[ry] = (d[rx] - d[ry] + 6) % 3;
}
void eat(int x, int y) {
	int rx = find(x);int ry = find(y);
	if (rx == ry)return ;
	p[rx] = ry;
	d[ry] = ;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n >> k;

}
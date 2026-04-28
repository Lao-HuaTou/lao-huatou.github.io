#include<iostream>
#include<vector>
using namespace std;
int n, m;
int N = 400005;
int p[400005];
int s[400005];
int reans;
vector<int>attack;
void init(int x){
	for (int i = 0; i < n; i++) {
		p[i] = i;
		s[i] = 1;
	}
}
int find(int x) {
	if (p[x] == x) return x;
	else return p[x] = find(p[x]);
}
void union1(int x, int y) {
	int rx = find(x);
	int ry = find(y);
	if (rx != ry) {
		if (s[rx] < s[ry]) {
			p[rx] = ry;
			s[rx] += s[ry];
		}
		else {
			p[ry] = rx;
			s[ry] += s[rx];
		}
		reans--;
	}
}
int ans[400005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	vector<bool>live(n,true);
	vector<vector<int>>map(n);//map[i]={。。。。} i可去的点
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		map[x].push_back(y);
		map[y].push_back(x);
	}
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int x; cin >> x;
		attack.push_back(x);
		live[x] = false;
	}
	init(n);
	reans = n - k;
	for (int i = 0; i < n; i++) {
		if (live[i]) {
			for (auto j : map[i]) {
				if(live[j]) union1(i, j);
			}
		}
	}
	ans[k] = reans;
	for (int i = k - 1; i >= 0; i--) {
		int now = attack[i];
		live[now] = true;
		reans++;
		for (auto j : map[now]) {
			if (live[j]) union1(now, j);
		}
		ans[i] = reans;
	}
	for (int i = 0; i <= k; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}



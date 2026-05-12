#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
#define int long long
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

struct p {
	int x;
	int y;
	int l;
	int r;
	int cnt;
};


void solve() {
	int n, m;
	cin >> n >> m;
	int stx, sty;
	int edx, edy;
	queue<p> q;
	vector<vector<char>> mp(n, vector<char>(m));
	vector<vector<vector<vector<bool>>>> vis(n, vector<vector<vector<bool>>>(m, vector<vector<bool>>(4, vector<bool>(4, 0))));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> mp[i][j];
			if (mp[i][j] == 'S') {
				stx = i, sty = j;
			}
			if (mp[i][j] == 'T') {
				edx = i, edy = j;
				mp[i][j] = '.';
			}
		}
	}
	for (int i = 0; i < 4; ++i) {
		q.push({ stx,sty,i,0,0 });
		vis[stx][sty][i][0] = 1;
	}
	while (!q.empty()) {
		p tp = q.front();
		q.pop();
		if (tp.x == edx && tp.y == edy) {
			cout << tp.r << endl;
			return;
		}
		for (int i = 0; i < 4; ++i) {
			int tx, ty;
			tx = tp.x + dx[i];
			ty = tp.y + dy[i];
			if (tx >= 0 && ty >= 0 && tx <n && ty < m && mp[tx][ty] == '.') {
				if (tp.l == i) {
					if (tp.cnt < 3 && !vis[tx][ty][i][tp.cnt + 1]) {
						vis[tx][ty][i][tp.cnt + 1] = 1;
						q.push({ tx,ty,tp.l,tp.r + 1,tp.cnt + 1 });
					}
				}
				else if (!vis[tx][ty][i][1]) {
					vis[tx][ty][i][1] = 1;
					q.push({ tx,ty,i,tp.r + 1,1 });
				}
			}
		}
	}
	cout << -1 << endl;
}



signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	//cin >> t;
	t = 1;
	while (t--) {
		solve();
	}
	return 0;
}
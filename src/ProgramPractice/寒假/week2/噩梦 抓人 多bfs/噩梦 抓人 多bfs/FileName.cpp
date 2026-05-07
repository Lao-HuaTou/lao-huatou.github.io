#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
struct Node {
	int x, y;
};
vector<vector<char>>map;
Node g1, g2, boy, girl;
bool is_goast(int x, int y, int time) {
	int s1 = abs(x - g1.x) + abs(y - g1.y);
	int s2 = abs(x - g2.x) + abs(y - g2.y);
	if (s1 <= time << 1 || s2 <= time << 1) return true;
	return false;
}
bool vis_b[805][805];
bool vis_g[805][805];
int mx[4] = {0,1,0,-1};
int my[4] = {1,0,-1,0};


int bfs(int n,int m) {
	memset(vis_b, false,sizeof(vis_b));
	memset(vis_g, false,sizeof(vis_g));
	queue<Node>bo;
	queue<Node>gi;
	bo.push(boy);
	gi.push(girl);
	vis_b[boy.x][boy.y] = true;
	vis_g[girl.x][girl.y] = true;
	if (is_goast(boy.x, boy.y, 0) || is_goast(girl.x, girl.y, 0)) return -1;
	int time = 0;
	while (!bo.empty() || !gi.empty()) {
		time++;
		for (int step = 0; step < 3; step++) {
			int cnt_b = bo.size();
			while (cnt_b--) {
				Node nb = bo.front();
				bo.pop();
				if (is_goast(nb.x, nb.y, time)) continue;
				for (int p = 0; p < 4; p++) {
					int nx = nb.x + mx[p];
					int ny = nb.y + my[p];
					if (is_goast(nx, ny, time))continue;
					if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && map[nx][ny] != 'X' && !is_goast(nx, ny, time) && !vis_b[nx][ny]) {
						if (vis_g[nx][ny]) return time;
						bo.push({ nx,ny });
						vis_b[nx][ny] = true;
					}
				}
			}
		}

		int cnt_g = gi.size();
		while (cnt_g--) {
			Node ng = gi.front();
			gi.pop();
			if (is_goast(ng.x, ng.y, time)) continue;
			for (int p = 0; p < 4; p++) {
				int nx = ng.x + mx[p];
				int ny = ng.y + my[p];
				if (is_goast(nx, ny, time))continue;
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && map[nx][ny] != 'X' && !is_goast(nx, ny, time) && !vis_g[nx][ny]) {
					if (vis_b[nx][ny]) return time;
					gi.push({ nx,ny });
					vis_g[nx][ny] = true;
				}
			}
		}
	}
	return -1;
}
void solve() {
	int n, m; cin >> n >> m;
	map.assign(n + 1, vector<char>(m + 1, 'X'));
	bool flag_g1 = false;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			char x = map[i][j];
			if (x == 'Z') {
				if (!flag_g1) {
					g1 = { i,j };
					flag_g1 = true;
				}
				else g2 = { i,j };
			}
			else if (x == 'M') {
				boy = { i,j };
			}
			else if (x == 'G') girl = { i,j };
		}
	}
	cout << bfs(n, m) << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
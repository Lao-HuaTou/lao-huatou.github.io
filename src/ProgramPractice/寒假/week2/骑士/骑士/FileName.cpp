#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
struct Node {
	int x, y;
	int step;
};
int map[305][305];
int dx[] = { -1,-2,-2,-1,1,2,2,1 };
int dy[] = { -2,-1,1,2,2,1,-1,-2 };
int main() {
	int t; cin >> t;
	while (t--) {
		int L; cin >> L;
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a == c && b == d) {
			cout << "0\n";
			continue;
		}
		memset(map, 0, sizeof(map));
		queue<Node>q;
		q.push({a,b,0});
		map[a][b] = 1;
		int ans = -1;
		bool found = false;
		while (!q.empty()) {
			Node now = q.front(); q.pop();
			for (int i = 0; i < 8; i++) {
				int x = now.x + dx[i];
				int y = now.y + dy[i];
				if (x >= 0 && x < L && y >= 0 && y < L && !map[x][y]) {
					q.push({ x,y,now.step + 1 });
					map[x][y] = 1;
					if(x==c&&y==d) {
						ans = now.step + 1;
						found = true;
						break;
					}
				}
			}
			if (found) break;
		}
		cout << ans << "\n";
	}
	return 0;
}
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<cstring>
using namespace std;
struct Node {
		int x;
	int y;

};
int dx[] = {0,-1,-1,-1,0,1,1,1};
int dy[] = {-1,-1,0,1,1,1,0,-1};
char map[105][105];
bool vis[105][105];
int main()
{
	int m, n;
	cin >> m >> n;
	while (m != 0) {
		memset(map, '*', sizeof(map));
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				cin >> map[i][j];
			}
			getchar();
		}
		int ans = 0;
		memset(vis, false, sizeof(vis));
		
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j] == '@'&&!vis[i][j]) {
					ans++;
					vis[i][j] = true;
					queue<Node>q;
					q.push({ i,j });
					while (!q.empty()) {
						Node now = q.front();
						q.pop();
						for (int ck = 0; ck < 8; ck++) {
							int new_x = now.x + dx[ck];
							int new_y = now.y + dy[ck];
							if (new_x>=1&&new_x<=m&&new_y>=1&&new_y<=n&&map[new_x][new_y] == '@'&&!vis[new_x][new_y]) {
								vis[new_x][new_y] = true;
								q.push({ new_x,new_y });
							}
						}
					}
				}
			}
		}
		cout << ans << '\n';
		cin >> m >> n;
	}
	return 0;
}



//#include<iostream>
//#include<cstring>
//using namespace std;
//
//int m, n;
//char map_data[105][105];
//bool vis[105][105];
//int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
//int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
//
//// DFS 递归函数：负责把这一片连通的油田全部标记为 vis
//void dfs(int x, int y) {
//	vis[x][y] = true; // 标记当前油囊
//
//	for (int i = 0; i < 8; i++) {
//		int nx = x + dx[i];
//		int ny = y + dy[i];
//
//		// 如果在范围内、是油囊、且没被访问过，就递归深入
//		if (nx >= 1 && nx <= m && ny >= 1 && ny <= n &&
//			map_data[nx][ny] == '@' && !vis[nx][ny]) {
//			dfs(nx, ny);
//		}
//	}
//}
//
//int main() {
//	while (cin >> m >> n && m != 0) {
//		memset(vis, false, sizeof(vis));
//		for (int i = 1; i <= m; i++) {
//			for (int j = 1; j <= n; j++) {
//				cin >> map_data[i][j];
//			}
//		}
//
//		int ans = 0;
//		for (int i = 1; i <= m; i++) {
//			for (int j = 1; j <= n; j++) {
//				// 发现一个新起点，只调用一次递归，它就能“排除”整片油田
//				if (map_data[i][j] == '@' && !vis[i][j]) {
//					ans++;
//					dfs(i, j);
//				}
//			}
//		}
//		cout << ans << '\n';
//	}
//	return 0;
//}
////‘.’ 表示一个空地，所有人都可以走。
////‘X’ 表示一堵墙，只有人不能走。
////‘M’ 表示小二月
////‘W’ 表示女朋友。
////‘G’ 表示鬼魂。
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <set>
//#include<queue>
//using namespace std;
//typedef struct NODE {
//	int x, y;
//}dot;
//int dx[] = { 0,-1,0,1 };
//int dy[] = { -1,0,1,0 };
//int m, n;
//vector<vector<char>>map;
//dot man, w, g;
//int ck=0;
//void dfs() {
//	queue<dot>qw,qm,qg;
//	qw.push(w); qm.push(man); qg.push(g);
//	while (!qw.empty()||!qm.empty()) {
//		dot curw = qw.front();
//		qw.pop();
//		dot curm = qm.front(); qm.pop();
//		for (int i = 0; i < 4; i++) {
//			int go = 2;
//			
//			int cx = curw.x + dx[i];
//			int cy = curw.y + dy[i];
//			if (cx>=1 && cx<=m && cy>=1 && cy<=n) {
//				if (map[cx][cy] != 'G' && map[cx][cy] != 'X') {
//					qw.push({ cx,cy });
//				}
//			}
//		}
//	}
//}
//int main()
//{
//	int t; cin >> t;
//	while (t--) {
//		 cin >> m >> n;
//		 map.clear();
// 		map.resize(m+1, vector<char>(n+1));
//		for (int x = 1; x <= m; x++)
//		{
//			for (int y = 1; y <= n; y++) {
//				cin >> map[x][y];
//				if (map[x][y] == 'M') {
//					man.x = x; man.y = y;
//				}
//				else if (map[x][y] == 'W') {
//					w.x = x; w.y = y;
//				}
//				else if (map[x][y] == 'G') {
//					g.x = x; g.y = y;
//				}
//			}
//		}
//	}
//}


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

struct NODE {
    int x, y;
};
int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };
int m, n;
char map_data[805][805];
bool vis_man[805][805], vis_w[805][805];
NODE man, w;
vector<NODE> zs;
bool is_ghost(int x, int y, int time) {
    for (int i = 0; i < zs.size(); i++) {
        int dist = abs(x - zs[i].x) + abs(y - zs[i].y);
        if (dist <= 2 * time) return true;
    }
    return false;
}
int bfs() {
    queue<NODE> qm, qw;
    qm.push(man);
    qw.push(w);
    memset(vis_man, 0, sizeof(vis_man));
    memset(vis_w, 0, sizeof(vis_w));
    vis_man[man.x][man.y] = true;
    vis_w[w.x][w.y] = true;

    int time = 0;
    while (!qm.empty() || !qw.empty()) {
        time++;
        for (int step = 0; step < 3; step++) {
            int sz = qm.size();
            while (sz--) {
                NODE curr = qm.front(); qm.pop();
                if (is_ghost(curr.x, curr.y, time)) continue;

                for (int i = 0; i < 4; i++) {
                    int nx = curr.x + dx[i], ny = curr.y + dy[i];
                    if (nx >= 1 && nx <= m && ny >= 1 && ny <= n && map_data[nx][ny] != 'X'
                        && !is_ghost(nx, ny, time) && !vis_man[nx][ny]) {
                        if (vis_w[nx][ny]) return time;
                        vis_man[nx][ny] = true;
                        qm.push({ nx, ny });
                    }
                }
            }
        }

        int sz = qw.size();
        while (sz--) {
            NODE curr = qw.front(); qw.pop();
            if (is_ghost(curr.x, curr.y, time)) continue;

            for (int i = 0; i < 4; i++) {
                int nx = curr.x + dx[i], ny = curr.y + dy[i];
                if (nx >= 1 && nx <= m && ny >= 1 && ny <= n && map_data[nx][ny] != 'X'
                    && !is_ghost(nx, ny, time) && !vis_w[nx][ny]) {
                    if (vis_man[nx][ny]) return time;
                    vis_w[nx][ny] = true;
                    qw.push({ nx, ny });
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> m >> n;
        zs.clear();
        for (int x = 1; x <= m; x++) {
            for (int y = 1; y <= n; y++) {
                cin >> map_data[x][y];
                if (map_data[x][y] == 'M') man = { x, y };
                else if (map_data[x][y] == 'G') w = { x, y };
                else if (map_data[x][y] == 'Z') zs.push_back({ x, y });
            }
        }
        cout << bfs() << endl;
    }
    return 0;
}
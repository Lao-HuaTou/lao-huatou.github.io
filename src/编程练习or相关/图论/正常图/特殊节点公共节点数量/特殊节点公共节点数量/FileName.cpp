#include <iostream>
#include <cstring>
using namespace std;
const int N = 1505;
const int M = 1505;
char mat[N][N];
int n, m;
// vis[rX][rY] 记录该相对位置是否访问过
bool vis[N][M];
// lastX 和 lastY 记录第一次到达相对位置 (rX, rY) 时的绝对坐标
int lastX[N][M], lastY[N][M];

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
bool flag; // 是否找到无限路径

void dfs(int x, int y, int rx, int ry) {//绝对坐标  相对坐标
    if (flag) return; // 已经找到结果，提前退出

    // 如果这个相对位置之前走过
    if (vis[rx][ry]) {
        // 关键判定：对比当前绝对坐标和记录的绝对坐标
        // 如果坐标不同，说明从一个副本跑到了另一个副本的相同位置
        if (lastX[rx][ry] != x || lastY[rx][ry] != y) {
            flag = true;
        }
        return;//相同则说明陷入死循环 故直接返回
    }

    // 第一次到达，记录状态
    vis[rx][ry] = true;
    lastX[rx][ry] = x;
    lastY[rx][ry] = y;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 计算下一步的相对位置（C++ 取模负数处理）
        int nrx = (nx % n + n) % n;
        int nry = (ny % m + m) % m;

        if (mat[nrx][nry] != '#') {
            dfs(nx, ny, nrx, nry);
        }
    }
}

void solve() {
    int sx, sy;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            if (mat[i][j] == 'S') {
                sx = i; sy = j;
            }
        }
    }

    // 清空数据
    flag = false;
    memset(vis, 0, sizeof vis);
    // 注意：如果是 DFS 寻找路径，不需要 memset lastX/lastY，因为 vis 会挡住

    dfs(sx, sy, sx, sy);

    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        solve();
    }
    return 0;
}
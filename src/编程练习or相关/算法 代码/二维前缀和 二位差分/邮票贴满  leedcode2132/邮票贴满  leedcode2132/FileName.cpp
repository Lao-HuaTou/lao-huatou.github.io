#include<iostream>
#include<vector>
using namespace std;

// 建议使用 long long 或 int，这里 grid 较大建议放在全局或用 vector
vector<vector<int>> mat;   // 原始矩阵
vector<vector<int>> pre;   // 二维前缀和数组
vector<vector<int>> diff;  // 二维差分数组
int n, m;
int h, w;

// 1. 二维前缀和查询：计算 (a,b) 到 (c,d) 矩形内的障碍物数量
int get(int a, int b, int c, int d) {
    return pre[c][d] - pre[c][b - 1] - pre[a - 1][d] + pre[a - 1][b - 1];
}

// 2. 判断当前位置 (x,y) 是否能放下 h * w 的邮票
bool ck(int x, int y) {
    // 越界检查：如果邮票右下角超出了网格范围，不能贴
    if (x + h - 1 > n || y + w - 1 > m) return false;
    // 只要区域内障碍物总和为 0，说明全是空格，可以贴
    if (get(x, y, x + h - 1, y + w - 1) == 0) return true;
    return false;
}

// 3. 二维差分：在 (x,y) 到 (x+h-1, y+w-1) 区域盖章
void add(int x, int y) {
    int x2 = x + h - 1;
    int y2 = y + w - 1;
    diff[x][y]++;
    diff[x][y2 + 1]--;
    diff[x2 + 1][y]--;
    diff[x2 + 1][y2 + 1]++;
}

int main() {
    // 注意输入顺序：先地图大小 n, m，再邮票大小 h, w
    if (!(cin >> n >> m >> h >> w)) return 0;

    // 初始化数组大小 (n+2 是为了防止差分越界)
    mat.assign(n + 1, vector<int>(m + 1));
    pre.assign(n + 1, vector<int>(m + 1, 0));
    diff.assign(n + 2, vector<int>(m + 2, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
            // 预处理前缀和
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + mat[i][j];
        }
    }

    // 第一遍遍历：尝试在所有位置贴邮票
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ck(i, j)) add(i, j);
        }
    }

    // 第二遍遍历：还原差分数组，计算每个格子的覆盖次数
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 利用前缀和原理还原差分
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];

            // 最终判断：如果是空格(0)且覆盖次数也是 0
            if (mat[i][j] == 0 && diff[i][j] == 0) {
                cout << "false" << endl;
                return 0;
            }
        }
    }

    cout << "true" << endl;
    return 0;
}
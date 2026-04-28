#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
#define int long long
const long long INF = 1e18;
int n, m, q;

// 修正：在知道n的值后再初始化vector
vector<vector<int>> matrix;

int dig(int st, int ed) {
    // 使用Floyd算法后，直接返回矩阵中存储的结果
    
    return matrix[st][ed] >= INF ? -1 : matrix[st][ed]; // 如果不可达返回-1
}

signed main()
{
    cin >> n >> m >> q;

    // 修正：在输入n后才初始化matrix
    matrix.resize(n + 1, vector<int>(n + 1, INF));

    // 初始化：自己到自己的距离为0
    for (int i = 1; i <= n; i++) {
        matrix[i][i] = 0;
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        matrix[u][v] = min(matrix[u][v], w);
        matrix[v][u] = min(matrix[v][u], w);// 处理重边，取最小值
    }

    // Floyd算法：放在主函数中只执行一次
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (matrix[i][k] < INF && matrix[k][j] < INF) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int st, ed;
        cin >> st >> ed;
        cout << dig(st, ed) << "\n";
    }

    return 0;
}
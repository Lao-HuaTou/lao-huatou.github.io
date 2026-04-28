#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 推导部分和，带权并查集模版题1
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 先给出m个数字段的累加和，再查询q个数字段的累加和
// 给出数字段累加和的操作 l r v，代表l~r范围上的数字，累加和为v
// 查询数字段累加和的操作 l r，代表查询l~r范围上的数字累加和
// 请根据m个给定，完成q个查询，如果某个查询无法给出答案，打印"UNKNOWN"
// 1 <= n, m, q <= 10^5
// 累加和不会超过long类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P8779
// 提交时请把类名改成"Main"，可以通过所有测试用例
class Code01_DerivePartialSums {
public:
    static const int MAXN = 100005;
    static const long long INF = LLONG_MAX;

    static int n, m, q;
    static int father[MAXN];
    static long long dist[MAXN];

    static void prepare() {
        for (int i = 0; i <= n; i++) {
            father[i] = i;
            dist[i] = 0;
        }
    }

    static int find(int i) {
        if (i != father[i]) {
            int tmp = father[i];
            father[i] = find(tmp);
            // 递归更新权值：dist[i] 代表 i 到父节点的距离
            dist[i] += dist[tmp];
        }
        return father[i];
    }

    static void union_sets(int l, int r, long long v) {
        int lf = find(l), rf = find(r);
        if (lf != rf) {
            father[lf] = rf;
            // 权值更新公式：dist[l] + dist[new_edge] = v + dist[r]
            dist[lf] = v + dist[r] - dist[l];
        }
    }

    static long long query(int l, int r) {
        if (find(l) != find(r)) {
            return INF;
        }
        // 同一个集合中，利用前缀和之差求区间和
        return dist[l] - dist[r];
    }
};

// 静态变量初始化
int Code01_DerivePartialSums::n;
int Code01_DerivePartialSums::m;
int Code01_DerivePartialSums::q;
int Code01_DerivePartialSums::father[Code01_DerivePartialSums::MAXN];
long long Code01_DerivePartialSums::dist[Code01_DerivePartialSums::MAXN];

int main() {
    // 快速 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (!(cin >> Code01_DerivePartialSums::n >> Code01_DerivePartialSums::m >> Code01_DerivePartialSums::q)) {
        return 0;
    }

    // 内部下标处理：n 自增以适配范围
    Code01_DerivePartialSums::n += 1;
    Code01_DerivePartialSums::prepare();

    int l, r;
    long long v;
    for (int i = 1; i <= Code01_DerivePartialSums::m; i++) {
        cin >> l >> r >> v;
        // 原代码逻辑：r 变为 r + 1 形成前缀和坐标
        Code01_DerivePartialSums::union_sets(l, r + 1, v);
    }
    
    for (int i = 1; i <= Code01_DerivePartialSums::q; i++) {
        cin >> l >> r;
        v = Code01_DerivePartialSums::query(l, r + 1);
        if (v == Code01_DerivePartialSums::INF) {
            cout << "UNKNOWN" << "\n";
        }
        else {
            cout << v << "\n";
        }
    }

    return 0;
}
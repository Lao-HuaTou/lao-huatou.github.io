#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// 银河英雄传说
// 一共有30000搜战舰，编号1~30000，一开始每艘战舰各自成一队
// 如果若干战舰变成一队，那么队伍里的所有战舰竖直地排成一列
// 实现如下两种操作，操作一共调用t次
// M l r : 合并l号战舰所在队伍和r号战舰所在队伍
//         l号战舰的队伍，整体移动到，r号战舰所在队伍的最末尾战舰的后面
//         如果l号战舰和r号战舰已经是一队，不进行任何操作
// C l r : 如果l号战舰和r号战舰不在一个队伍，打印-1
//         如果l号战舰和r号战舰在一个队伍，打印它俩中间隔着几艘战舰
// 1 <= t <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1196
// 提交时请把类名改成"Main"，可以通过所有测试用例
class Code04_LegendOfHeroes {
public:
    static const int MAXN = 30001;
    static const int n = 30000;

    static int father[MAXN];
    static int dist[MAXN];
    static int size[MAXN];

    // 递归可能会爆栈，所以用迭代来寻找并查集代表节点
    static int stack_arr[MAXN];

    static void prepare() {
        for (int i = 1; i <= n; i++) {
            father[i] = i;
            dist[i] = 0;
            size[i] = 1;
        }
    }

    // 迭代的方式实现find，防止递归爆栈
    static int find(int i) {
        int si = 0;
        int curr = i;
        while (curr != father[curr]) {
            stack_arr[++si] = curr;
            curr = father[curr];
        }
        // curr 现在是代表节点（根）
        // 从上往下更新，保证 dist 的累加正确
        // stack_arr[si] 是根的直接孩子
        for (int j = si; j >= 1; j--) {
            int node = stack_arr[j];
            int p = father[node];
            dist[node] += dist[p];
            father[node] = curr;
        }
        return curr;
    }

    static void union_sets(int l, int r) {
        int lf = find(l), rf = find(r);
        if (lf != rf) {
            // l 所在的队伍整体移动到 r 所在队伍的后面
            // 所以 l 的根 lf 指向 r 的根 rf
            father[lf] = rf;
            // lf 到 rf 的距离就是目前 rf 队伍的总长度
            dist[lf] = size[rf];
            // 更新 rf 队伍的总长度
            size[rf] += size[lf];
        }
    }

    static int query(int l, int r) {
        if (find(l) != find(r)) {
            return -1;
        }
        // 中间相隔战舰数 = |dist[l] - dist[r]| - 1
        return abs(dist[l] - dist[r]) - 1;
    }
};

// 静态变量定义
int Code04_LegendOfHeroes::father[Code04_LegendOfHeroes::MAXN];
int Code04_LegendOfHeroes::dist[Code04_LegendOfHeroes::MAXN];
int Code04_LegendOfHeroes::size[Code04_LegendOfHeroes::MAXN];
int Code04_LegendOfHeroes::stack_arr[Code04_LegendOfHeroes::MAXN];

int main() {
    // 快速 I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Code04_LegendOfHeroes::prepare();

    int t;
    if (!(cin >> t)) return 0;

    string op;
    int l, r;
    while (t--) {
        cin >> op >> l >> r;
        if (op == "M") {
            Code04_LegendOfHeroes::union_sets(l, r);
        }
        else {
            cout << Code04_LegendOfHeroes::query(l, r) << "\n";
        }
    }

    return 0;
}
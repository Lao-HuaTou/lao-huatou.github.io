#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 关押罪犯
// 一共有n个犯人，编号1 ~ n，一共有两个监狱，你可以决定每个犯人去哪个监狱
// 给定m条记录，每条记录 l r v，表示l号犯人和r号犯人的仇恨值
// 每个监狱的暴力值 = 该监狱中仇恨最深的犯人之间的仇恨值
// 冲突值 = max(第一座监狱的暴力值，第二座监狱的暴力值)
// 犯人的分配方案需要让这个冲突值最小，返回最小能是多少
// 1 <= n <= 20000    1 <= m <= 100000    1 <= 仇恨值 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P1525
// 提交时请把类名改成"Main"，可以通过所有测试用例
class Code07_DetainCriminals {
public:
    static const int MAXN = 20005;
    static const int MAXM = 100005;

    struct Edge {
        int l, r, v;
    };

    static int n, m;
    static int father[MAXN];
    static int enemy[MAXN];
    static Edge arr[MAXM];

    static void prepare() {
        for (int i = 1; i <= n; i++) {
            father[i] = i;
            enemy[i] = 0;
        }
    }

    static int find(int i) {
        if (father[i] == i) return i;
        return father[i] = find(father[i]);
    }

    static void union_sets(int l, int r) {
        int fl = find(l);
        int fr = find(r);
        if (fl != fr) {
            father[fl] = fr;
        }
    }

    static bool same(int l, int r) {
        return find(l) == find(r);
    }

    static int compute() {
        // 按照仇恨值从大到小排序 (b[2] - a[2] 逻辑)
        sort(arr + 1, arr + m + 1, [](const Edge& a, const Edge& b) {
            return a.v > b.v;
            });

        int ans = 0;
        for (int i = 1; i <= m; i++) {
            int l = arr[i].l;
            int r = arr[i].r;
            int v = arr[i].v;

            if (same(l, r)) {
                // 如果当前仇恨最大的两人已经在同一个集合（同一个监狱），产生冲突
                ans = v;
                break;
            }
            else {
                // 敌人的敌人是朋友
                if (enemy[l] == 0) {
                    enemy[l] = r;
                }
                else {
                    union_sets(enemy[l], r);
                }

                if (enemy[r] == 0) {
                    enemy[r] = l;
                }
                else {
                    union_sets(l, enemy[r]);
                }
            }
        }
        return ans;
    }
};

// 静态成员初始化
int Code07_DetainCriminals::n;
int Code07_DetainCriminals::m;
int Code07_DetainCriminals::father[Code07_DetainCriminals::MAXN];
int Code07_DetainCriminals::enemy[Code07_DetainCriminals::MAXN];
Code07_DetainCriminals::Edge Code07_DetainCriminals::arr[Code07_DetainCriminals::MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> Code07_DetainCriminals::n >> Code07_DetainCriminals::m)) {
        return 0;
    }

    Code07_DetainCriminals::prepare();

    for (int i = 1; i <= Code07_DetainCriminals::m; i++) {
        cin >> Code07_DetainCriminals::arr[i].l >> Code07_DetainCriminals::arr[i].r >> Code07_DetainCriminals::arr[i].v;
    }

    cout << Code07_DetainCriminals::compute() << endl;

    return 0;
}
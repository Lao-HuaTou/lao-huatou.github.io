#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
struct T {
    int num;
    int tree;
    bool cut;
};
int cmp(const void* a, const void* b)
{
    T* x = (T*)a;
    T* y = (T*)b;
    if (x->tree == y->tree)
        return x->num - y->num;
    return x->tree - y->tree;
}
int n;
vector<T>tr;
int search(int x)
{
    int l = 0, r = n - 1;
    int idx = -1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (tr[mid].tree >= x) {
            if (tr[mid].tree == x) idx = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }

    if (idx == -1) return -1;

    for (int i = idx; i < n && tr[i].tree == x; i++) {
        if (!tr[i].cut) {
            return i;
        }
    }

    return -1;
}
int main()
{
    int m;
    while ((scanf_s("%d %d",&n,&m))!=EOF) {  // 处理多组数据
        tr.resize(n);
        vector<int>hgt(m);
        for (int i = 0; i < n; i++) {
            cin >> tr[i].tree;
            tr[i].num = i + 1;
            tr[i].cut = false;
        }
        for (int i = 0; i < m; i++) cin >> hgt[i];
        qsort(&tr[0], n, sizeof(T), cmp);

        for (int i = 0; i < m; i++)
        {
            int id = search(hgt[i]);
            if (id != -1) {
                tr[id].cut = true;
                cout << tr[id].num << endl;
            }
            else cout << "-1" << endl;
        }
    }
    return 0;
}


#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n >> m) {
        vector<int> h(n + 1);
        map<int, set<int>> mp; 

        for (int i = 1; i <= n; i++) {
            cin >> h[i];
            mp[h[i]].insert(i);
        }

        for (int i = 0; i < m; i++) {
            int q;
            cin >> q;

            if (mp.count(q) && !mp[q].empty()) {

                int pos = *mp[q].begin();
                cout << pos << endl;
                mp[q].erase(pos);
                if (mp[q].empty()) {
                    mp.erase(q);
                }
            }
            else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}

//线段树
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

const int INF = 2e9;

struct Node {
    int minPos;  // 这个区间内该高度的最小位置
    int left, right;
};

vector<Node> segTree;
vector<unordered_map<int, set<int>>> heightData;  // 每个节点存储高度->位置集合

void build(int node, int l, int r, vector<int>& h) {
    if (l == r) {
        heightData[node][h[l]].insert(l);
        segTree[node] = { l, l, r };
        return;
    }

    int mid = (l + r) / 2;
    build(node * 2, l, mid, h);
    build(node * 2 + 1, mid + 1, r, h);

    // 合并两个子节点的高度数据
    for (auto& p : heightData[node * 2]) {
        for (int pos : p.second) {
            heightData[node][p.first].insert(pos);
        }
    }
    for (auto& p : heightData[node * 2 + 1]) {
        for (int pos : p.second) {
            heightData[node][p.first].insert(pos);
        }
    }

    segTree[node] = { INF, l, r };
}

int query(int node, int height) {
    if (heightData[node].count(height) && !heightData[node][height].empty()) {
        return *heightData[node][height].begin();  // 最小位置
    }

    if (segTree[node].left == segTree[node].right) {
        return INF;
    }

    int leftRes = query(node * 2, height);
    if (leftRes != INF) return leftRes;

    return query(node * 2 + 1, height);
}

void update(int node, int pos, int height) {
    if (segTree[node].left == segTree[node].right) {
        heightData[node][height].erase(pos);
        return;
    }

    int mid = (segTree[node].left + segTree[node].right) / 2;
    if (pos <= mid) {
        update(node * 2, pos, height);
    }
    else {
        update(node * 2 + 1, pos, height);
    }

    heightData[node][height].erase(pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n >> m) {
        vector<int> h(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
        }

        segTree.resize(4 * n);
        heightData.resize(4 * n);
        build(1, 1, n, h);

        for (int i = 0; i < m; i++) {
            int q;
            cin >> q;

            int pos = query(1, q);
            if (pos != INF) {
                cout << pos << endl;
                update(1, pos, q);
            }
            else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}
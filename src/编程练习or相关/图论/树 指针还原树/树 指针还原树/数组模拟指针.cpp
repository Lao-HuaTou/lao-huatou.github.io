#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 300; // 节点总数不超过256
char s[1000];         // 用于读取每个节点的字符串，如 (11,LL)

struct Node {
    int v;
    int left, right;
    bool have_value;

    // 构造函数：初始化节点状态
    Node() : v(0), left(0), right(0), have_value(false) {}

    // 重置函数：方便多组数据重复使用数组
    void reset() {
        v = left = right = 0;
        have_value = false;
    }
} tree[MAXN];
int cnt, root;
bool failed;

// 申请新节点
int newnode() {
    int u = ++cnt;
    tree[u].reset();
    return u;
}

void addnode(int v, char* path) {
    int u = root;
    int n = strlen(path);
    for (int i = 0; i < n; i++) {
        if (path[i] == 'L') {
            if (!tree[u].left) tree[u].left = newnode();
            u = tree[u].left;
        }
        else if (path[i] == 'R') {
            if (!tree[u].right) tree[u].right = newnode();
            u = tree[u].right;
        }
    }
    if (tree[u].have_value) failed = true; // 重复赋值
    tree[u].v = v;
    tree[u].have_value = true;
}

bool read_input() {
    failed = false;
    cnt = 0;
    root = newnode();
    for (;;) {
        if (scanf("%s", s) != 1) return false;
        if (strcmp(s, "()") == 0) break; // 一棵树输入结束
        int v;
        sscanf(&s[1], "%d", &v);        // 读取括号后的数字
        char* path = strchr(s, ',');    // 找到逗号的位置
        if (path == NULL) addnode(v, (char*)""); // 根节点无路径
        else addnode(v, path + 1);      // 逗号后即为路径，注意 path+1 会跳过逗号
    }
    return true;
}

void solve() {
    vector<int> ans;
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (!tree[u].have_value) { failed = true; break; }
        ans.push_back(tree[u].v);
        if (tree[u].left) q.push(tree[u].left);
        if (tree[u].right) q.push(tree[u].right);
    }

    if (failed) printf("not complete\n");
    else {
        for (int i = 0; i < ans.size(); i++)
            printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
}

int main() {
    while (read_input()) {
        solve();
    }
    return 0;
}   
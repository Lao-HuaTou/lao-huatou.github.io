#include <vector>
#include <algorithm>

using namespace std;

// 树节点的第K个祖先
// 树上有n个节点，编号0 ~ n-1，树的结构用parent数组代表
// 其中parent[i]是节点i的父节点，树的根节点是编号为0
// 树节点i的第k个祖先节点，是从节点i开始往上跳k步所来到的节点
// 实现TreeAncestor类
// TreeAncestor(int n, int[] parent) : 初始化
// getKthAncestor(int i, int k) : 返回节点i的第k个祖先节点，不存在返回-1
// 测试链接 : https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/
class TreeAncestor {
public:
    static const int MAXN = 50005;
    static const int LIMIT = 20; // 对应 2^16 左右，根据 n 的范围调整，16-20 均可

    // 根据节点个数n，计算出2的几次方就够用了
    int power;

    static int log2_custom(int n) {
        int ans = 0;
        while ((1 << ans) <= (n >> 1)) {
            ans++;
        }
        return ans;
    }

    // 链式前向星建图
    // 注意：在 LeetCode 环境中，如果是多次实例化，静态数组需要手动 reset
    static int head[MAXN];
    static int next_edge[MAXN];
    static int to[MAXN];
    static int cnt;

    // deep[i] : 节点i在第几层
    static int deep[MAXN];

    // stjump[i][p] : 节点i往上跳2的p次方步，到达的节点编号
    static int stjump[MAXN][LIMIT];

    TreeAncestor(int n, vector<int>& parent) {
        power = log2_custom(n);
        cnt = 1;
        // 初始化 head 数组
        fill(head, head + n, 0);

        for (int i = 1; i < (int)parent.size(); i++) {
            addEdge(parent[i], i);
        }
        dfs(0, 0);
    }

    static void addEdge(int u, int v) {
        next_edge[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt++;
    }

    // 当前来到i节点，i节点父亲节点是f
    static void dfs(int i, int f) {
        if (i == 0) {
            deep[i] = 1;
        }
        else {
            deep[i] = deep[f] + 1;//建立深度表

        }
        stjump[i][0] = f;//0层初始化
        // 倍增预处理
        for (int p = 1; p <= 16; p++) { // 这里的 16 对应 LIMIT-4 左右，保证安全
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
        for (int e = head[i]; e != 0; e = next_edge[e]) {
            dfs(to[e], i);
        }
    }

    int getKthAncestor(int i, int k) {
        if (deep[i] <= k) {
            return -1;
        }
        // s是想要去往的层数
        int s = deep[i] - k;
        for (int p = 16; p >= 0; p--) {
            if (deep[stjump[i][p]] >= s) {
                i = stjump[i][p];
            }
        }
        return i;
    }
};

// 静态成员变量初始化（若在本地执行需要这些，在 LeetCode 类定义内通常不需要重复定义，但为了严谨加上）
int TreeAncestor::head[TreeAncestor::MAXN];
int TreeAncestor::next_edge[TreeAncestor::MAXN];
int TreeAncestor::to[TreeAncestor::MAXN];
int TreeAncestor::cnt = 0;
int TreeAncestor::deep[TreeAncestor::MAXN];
int TreeAncestor::stjump[TreeAncestor::MAXN][TreeAncestor::LIMIT];
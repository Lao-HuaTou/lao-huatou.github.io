//#include <iostream>
//#include <vector>
//#include <algorithm>
//#define int long long
//using namespace std;
//
//int n, W;
//int w[50005], v[50005], d[50005];
//vector<int> adj[50005];
//int seq_w[50005], seq_v[50005], sz[50005];
//int timer = 0;
//void dfs(int u) {
//    sz[u] = 1;
//    for (int son : adj[u]) {
//        dfs(son);
//        sz[u] += sz[son];
//    }
//    timer++;
//    seq_w[timer] = w[u];
//    seq_v[timer] = v[u];
//    sz[timer] = sz[u];
//}
//signed main() {
//    ios::sync_with_stdio(false); cin.tie(0);
//    cin >> n >> W;
//    for (int i = 1; i <= n; i++) {
//        cin >> d[i];
//        adj[d[i]].push_back(i);
//    }
//    for (int i = 1; i <= n; i++) cin >> w[i];
//    for (int i = 1; i <= n; i++) cin >> v[i];
//    w[0] = 0; v[0] = 0;
//    dfs(0);
//    int tem = (timer + 1) * (W + 1);
//    int* pool = new int[tem]();
//    for (int i = 1; i <= timer; i++) {
//        int cur_w = seq_w[i];
//        int cur_v = seq_v[i];
//        int s = sz[i];
//
//        for (int j = 0; j <= W; j++) {
//            // 1. 绝对不选当前节点 i：
//            // 那么 $i$ 及其子树全部放弃，直接继承“这棵树开始前”的状态
//            int skip_idx = i - s;
//            pool[i * (W + 1) + j] = pool[skip_idx * (W + 1) + j];
//
//            // 2. 选当前节点 i：
//            // 只有在选了 i 的前提下，才能继承 i-1 的结果
//            // 注意：这里的 pool[i-1] 在后序中包含了子树的最优组合
//            if (j >= cur_w) {
//                pool[i * (W + 1) + j] = max(pool[i * (W + 1) + j],
//                    pool[(i - 1) * (W + 1) + j - cur_w] + cur_v);
//            }
//        }
//    }
//    cout << pool[timer*(W+1)+W] << endl;
//    return 0;
//}


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, W;
int weight[50005], value[50005];
vector<int> adj[50005];
int dfn_w[50005], dfn_v[50005], sz[50005], timer = 0;
//void dfs(int u) {
//    int id = ++timer;
//    dfn_w[id] = weight[u];
//    dfn_v[id] = value[u];
//    sz[id] = 1;
//    for (int v : adj[u]) {
//        dfs(v);
//        sz[id] += sz[id + sz[id]]; // 这里的逻辑通过 timer 自动处理
//    }
//}

// 更稳妥的 timer 计数
void dfs_fixed(int u) {
    int id = ++timer;
    dfn_w[id] = weight[u];
    dfn_v[id] = value[u];
    int start = timer;//用timer的q
    for (int v : adj[u]) dfs_fixed(v);
    sz[id] = timer - start + 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    if (!(cin >> n >> W)) return 0;
    for (int i = 1; i <= n; i++) {
        int p; cin >> p;
        adj[p].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> weight[i];
    for (int i = 1; i <= n; i++) cin >> value[i];

    // 虚拟根节点 0 必须包含在序列中，且我们强制选它
    dfs_fixed(0);

    // dp[i][j] 表示考虑 DFS 序中第 i 到第 timer 个节点
    // 我们倒着遍历 DFS 序
    ll* dp = new ll[(timer + 2) * (W + 1)]();

    for (int i = timer; i >= 1; i--) {
        for (int j = 0; j <= W; j++) {
            // 选项 1：不选节点 i，直接跳过整棵子树
            int skip = i + sz[i];
            ll res_skip = dp[skip * (W + 1) + j];

            // 选项 2：选节点 i，那么可以继续考虑 i+1 (它的子节点或兄弟)
            ll res_pick = 0;
            if (j >= dfn_w[i]) {
                res_pick = dp[(i + 1) * (W + 1) + j - dfn_w[i]] + dfn_v[i];
            }
            dp[i * (W + 1) + j] = max(res_skip, res_pick);
        }
    }

    // 虚拟根节点在 dfn 序的第 1 位
    cout << dp[1 * (W + 1) + W] << endl;

    delete[] dp;
    return 0;
}

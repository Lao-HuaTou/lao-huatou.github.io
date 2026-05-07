#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
struct edge {
    int to, w, nxt;
} e[N << 1];
int head[N], c = 0;
ll cnt_even = 0, cnt_odd = 0;

void add(int u, int v, int w) {
    e[++c] = {v, w, head[u]};
    head[u] = c;
}
void dfs(int u, int f, int parity) {
    if (parity == 0) cnt_even++;
    else cnt_odd++;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == f) continue;
        dfs(v, u, parity ^ (e[i].w & 1));
    }
}
int main() {
    int n;
    cin >> n;
    for (int i = 0, u, v, w; i < n - 1; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0, 0);
    cout << cnt_even * cnt_odd << endl;
    return 0;
}
//Solution 2

#include<bits/stdc++.h>
using namespace std;
typedef long long ll; // 必须用 long long，10^5 规模路径数会爆 int

const int N = 1e5 + 5;
struct edge {
    int to, w, nxt;
} e[N << 1];
int head[N], c = 0;
ll ans = 0;
ll G[N], O[N]; // G为奇数(Odd)，O为偶数(Even)

void add(int u, int v, int w) {
    e[++c] = {v, w, head[u]};
    head[u] = c;
}

void dfs(int u, int f) {
    O[u] = 1; // 初始状态：u 到自己距离为 0，是一条偶数路径
    G[u] = 0;

    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        int w = e[i].w;
        if (v == f) continue;

        dfs(v, u);

        if (w & 1) { // 边权是奇数
            // 统计跨子树的奇数路径
            ans += O[u] * O[v] + G[u] * G[v];
            // 更新 u 的状态给下一个兄弟子树用
            // 暂存旧值，防止互相干扰
            ll next_O = G[v];
            ll next_G = O[v];
            O[u] += next_O;
            G[u] += next_G;
        } else { // 边权是偶数
            ans += O[u] * G[v] + G[u] * O[v];
            O[u] += O[v];
            G[u] += G[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0, u, v, w; i < n - 1; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }

    dfs(1, 0); // 随便选一个点作为根即可

    cout << ans << endl;
    return 0;
}
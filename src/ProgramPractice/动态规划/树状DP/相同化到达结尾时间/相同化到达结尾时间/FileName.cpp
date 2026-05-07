#include<iostream>
#include<algorithm>

using namespace std;
const int N = 5e5 + 5;
int n,s;
long long ans = 0;
struct edge {
    int to, w, nxt;
}e[N];
int head[N];
int dis[N];
int cnt = 0;
void add(int u, int v,int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
void dfs(int u, int fa) {
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v != fa) {
            dfs(v, u);
            dis[u] = max(dis[u], dis[v] + e[i].w);
        }
    }
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (v != fa) {
            ans += dis[u] - dis[v] - w;
        }
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> s;
     for (int i = 0; i < n - 1; i++) {
         int u, v, w; cin >> u >> v >> w;

         add(u, v, w);
         add(v, u, w);
    }
    dfs(s, 0);
    cout << ans;

    return 0;
}
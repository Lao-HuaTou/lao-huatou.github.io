#include<iostream>
#include<vector>
using namespace std;
const int N = 510;
vector<int>g[N];// g[u]存储u能到达的点 u是左   g[u]是右
int visit[N], match[N];// match[v]存储v匹配的点 v是右 match[v]是左 visit[]标记右点是否被访问过
int n, m, k;
int dfs(int u)
{
    for (auto v : g[u])
    {
        if (visit[v]) continue;
        visit[v]++;
        if (!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int main()
{
    cin >> n >> m >> k;
    int a, b;
    while (k--)
    {
        cin >> a >> b;
        g[a].push_back(b);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(visit, 0, sizeof(visit));
        if (dfs(i))ans++;
    }
    cout << ans;
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
//#define int long long

const int N = 3e5 + 5;
const int mod = 998244353;

int n, m;
int d[N];
vector<int> mat[N];
int s[N];
int dp[N];
int dfs(int cur)
{
    s[cur] = 1;
    for (auto nxt : mat[cur]) {
        s[cur] += dfs(nxt); 
    }
    
    return s[cur];
}
int f(int cur)
{
    if(mat[cur].size()==0){
        return 0;
    }
    int first = 0;
    vector<int> tem;
    for (auto i : mat[cur])
    {
        int ttt = dfs(i);
        first += ttt;
        tem.push_back(ttt);
    }
    int second = 0;
    if(tem.size()>=2){
        second = 1;
        for(auto i:tem){
            second *= i;
        }
    }
    int third = s[cur]-mat[cur].size();
    return first + second + third;
}

void solve()
{
    cin >> n;
    int u, v;
    for (int i = 1; i <= n;i++){
        cin >> u >> v;
        mat[u].push_back(v);
        d[v]++;
    }
    int s;
    for (int i = 1; i <= n;i++){
        if(d[i]==0){
            s = i;
            break;
        }
    }
    int dots = dfs(s);
    cout << f(s);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    // cin>>tt;
    for (int i = 1; i <= tt;i++){
        solve();
    }
    return 0;
}

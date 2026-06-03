#include<bits/stdc++.h>

using namespace std;
//#define int long long

const int N = 2e5 + 5;
const int mod = 998244353;

int n, m;
int dp[N];
int v[N], w[N], cnt[N];
//dp[i][j]=max(dp[i-1][j-x*w[i]]+x*v[i])  (0-cnt[i])

void solve(){
    cin >> n >> m;
    for (int i = 1; i <= n;i++)
        cin >> v[i] >> w[i] >> cnt[i];
    for (int i = 1; i <= n;i++){
        for (int j = w[i]; j <=m;j++){
            for (int x = 0; x <= cnt[i];x++){
                dp[j] = max(dp[j], dp[j - x * w[i]] + x * v[i]);
            }
        }
    }
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

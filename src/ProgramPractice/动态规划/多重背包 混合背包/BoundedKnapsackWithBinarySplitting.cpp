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
    int c = 0;
    int vv, ww, ccnt;
    for (int i = 1; i <= n; i++)
    {
        cin >> vv >> ww >> ccnt;
        for (int j = 1;ccnt-j>=0;j<<=1){
            v[++c] = j * vv;
            w[c] = j * ww;
            ccnt -= j;
        }
        if(ccnt){
            v[++c] = ccnt * vv;
            w[c] = ccnt * ww;
        }
    }
    for (int i = 1; i <= c;i++){
        for (int j = m; j >=0;j--){
            if(j-w[i]>=0)
                dp[j] = max(dp[j], dp[j -w[i]] + v[i]);
            
        }
    }
    cout<<dp[m];
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

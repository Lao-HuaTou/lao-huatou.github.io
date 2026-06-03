#include<bits/stdc++.h>

using namespace std;
//#define int long long

const int N = 2e5 + 5;
//const int mod = 998244353;

int n, m;
int dp[N];
int v[N], w[N], cnt[N];
//dp[i][j]=max(dp[i-1][j-x*w[i]]+x*v[i])  (0-cnt[i])

int q[N];
int d[N][N];
int value(int i,int j){
    return d[i-1][j] - j / w[i] * v[i];
}
void solve1()
{
    cin >> n >> m;
    for (int i = 1; i <= n;i++)
        cin >> v[i] >> w[i] >> cnt[i];
    for (int i = 1; i <= n;i++){
        for (int mod = 0; mod <= min(m, w[i] - 1);mod++){
            int l = 0, r = 0;
            for (int j = mod; j <= m; j += w[i])
            {
                while(l<r&&value(i,q[r-1])<=value(i,j)){
                    r--;
                }
                q[r++] = j;
                if(q[l]==j-(cnt[i]+1)*w[i]){
                    l++;
                }
                d[i][j] = value(i, q[l]) + j / w[i] * v[i];

            }
        }
    }
    cout << d[n][m];
}
int value2(int i,int j){
    return dp[j] - j / w[i] * v[i];
}
void solve2(){
    cin >> n >> m;
    for (int i = 1; i <= n;i++)
        cin >> v[i] >> w[i] >> cnt[i];
    for (int i = 1; i <= n;i++){
        for (int mod = 0; mod <= min(m, w[i] - 1);mod++){
            int l = 0, r = 0;
            int c = 1;
            for (int j = m - mod; j >= 0 && c <= cnt[i];j-=w[i],c++){
                while(l<r&&value2(i,q[r-1])<=value2(i,j)){
                    r--;
                }
                q[r++] = j;
            }//先放入 买0 - (cnt[i]-1) 的
            for (int j = m - mod, enter = m-mod-cnt[i]*w[i]; j >= 0;j-=w[i],enter-=w[i]){
                if(enter>=0){
                    while(l<r&&value2(i,q[r-1])<=value2(i,enter)){
                        r--;
                    }
                    q[r++] = enter;
                    
                }
                dp[j] = value2(i, q[l]) + j / w[i] * v[i];
                if(q[l]==j){
                    l++;
                }
            }
        }
    }
    cout << dp[m];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    // cin>>tt;
    for (int i = 1; i <= tt;i++){
        solve2();
    }
    return 0;
}

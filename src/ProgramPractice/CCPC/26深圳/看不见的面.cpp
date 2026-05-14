#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
const int N = 2e3;
int mat[2][N];
int n, m;
int mpow(int x,int c){
    int res = 1;
    while(c){
        if(c&1)
            res = (res * x) % mod;
        x = (x * x) % mod;
        c >>= 1;
    }
    return res;
}

void solve()
{
    cin >> n >> m;
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        mat[0][i] = 2 << (i - 1);
    }
    for (int c = 1; c <= m;c++){
        for (int i = 1; i <= n; i++, k ^= 1)
        {
            mat[k][i] = mat[k][i - 1] + 2 * mat[k ^ 1][i - 1];
        }
    }
    cout << mat[k ^ 1][n];
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    // cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}

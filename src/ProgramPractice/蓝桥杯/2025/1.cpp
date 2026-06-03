#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e6 + 5;
const int mod = 1e9+7;
vector<int> a(N);
int n, m;
int chengjie[2500];
int inv[2500];
int qpow(int a, int b)
{
    int res = 1;
    while(b){
        if(b&1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
void solve()
{
    cout << (qpow(2, 2021) + qpow(2, 4042)) % mod;
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

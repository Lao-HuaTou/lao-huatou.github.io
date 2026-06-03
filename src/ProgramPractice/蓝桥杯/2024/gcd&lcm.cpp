#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
const int mod = 998244353;
int qpow(int a,int b){
    int res = 1;
    while(b){
        if(b&1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
int x, y, n;
vector<int> v;
void solve()
{
    cin >> x >> y >> n;
    int t = y / x;
    int q = 2;
    v.clear();
    while (q * q <= t)
    {
        if(t%q==0){
            v.push_back(0);
            while(t%q==0){
                v.back()++;
                t /= q;
            }
        }
        else
            q++;
    }
    if(t>1){
        v.push_back(1);
    }
    int ans = 0;
    for (auto i : v)
    {
        ans = (ans * (qpow(i + 1, n) - 2 * qpow(i, n) + qpow(i - 1, n)) % mod) % mod;
    }
    cout << (ans + mod) % mod << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin>>tt;
    for (int i = 1; i <= tt;i++){
        solve();
    }
    return 0;
}

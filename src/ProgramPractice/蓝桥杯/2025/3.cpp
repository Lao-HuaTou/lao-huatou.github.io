#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e6 + 5;
const int mod = 998244353;

int n, m;
int ar[N];
int vis[N];
void solve()
{
    cin>>n;
    map<int, int> a;

    ar[0] = -1;
    int pre = -1;
    for (int i = 1; i <= n; i++){
        cin >> ar[i];
        if(ar[i]!=pre){
            if(vis[ar[i]]){
                a[ar[i]]++;
            }
            else{
                vis[ar[i]] = 1;
                a[ar[i]] = 1;
            }
        }
        pre = ar[i];
    }
    int ans = 1e18;
    for (auto i : a)
    {
        int v=i.first;
        int cnt=0;
        if(v==ar[1])cnt++;
        if(v==ar[n])cnt++;
        ans = min(ans, i.first * (i.second-cnt+1));
    }
    cout << ans;
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

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;

struct node
{
    int x, d, w;
    bool operator<(const node&o)const{
        return x < o.x;
    }
}an[N];
int n;
int l;
void solve()
{
    int cnt = 0;
    cin >> n >> l;
    for (int i = 0; i < n;i++){
        cin >> an[i].x >> an[i].d >> an[i].w;
        if(an[i].d==0)
            cnt++;
    }
    sort(an, an + n);
    int ans = 0;
    for (int i = 0; i < cnt;i++){
        ans += an[i].w;
    }
    cout << ans << endl;
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

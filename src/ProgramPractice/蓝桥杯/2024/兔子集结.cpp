#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
int n;
struct node
{
    int p;
    int id;
} a[N];
bool cmp1(const node &a, const node &b)
{
    return a.p < b.p;
}
bool cmp2(const node&a,const node &b){
    return a.id < b.id;
}
int f[N];
void solve()
{
    cin >> n;
    for (int i = 1; i <= n;i++)
        f[i] = i;
    f[1] = 2;
    f[n] = n - 1;
    int tem;
    for (int i = 1; i <= n; i++)
    {
        cin >> tem;
        a[i] = {tem, i};
    }
    sort(a, a + n,cmp1);
    for (int i = 2; i <= n - 1;i++){
        if(a[i].p-a[i-1].p<=a[i+1].p-a[i].p){
            f[i] = i - 1;
        
        }
        else
            f[i] = i + 1;
    }
    for (int i = 1; i <= n - 1;i++)
    {
        if(f[i]==i+1&&f[i+1]==i){
            f[i] = i;
            f[i + 1] = i + 1;
            a[i].p = a[i+1].p = (a[i].p + a[i + 1].p) >> 1;
        }
    }
    for (int i = 1; i <= n;i++){
        if(f[i]!=i){
            a[i].p = a[f[i]].p;
        }
    }
    sort(a + 1, a + 1 + n, cmp2);
    for (int i = 1; i <= n;i++)
        cout << a[i].p<<" ";
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

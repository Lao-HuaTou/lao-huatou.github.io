#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+5;
int p[N];
int s[N];
int n, q;
int id[N];
int total;
void build(int n)
{
    for (int i = 1; i <= n;i++){
        p[i] = i;
        s[i] = 1;
    }
}
int find(int x){
    if(p[x]==x)
        return x;
    return p[x] = find(p[x]);
}
void merge(int x,int y){
    int rx = find(x);
    int ry = find(y);
    if(rx!=ry){
        p[rx] = ry;
        s[ry] += s[rx];
    }
}
void del(int x){
    int cc = id[x];
    int rx = find(cc);
    int size = s[rx];
    if(size==1)
        return;
    s[rx]--;
    id[cc] = ++total;
    s[cc] = 1;
    p[cc] = total;
}
void solve()
{
    cin >> n >> q;
    total = n;
    int op;
    int x, y;
    while(q--){
        cin >> op;
        if(op==1){
            cin >> x >> y;
            merge(x, y);
        }
        else if(op==2){
            cin >> x;
            del(x);
        }
        else if(op==3){
            cin >> x >> y;
            if(find(x)==find(y)){
                cout << "Yes\n";
            }
            else
                cout << "No\n";
        }
        else {
            cin >> x;
            cout << s[find(x)] << "\n";
        }
    }
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

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
const int N = 1e5 + 5;
string x, y;
void solve()
{
    cin >> x >> y;
    string tx="", ty="";
    int c = 0;
    for (int i = 0; i < x.length(); i++)
    {
        if(x[i]=='1')
            c++;
        tx += c & 1 ? '1' : '0';
    }
    c = 0;
    for (int i = 0; i < y.length();i++){
        if(y[i]=='1'){
            c++;
        }
        ty += c & 1 ? '1' : '0';
    }
    cout << " x " << x << " y " << y << endl;
    cout << " tx" << tx << " ty " << ty;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}
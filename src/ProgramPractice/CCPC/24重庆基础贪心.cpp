#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[13];
int ans=1;
const int mod = 998244353;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;

    while(T--){
        for (int i = 1; i <= 9;i++){
            cin >> a[i];
        }
        while(!a[1]&&!a[2]){
            a[1]--;
            a[2]--;
            a[3]++;

        }
        a[3] += (a[1] / 3);
        a[1] /= 3;
        if(a[1]==1){
            for (int i = 2; i <= 9;i++){
                if(a[i]){
                    a[i+1]++;
                    a[i]--;
                }
            }
        }
        else if(a[1]==2){
            a[2]++;
        }
        for (int i = 2; i <= 10;i++){
            for (int j = 1; j <= a[i];j++){
                ans = ans * i % mod;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
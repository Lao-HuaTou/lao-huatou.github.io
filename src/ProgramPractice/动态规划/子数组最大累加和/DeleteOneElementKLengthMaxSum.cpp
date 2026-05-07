#include<bits/stdc++.h>
//#define int long long

using namespace std;
const int mod = 98244353;
const int N = 1e5 + 5;
const int M = 1e5;
int n, k;
int ar[N];
int q[N];
int l, r;

int solve(){
    if (n <= k) {
        return 0;
    }
    
    l = 1; r = 1;
    long long sum = 0,ans = 0;
    for (int i = 1; i <= n; i++)
    {
        //单调队列 维护k长度内的最小值
        while(l<r && ar[i] <= ar[q[r-1]])
        {
            r--;
        }
        q[r++] = i;
        sum += ar[i];
        if(i>=k+1){
            ans = max((long long)ans, sum - ar[q[l]]);
           
            sum -= ar[i - k];
            if(i-q[l]==k){
                l++;
            }
        }
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    if(cin>>n>>k){
        for (int i = 1; i <= n;i++)
            cin >> ar[i];
        cout << solve() << endl;
    }
    return 0;
}
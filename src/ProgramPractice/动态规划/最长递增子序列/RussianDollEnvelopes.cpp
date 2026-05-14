#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
struct node{
    int x, y;
    bool operator<(const node&o)const{
        if(x==o.x)
            return y > o.y;
        return x < o.x;
    }
}e[N];
int dp[N], tail[N];
int n;
int ans = 0;
void lengthofLIS(){
    for (int i = 0; i < n;i++){
        int *it = lower_bound(tail, tail + ans, e[i].y);
        if(it==tail+ans){
            tail[ans++] = e[i].y;
        }
        else
            *it = e[i].y;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n;i++){
        cin >> e[i].x >> e[i].y;
    }
    sort(e, e + n);
    lengthofLIS();
    cout << ans;
    return 0;
}

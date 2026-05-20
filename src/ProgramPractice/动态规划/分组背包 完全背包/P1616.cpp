// 完全背包(模版)
// 给定一个正数t，表示背包的容量
// 有m种货物，每种货物可以选择任意个
// 每种货物都有体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1616
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e7 + 5;
int t, m;
int c[10005];
int v[10005];
int dp[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t >> m;
    for (int i = 1; i <= m;i++){
        cin >> c[i] >> v[i];
    }
    for (int i = 1; i <= m;i++){
        for (int j = c[i]; j <= t;j++){
            dp[j] = max(dp[j], dp[j - c[i]] + v[i]); // dp[i][j]=max(dp[i][j],dp[i][j-c[i]]+v[i]);
        }
    }
    cout << dp[t];
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int dp[N];//以i结尾的最长子数组
int tail[N];//长度为i的LIS最后一位数
int n;
int a[N];

int lengthofLIS1(){
    int ans = 0;
    for (int i = 0; i < n;i++){
        dp[i] = 1;
        for (int j = 0; j < n;j++){
            if(a[j]<a[i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// 最优解
// 时间复杂度O(n * logn)
// 如果要求最长不下降子序列 (Non-Decreasing)，只需将 lower_bound 换成 upper_bound
// 核心逻辑：ends 数组保持不降序，使用 upper_bound 找到第一个 > num 的位置并替换
int lengthofLIS2(){
    int len = 0;
    for (int i = 0; i < n; i++) {
        // upper_bound 在 [0, len) 范围内找第一个 > nums[i] 的迭代器
        int* it = upper_bound(tail, tail+len, a[i]);
        if (it == tail + len) {
            tail[len++] = a[i];
        } else {
            *it = a[i];
        }
    }
    return len;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
}
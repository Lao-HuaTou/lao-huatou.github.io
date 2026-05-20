#include <iostream>
#include <algorithm>

using namespace std;

// 根据 LeetCode 规模：石头数量不超过 30，每块石头重量不超过 100
// 最大总重量为 3000，背包容量 sum / 2 最大为 1500
const int MAXN = 105;
const int MAXT = 3005;

int nums[MAXN];
int dp[MAXT];
int n;

// 非负数组nums中，子序列累加和不超过t，但是最接近t的累加和是多少
// 01背包问题(子集累加和尽量接近t) + 空间压缩
int near(int t) {
    for (int i = 0; i <= t; i++) {
        dp[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        for (int j = t; j >= num; j--) {
            // dp[i][j] = Math.max(dp[i-1][j], dp[i-1][j-nums[i]]+nums[i])
            dp[j] = max(dp[j], dp[j - num] + num);
        }
    }
    return dp[t];
}

int lastStoneWeightII() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    // nums中随意选择数字
    // 累加和一定要 <= sum / 2
    // 又尽量接近
    int near_val = near(sum / 2);
    return sum - near_val - near_val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        cout << lastStoneWeightII() << "\n";
    }

    return 0;
}
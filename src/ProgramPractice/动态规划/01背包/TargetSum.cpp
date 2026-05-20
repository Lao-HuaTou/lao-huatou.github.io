#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std;

// 目标和 - ACM 风格全解法版
const int MAXN = 35;       // 根据力扣数据规模，N <= 20
const int MAXM = 3005;     // 累加和最大在 1000 左右，2 * s + 1 足够

int nums[MAXN];
int n, target_val;

// ==================== 解法 1：普通尝试，暴力递归版 ====================
int f1(int i, int sum) {
    if (i == n) {
        return sum == target_val ? 1 : 0;
    }
    return f1(i + 1, sum + nums[i]) + f1(i + 1, sum - nums[i]);
}

int findTargetSumWays1() {
    return f1(0, 0);
}


// ==================== 解法 2：普通尝试，记忆化搜索版 ====================
// 因为累加和可以为负数，缓存动态规划表用哈希表
unordered_map<int, unordered_map<int, int>> dp_memo;

int f2(int i, int j) {
    if (i == n) {
        return j == target_val ? 1 : 0;
    }
    if (dp_memo.count(i) && dp_memo[i].count(j)) {
        return dp_memo[i][j];
    }
    int ans = f2(i + 1, j + nums[i]) + f2(i + 1, j - nums[i]);
    dp_memo[i][j] = ans;
    return ans;
}

int findTargetSumWays2() {
    dp_memo.clear(); // 别忘了多组数据时清空缓存
    return f2(0, 0);
}


// ==================== 解法 3：普通尝试，严格位置依赖的动态规划（平移技巧） ====================
int dp3[MAXN][MAXM];

int findTargetSumWays3() {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += nums[i];
    }
    if (target_val < -s || target_val > s) {
        return 0;
    }
    // -s ~ +s -> 2 * s + 1
    int m = 2 * s + 1;
    
    // 初始化 dp 表
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) dp3[i][j] = 0;
    }
    
    // 原本的 dp[n][target] = 1，平移！
    dp3[n][target_val + s] = 1;
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = -s; j <= s; j++) {
            if (j + nums[i] + s < m) {
                // 原本是 : dp[i][j] = dp[i + 1][j + nums[i]] -> 平移！
                dp3[i][j + s] = dp3[i + 1][j + nums[i] + s];
            }
            if (j - nums[i] + s >= 0) {
                // 原本是 : dp[i][j] += dp[i + 1][j - nums[i]] -> 平移！
                dp3[i][j + s] += dp3[i + 1][j - nums[i] + s];
            }
        }
    }
    // 原本应该返回 dp[0][0] -> 平移返回 dp[0][s]
    return dp3[0][s];
}


// ==================== 解法 4：新思路，转化为 01 背包问题 ====================
int dp4[MAXM];

// 求非负数组nums有多少个子序列累加和是t
// 01背包问题(子集累加和严格是t) + 空间压缩
int subsets(int t) {
    if (t < 0) {
        return 0;
    }
    for (int i = 0; i <= t; i++) dp4[i] = 0;
    dp4[0] = 1;
    
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        for (int j = t; j >= num; j--) {
            dp4[j] += dp4[j - num];
        }
    }
    return dp4[t];
}

// 思考1: 即使nums中有负数，也可以直接变正数，不影响结果
// 思考2: 如果target > sum，直接返回0
// 思考3: 数组不管怎么加减，最终结果奇偶性不变。若sum与target奇偶性不同，直接返回0
// 思考4(最重要): sum(A) - sum(B) = target -> 2 * sum(A) = target + sum -> sum(A) = (target + sum) / 2
int findTargetSumWays4() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        nums[i] = abs(nums[i]); // 保证思考1的鲁棒性
        sum += nums[i];
    }
    if (sum < abs(target_val) || ((target_val & 1) ^ (sum & 1)) == 1) {
        return 0;
    }
    return subsets((target_val + sum) >> 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (cin >> n >> target_val) {
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        
        // 默认调用最优的解法 4，你想测哪个就换成哪个函数
        cout << findTargetSumWays4() << "\n";
    }

    return 0;
}
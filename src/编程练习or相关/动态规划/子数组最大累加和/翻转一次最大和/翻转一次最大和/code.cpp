#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>

using namespace std;

// 可以翻转1次的情况下子数组最大累加和
// 给定一个数组nums，
// 现在允许你随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 返回必须随意翻转1次之后，子数组的最大累加和
// 对数器验证

const int MAXN = 100005;
int start_dp[MAXN]; // start[i] : 所有必须以i开头的子数组中，最大累加和是多少

// 返回子数组最大累加和 (基础 Kadane 算法)
int maxSum(const vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    int ans = nums[0];
    for (int i = 1, pre = nums[0]; i < n; i++) {
        pre = max(nums[i], pre + nums[i]);
        ans = max(ans, pre);
    }
    return ans;
}

// 暴力方法 - 用于验证
void reverse_range(vector<int>& nums, int l, int r) {
    while (l < r) {
        swap(nums[l++], nums[r--]);
    }
}

int maxSumReverse1(vector<int>& nums) {
    int n = nums.size();
    int ans = INT_MIN;
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            reverse_range(nums, l, r);
            ans = max(ans, maxSum(nums));
            reverse_range(nums, l, r); // 还原
        }
    }
    return ans;
}

// 正式方法 - O(n)
int maxSumReverse2(const vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // start_dp[i] : 所有必须以i开头的子数组中，最大累加和
    start_dp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        start_dp[i] = max(nums[i], nums[i] + start_dp[i + 1]);
    }

    int ans = start_dp[0];
    int end_val = nums[0];    // 子数组必须以i-1结尾的最大累加和
    int maxEnd = nums[0]; // 0~i-1范围内，以任意位置结尾的所有子数组中最大的累加和

    for (int i = 1; i < n; i++) {
        // 枚举划分点 i
        // 翻转的效果可以将 0...i-1 中的某个最大结尾段 
        // 和 i...n-1 中的某个最大开始段 拼在一起
        ans = max(ans, maxEnd + start_dp[i]);

        // 更新以 i 结尾的最大累加和
        end_val = max(nums[i], end_val + nums[i]);
        // 更新 0...i 范围内最大的以某个位置结尾的累加和
        maxEnd = max(maxEnd, end_val);
    }
    ans = max(ans, maxEnd);
    return ans;
}

// 为了测试
vector<int> randomArray(int n, int v) {
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = (rand() % (v * 2 + 1)) - v;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr));

    int n = 50;
    int v = 200;
    int testTime = 20000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int len = (rand() % n) + 1;
        vector<int> arr = randomArray(len, v);
        int ans1 = maxSumReverse1(arr);
        int ans2 = maxSumReverse2(arr);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
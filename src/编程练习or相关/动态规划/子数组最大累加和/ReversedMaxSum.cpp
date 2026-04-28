#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long long maxSubarraySumWithOneReverse(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    // leftMax[i] 表示从左往右看，[0...i] 范围内的最大子数组累加和
    vector<long long> leftMax(n);
    long long currentMax = LLONG_MIN;
    long long maxSoFar = LLONG_MIN;

    for (int i = 0; i < n; ++i) {
        // 标准 Kadane 算法：以 i 结尾的最大和
        if (currentMax < 0) {
            currentMax = nums[i];
        } else {
            currentMax += nums[i];
        }
        maxSoFar = max(maxSoFar, currentMax);
        leftMax[i] = maxSoFar;
    }

    // rightMax[i] 表示从右往左看，[i...n-1] 范围内的最大子数组累加和
    vector<long long> rightMax(n);
    currentMax = LLONG_MIN;
    maxSoFar = LLONG_MIN;

    for (int i = n - 1; i >= 0; --i) {
        if (currentMax < 0) {
            currentMax = nums[i];
        } else {
            currentMax += nums[i];
        }
        maxSoFar = max(maxSoFar, currentMax);
        rightMax[i] = maxSoFar;
    }

    // 结果至少是原数组的最大子数组和（即不翻转，或者翻转一个不影响结果的区间）
    long long result = leftMax[n - 1];

    // 关键步骤：遍历分割点 i，将左边最大的一段和右边最大的一段拼起来
    // 翻转操作本质上可以把不相邻的两段拼成相邻的一段
    for (int i = 0; i < n - 1; ++i) {
        result = max(result, leftMax[i] + rightMax[i + 1]);
    }

    return result;
}

int main() {
    // 测试用例
    vector<int> nums = {5, -10, 6, -2, 7, -10, 4};
    cout << "最大累加和: " << maxSubarraySumWithOneReverse(nums) << endl; 
    // 输出应该是 16 (即 5 + [6, -2, 7] 的结果)
    return 0;
}

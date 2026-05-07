#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 最接近目标值的子序列和
// 给你一个整数数组 nums 和一个目标值 goal
// 你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal
// 也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal)
// 返回 abs(sum - goal) 可能的 最小值
// 注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。
// 数据量描述:
// 1 <= nums.length <= 40
// -10^7 <= nums[i] <= 10^7
// -10^9 <= goal <= 10^9
// 测试链接 : https://leetcode.cn/problems/closest-subsequence-sum/
class Code03_ClosestSubsequenceSum {
public:
    static const int MAXN = 1 << 20;

    int lsum[MAXN];

    int rsum[MAXN];

    int fill;

    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        long long min_val = 0;
        long long max_val = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) {
                max_val += nums[i];
            }
            else {
                min_val += nums[i];
            }
        }
        if (max_val < goal) {
            return (int)abs(max_val - goal);
        }
        if (min_val > goal) {
            return (int)abs(min_val - goal);
        }
        // 原始数组排序，为了后面递归的时候，还能剪枝
        // 常数优化
        sort(nums.begin(), nums.end());
        fill = 0;
        collect(nums, 0, n >> 1, 0, lsum);
        int lsize = fill;
        fill = 0;
        collect(nums, n >> 1, n, 0, rsum);
        int rsize = fill;
        sort(lsum, lsum + lsize);
        sort(rsum, rsum + rsize);
        long long ans = abs((long long)goal);
        for (int i = 0, j = rsize - 1; i < lsize; i++) {
            while (j > 0 && abs((long long)goal - lsum[i] - rsum[j - 1]) <= abs((long long)goal - lsum[i] - rsum[j])) {//移了更小
                j--;
            }
            //1 1 1 1 1 2 2...
            //i         j
            ans = min(ans, (long long)abs((long long)goal - lsum[i] - rsum[j]));
        }
        return (int)ans;
    }

    void collect(const vector<int>& nums, int i, int e, int s, int sum[]) {//数组  l  r  carry
        if (i == e) {
            sum[fill++] = s;
        }
        else {
            // nums[i.....]这一组，相同的数字有几个
            int j = i + 1;
            while (j < e && nums[j] == nums[i]) {
                j++;
            }
            // nums[ 1 1 1 1 1 2....
            //       i         j
            for (int k = 0; k <= j - i; k++) {
                // k = 0个
                // k = 1个
                // k = 2个
                collect(nums, j, e, s + k * nums[i], sum);
            }
        }
    }
};
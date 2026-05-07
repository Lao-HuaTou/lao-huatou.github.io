#include <vector>
#include <algorithm>

using namespace std;

// 三个无重叠子数组的最大和
// 给你一个整数数组 nums 和一个整数 k
// 找出三个长度为 k 、互不重叠、且全部数字和（3 * k 项）最大的子数组
// 并返回这三个子数组
// 以下标的数组形式返回结果，数组中的每一项分别指示每个子数组的起始位置
// 如果有多个结果，返回字典序最小的一个
// 测试链接 : https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/
class Code04_MaximumSum3UnoverlappingSubarrays {
public:
    static vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // sums[i] : 以i开头并且长度为k的子数组的累加和
        // 使用 static 数组处理大数据量
        static int sums[20001];
        for (int l = 0, r = 0, sum = 0; r < n; r++) {
            // l....r
            sum += nums[r];
            if (r - l + 1 == k) {
                sums[l] = sum;
                sum -= nums[l];
                l++;
            }
        }

        // prefix[i] :
        // 0~i范围上所有长度为k的子数组中，拥有最大累加和的子数组，是以什么位置开头的
        static int prefix[20001];
        // 初始化第一个长度为k的子数组开头为0
        prefix[k - 1] = 0;
        for (int l = 1, r = k; r < n; l++, r++) {
            if (sums[l] > sums[prefix[r - 1]]) {
                // 注意>，为了同样最大累加和的情况下，最小的字典序
                prefix[r] = l;
            }
            else {
                prefix[r] = prefix[r - 1];
            }
        }

        // suffix[i] :
        // i~n-1范围上所有长度为k的子数组中，拥有最大累加和的子数组，是以什么位置开头的
        static int suffix[20001];
        suffix[n - k] = n - k;
        for (int l = n - k - 1; l >= 0; l--) {
            if (sums[l] >= sums[suffix[l + 1]]) {
                // 注意>=，为了同样最大累加和的情况下，最小的字典序
                suffix[l] = l;
            }
            else {
                suffix[l] = suffix[l + 1];
            }
        }

        int a = 0, b = 0, c = 0, max_total = 0;
        // 0...i-1    i...j    j+1...n-1
        //    左      中(长度为k)      右
        for (int p, s, i = k, j = 2 * k - 1, current_sum; j < n - k; i++, j++) {
            // 0.....i-1   i.....j  j+1.....n-1
            // 最好开头p      i开头      最好开头s
            p = prefix[i - 1];
            s = suffix[j + 1];
            current_sum = sums[p] + sums[i] + sums[s];
            if (current_sum > max_total) {
                // 注意>，为了同样最大累加和的情况下，最小的字典序
                max_total = current_sum;
                a = p;
                b = i;
                c = s;
            }
        }
        return { a, b, c };
    }
};
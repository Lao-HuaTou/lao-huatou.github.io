#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 删掉1个数字后长度为k的子数组最大累加和 
// 1 <= n <= 10^5 (根据常见题型设定 MAXN)
const int MAXN = 100005;

// 单调队列数组
int q[MAXN];
int l, r;

// 正式方法 - 时间复杂度 O(N)
// 核心思想：维护一个长度为 k+1 的窗口，删掉窗口内最小值，剩下的 k 个数累加和最大
int maxSum2(const vector<int>& nums, int k) {
    int n = nums.size();
    if (n <= k) return 0;

    l = 0; r = 0; // 重置单调队列头尾指针
    long long sum = 0;
    int ans = INT_MIN;

    for (int i = 0; i < n; i++) {
        // 单调队列：维持窗口内最小值的索引，队列内元素对应的数值单调递增
        while (l < r && nums[q[r - 1]] >= nums[i]) {
            r--;
        }
        q[r++] = i;
        sum += nums[i];

        // 窗口长度达到 k + 1 (索引范围 i-k 到 i)
        if (i >= k) {
            // 当前窗口累加和减去窗口内的最小值
            ans = max(ans, (int)(sum - nums[q[l]]));
            
            // 如果单调队列头部的索引即将过期（不在下一个 k+1 窗口内）
            if (q[l] == i - k) {
                l++;
            }
            // 减去窗口最左侧的元素，为下一次移动做准备
            sum -= nums[i - k];
        }
    }
    return ans;
}

// 为了测试
vector<int> randomArray(int n, int v) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = (rand() % (2 * v + 1)) - v;
    }
    return res;
}

int main() {
    // 标准 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_limit = 200;
    int v_limit = 1000;
    int testTimes = 10000;

    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++) {
        int len = (rand() % n_limit) + 1;
        vector<int> nums = randomArray(len, v_limit);
        int k = (rand() % n_limit) + 1;
        
        int ans1 = maxSum1(nums, k);
        int ans2 = maxSum2(nums, k);
        
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;

    return 0;
}

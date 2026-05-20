#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
 * 【题目简介】：非负数组前k个最小的子序列累加和
 * 给定一个数组nums，含有n个数字，都是非负数
 * 给定一个正数k，返回所有子序列中累加和最小的前k个累加和
 * 子序列是包含空集的
 * * 【数据范围】：
 * 1 <= n <= 10^5
 * 1 <= nums[i] <= 10^6
 * 1 <= k <= 10^5
 * 注意这个数据量，用01背包的解法是不行的，时间复杂度太高了
 */

const int N = 100005;


// ==================== 解法 1：暴力方法 (用于小规模验证) ====================
// 得到所有子序列的和
void f1(int index, long long sum, vector<long long>& allSubsequences) {
    if (index == n) {
        allSubsequences.push_back(sum);
    } else {
        f1(index + 1, sum, allSubsequences);
        f1(index + 1, sum + nums[index], allSubsequences);
    }
}

void topKSum1() {
    vector<long long> allSubsequences;
    f1(0, 0, allSubsequences);
    sort(allSubsequences.begin(), allSubsequences.end());
    for (int i = 0; i < k; i++) {
        ans_arr[i] = allSubsequences[i];
    }
}


// ==================== 解法 2：01背包来实现 (数据量大时不可行) ====================
// 这种方法此时不是最优解，因为n很大，数值也很大，那么可能的累加和就更大，时间复杂度太差
void topKSum2() {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    
    // 动态分配大数组，规避栈溢出，模拟 Java 的 int[] dp = new int[sum + 1];
    // 注意：如果数据量达到 10^5 * 10^6，此处的 sum 会引发 MLE，仅限规模较小时测试
    vector<int> dp(sum + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        long long num = nums[i];
        for (long long j = sum; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    
    int index = 0;
    for (long long j = 0; j <= sum && index < k; j++) {
        for (int i = 0; i < dp[j] && index < k; i++) {
            ans_arr[index++] = j;
        }
    }
}


// ==================== 解法 3：正式方法 (用堆来做是最优解) ====================
// 时间复杂度 O(n * log n) + O(k * log k)
struct node{
    int id;
    int sum;
    bool operator<(const node& o)const{
        return sum > o.sum;
    }
} e[N];
int n,k;
int nums[N];
int ans_arr[N];
int ansc = 1;
priority_queue<node> q;
void topKSum3()
{
    sort(nums, nums + n);
    q.push({0, nums[0]});
    ans_arr[0] = 0;
    while (ansc < k)
    {
        int id = q.top().id;
        int cur = q.top().sum;
        q.pop();
        ans_arr[ansc++] = cur;
        if(id+1<n){
        q.push({ id + 1, cur + nums[id + 1] });
        q.push({ id + 1, cur + nums[id + 1] - nums[id] });
        }
    }
    return;
}

int main() {
    // 极致 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 支持多组输入直到 EOF
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }

        // 默认调用最优的解法 3
        topKSum3();

        // 输出前 k 个最小的累加和
        for (int i = 0; i < k; i++) {
            cout << ans_arr[i] << (i == k - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
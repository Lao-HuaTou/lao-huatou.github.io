#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        deque<int> dq; // 单调队列：保存索引，对应arr值单调递减
        for (int i = 0; i < n && k > 0; ++i) {
            // 移除超出窗口左边界的元素（窗口范围：[i, i+k]）
            while (!dq.empty() && dq.front() < i) {
                dq.pop_front();
            }
            // 窗口右边界
            int end = min(i + k, n - 1);
            // 将窗口内新元素加入单调队列（维护递减性）
            for (int j = (dq.empty() ? i : dq.back() + 1); j <= end; ++j) {
                while (!dq.empty() && arr[j] >= arr[dq.back()]) {
                    dq.pop_back();
                }
                dq.push_back(j);
            }
            // 队列首元素是窗口内最大值的位置
            int pos = dq.front();
            // 移动元素到i位置
            int val = arr[pos];
            for (int j = pos; j > i; --j) {
                arr[j] = arr[j - 1];
            }
            arr[i] = val;
            // 消耗操作次数
            k -= (pos - i);
            // 重置队列（数组已修改，需重新维护）
            dq.clear();
        }

        // 输出结果
        for (int num : arr) {
            cout << num << " ";
        }
        cout << "\n";
    }

    return 0;
}
// 伪代码思路
// 1. 将所有数值及其原始下标存入 map 或 优先队列（按数值大、下标小排序）
// 2. 遍历数组位置 i 从 1 到 n:
//    - 如果 k == 0，结束
//    - 寻找当前未被使用的最大值
//    - 如果这个最大值就在位置 i，跳过（不消耗 k）
//    - 如果不在，消耗 1 次 k，把这个最大值标记为“已移动到前面”
// 3. 最后输出：先输出被移动的 k 个大数（降序），再输出剩下的数（保持原相对顺序）

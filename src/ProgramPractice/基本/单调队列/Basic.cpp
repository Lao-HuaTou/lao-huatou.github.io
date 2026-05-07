#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;

int n, k;
int arr[MAXN];
int q[MAXN]; // 存储的是下标，方便判断是否过期
int head, tail; // 队头和队尾指针 [head, tail)

void solve() {
    head = tail = 0; // 初始化
    
    for (int i = 0; i < n; i++) {
        // 1. 入队准备：如果新元素比队尾元素大，队尾元素永远不可能成为最大值，弹出
        // 维护单调递减队列 (队头是最大值)
        while (head < tail && arr[q[tail - 1]] <= arr[i]) {
            tail--;
        }
        
        // 2. 入队：存储下标
        q[tail++] = i;
        
        // 3. 检查过期：如果队头下标超出了窗口范围 [i-k+1, i]，弹出
        if (q[head] == i - k) {
            head++;
        }
        
        // 4. 结算：当窗口形成（i >= k-1）时，队头就是当前窗口最值
        if (i >= k - 1) {
            // arr[q[head]] 即为当前窗口最大值
            // printf("%d ", arr[q[head]]);
        }
    }
}
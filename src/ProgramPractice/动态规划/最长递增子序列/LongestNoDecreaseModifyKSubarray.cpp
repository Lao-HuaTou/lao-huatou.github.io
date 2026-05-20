#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;

int arr[MAXN];
int right_dp[MAXN];
int ends_arr[MAXN];
int n, k;
void compute_right() {
    int len = 0;
    for (int i = n - 1; i >= 0; i--) {
        // 在降序数组中，使用 upper_bound 配合 greater<int>() 可以直接找到第一个 < arr[i] 的位置
        int* it = upper_bound(ends_arr, ends_arr + len, arr[i], greater<int>());
        
        if (it == ends_arr + len) {
            ends_arr[len++] = arr[i];
            right_dp[i] = len;
        } else {
            *it = arr[i];
            right_dp[i] = (it - ends_arr) + 1;
        }
    }
}

int compute() {
    compute_right();
    int len = 0;
    int ans = 0;

    for (int i = 0, j = k; j < n; i++, j++) {
        int* it = upper_bound(ends_arr, ends_arr + len, arr[j]);
        int left = (it == ends_arr + len) ? len : (it - ends_arr);
        ans = max(ans, left + k + right_dp[j]);

        it = upper_bound(ends_arr, ends_arr + len, arr[i]);
        if (it == ends_arr + len) {
            ends_arr[len++] = arr[i];
        } else {
            *it = arr[i];
        }
    }

    ans = max(ans, len + k);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        if (k >= n) {
            cout << n << "\n";
        } else {
            cout << compute() << "\n";
        }
    }

    return 0;
}
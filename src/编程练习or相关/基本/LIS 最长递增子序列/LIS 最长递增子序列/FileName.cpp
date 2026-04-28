#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
vector<int>q;
int n;
int cnt = 0;
int main() {
    cin >> n;
    vector<int>ar(n);
    for (int i = 0; i < n; i++)cin >> ar[i];
    for (int i = 0; i < n; i++) {
        if (q.empty() || ar[i] > q[cnt - 1]) {
            q.push_back(ar[i]);
            cnt++;
        }
        else {
            auto it = upper_bound(q.begin(), q.end(), ar[i]);
            *it = ar[i];
        }
    }
    cout << q.size();
    return 0;
}
//•	要求严格递增子序列（LIS，元素相等不算延续）：用 lower_bound（找到第一个 >= x 并替换）。
//•	如果允许非严格递增（可以相等，求最长非减子序列），才用 upper_bound（找到第一个 > x）。
#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    int tem = 0;  // 关键：从0开始
    int max_so_far = INT_MIN; // 初始化为最小整数

    for (int i = 0; i < n; i++)
    {
        tem += a[i];
        max_so_far = max(max_so_far, tem);
        if (tem < 0) {
            tem = 0;
        }
    }

    cout << max_so_far;
    return 0;
}
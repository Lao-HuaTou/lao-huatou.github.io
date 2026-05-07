#include<cmath>
#include<vector>
#include<iostream>
#include<algorithm>
typedef long long ll;
using namespace std;

int n;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	vector<ll>h(n + 1, 0);
	vector<ll>pre(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
	}
	sort(h.begin() + 1, h.end());
	for (int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1] + h[i];
	}
	int q; cin >> q;
	while (q--) {
		ll a, b;
		cin >> a >> b;
		ll k = (ll)ceil(1.0 * n * b / (1.0 * (a + b)));
		ll y = h[k];
		cout << ((a + b) * k - b * n) * y - a * pre[k] + b * (pre[n] - pre[k]) << '\n';
	}
	return 0;
}



#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// 全局变量方便函数调用
int n;
vector<ll> h;
vector<ll> pre;

// 函数 f(y)：计算当选择 y 时，总的浪费量
// 时间复杂度：O(log n) 因为使用了 lower_bound
ll calculate_cost(ll y, ll a, ll b) {
    // 找到第一个大于等于 y 的位置 k
    // k 表示左侧（<=y）有几个元素
    int k = lower_bound(h.begin(), h.end(), y) - h.begin();

    // 左侧代价：a * (k*y - sum(h[0...k-1]))
    ll left_cost = a * (1LL * k * y - pre[k]);
    // 右侧代价：b * (sum(h[k...n-1]) - (n-k)*y)
    ll right_cost = b * ((pre[n] - pre[k]) - 1LL * (n - k) * y);

    return left_cost + right_cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n)) return 0;

    h.resize(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // 1. 排序是前提，为了后面配合 lower_bound 和前缀和
    sort(h.begin(), h.end());

    // 2. 预处理前缀和
    pre.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + h[i];
    }

    int q;
    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b;

        // 3. 在坐标范围 [0, 10^6] 内三分搜索最优的 y
        ll L = 0, R = 1000000;
        while (R - L > 2) {
            ll m1 = L + (R - L) / 3;
            ll m2 = R - (R - L) / 3;

            if (calculate_cost(m1, a, b) < calculate_cost(m2, a, b)) {
                R = m2; // 最小值在左侧，缩小右边界
            }
            else {
                L = m1; // 最小值在右侧，缩小左边界
            }
        }

        // 4. 在剩余的极小区间 [L, R] 内暴力找出最小值
        ll min_ans = calculate_cost(L, a, b);
        for (ll i = L + 1; i <= R; i++) {
            min_ans = min(min_ans, calculate_cost(i, a, b));
        }
        cout << min_ans << "\n";
    }

    return 0;
}
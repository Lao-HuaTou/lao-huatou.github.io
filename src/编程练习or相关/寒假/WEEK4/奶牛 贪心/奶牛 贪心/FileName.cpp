#include<vector>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
struct C {
	int val, id;
};
bool cmp(const C& x, const C& y) {
	return x.val < y.val;
}
bool cmp_val(const C& a, int b) {
	return a.val < b;
}
int n;
vector<C>cow;
signed main() {
	cin >> n;
	cow.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> cow[i].val;
		cow[i].id = i;
	}
	int pos[150005];
	sort(cow.begin()+1, cow.end(),cmp);
	for (int i = 1; i <= n; i++) {
		pos[cow[i].id] = i;
	}//p[i]表原第i个数的新位置
	vector<int>pre(n + 1, 0);
	int cur = 0;
	int t=0;
	for (int i = 1; i <= n; i++) {
		t += i * cow[i].val;
		cur += cow[i].val;
		pre[i] = cur;
	}
	int q; cin >> q;
	while (q--) {
		int odid, y; cin >> odid >> y;
		int nid = pos[odid];
		int ans = t;
		ans -= nid * cow[nid].val;
		auto it = lower_bound(cow.begin() + 1, cow.end(),  y, cmp_val);
		int k = (int)(it - cow.begin());
		if (y > cow[nid].val) {
			k--;
			ans -= pre[k] - pre[nid];
		}
		else ans += pre[nid - 1] - pre[k - 1];
		ans += k * y;
		cout << ans << '\n';
	}
	return 0;
}

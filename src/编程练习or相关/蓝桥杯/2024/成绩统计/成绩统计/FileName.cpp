#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
int n, k, t;
int ar[100005];
int tem[100005];
int pre[100005];
int pres[100005];
vector<int>tem;

int ck(int x) {
	if (x < k)return 0;
	for (int i = 1; i <= x; i++) {
		tem[i] = ar[i];
	}
	sort(tem + 1, tem + x);
	double fc = 0.0;
	for (int i = 1; i <= k; i++) {
		pre[i] = pre[i - 1] + tem[i];
		pres[i] = pres[i - 1] + tem[i] * tem[i];
	}
	fc = ((double)pres[k] - k * (1.0 * pre[k] / k)*(1.0*pre[k]/k)) / k;
	double t1 = pre[k], t2 = pres[k];
	for (int i = 1; i <= x - k; i++) {
		t1 = t1 - tem[i] + tem[i + k];
		t2 = t2 - tem[i] * tem[i] + tem[i + k] * tem[i + k];
		fc = min(fc, (t2 - t1 * (t1 / k)) / k);
	}
	if (fc < t)return true;
	return false;
}
void solve() {
	cin >> n >> k >> t;
	int ans=1e9+7;
	for (int i = 1; i <= n; i++) {
		cin >> ar[i];
	}
	int l = k, r = n,mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (ck(mid)) {
			ans = min(ans, l);
			r = mid - 1;

		}
		else l = mid + 1;
	}
	if (ans > 1e9) {
		cout << -1;
		return;
	}
	else {
		cout << ans;
		return;
	}
	
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	while (T--) {
		solve();
	}
	return 0;
	
	

}
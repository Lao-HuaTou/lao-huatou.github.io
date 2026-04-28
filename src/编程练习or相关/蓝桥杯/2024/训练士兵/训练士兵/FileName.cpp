#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n, s;
struct sold {
	int p, c;
	bool operator<(const sold& a)const {
		return c < a.c;
	}

}h[100005];
int cnt[1000005];
signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s;
	int maxc = 0;
	int sp = 0;
	for (int i = 1; i <= n; i++) {
		cin >> h[i].p >> h[i].c;
		sp += h[i].p;
		cnt[h[i].c] += h[i].p;
		maxc = max(maxc, h[i].c);
	}
	sort(h+1, h+n);
	int ans = 0;
	for (int i = 1; i <= maxc; i++) {
		if (sp > s) {
			ans += s;
		}
		else {
			ans += sp;
		}
		sp -= cnt[i];
	}
	cout << ans;
	return 0;
}
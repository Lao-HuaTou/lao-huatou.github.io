#include<iostream>
#include<vector>
#include<cmath>
#define int long long
using namespace std;
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n+1);
		int l=0;
		int g = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			g=gcd(abs(a[i]),g);
			if (i == 1) continue;
			l = gcd(abs(a[i - 1]-a[i]),l);
			
		}
		if (l == 0) {
			cout << "infinite\n";
			continue;
		}
		else {
			int k = l / gcd(l, g);
			int ans = gcd(k * g, l);
			cout << ans << " " << k << "\n";
		}
	}
	return 0;
}
#include<iostream>
#include<vector>
#define int long long
using namespace std;
signed main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int ans = 0;
		while (n >= 5) {
			ans += n / 5;
			n /= 5;
		}
		cout << ans << endl;
	}
	return 0;
}
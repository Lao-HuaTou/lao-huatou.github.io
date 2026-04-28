#include<iostream>
using namespace std;
int r[5000005], c[5000005];
int main() {
	std::ios::sync_with_stdio(0);
	int n, m, k, ans = 0;
	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		char d; int x;
		cin >> d >> x;
		if (d == 'R') r[x] = !r[x];
		else c[x] = !c[x];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (r[i] != c[j]) ans++;
		}
	}
	cout << ans;
	return 0;
}

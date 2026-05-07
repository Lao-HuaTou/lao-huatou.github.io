#include<iostream>
#include<algorithm>
typedef long long ll;
using namespace std;
int n; ll m;
int cd[55];
int ck(int x) {
	ll need = 0;
	for (int i = 0; i < n; i++) {
		need += max(0, x - cd[i]);
	}
	if (need <= m && need <= x) return 1;
	return 0;
}
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)cin >> cd[i];
	int ans = 0;
	int l = 0, r = 1e9;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (ck(mid)) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	cout << ans << endl;
}
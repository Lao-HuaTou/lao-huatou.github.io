#include<iostream>
#include<vector>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n, q; cin >> n >> q;
	vector<int>inv(n + 1, 0);
	inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		inv[i] = (q - (q / i)) * inv[q % i];
		inv[i] %= q;
	}
	for (int i = 1; i <= n; i++) {
		cout << inv[i] <<"\n";
	}
	return 0;
}
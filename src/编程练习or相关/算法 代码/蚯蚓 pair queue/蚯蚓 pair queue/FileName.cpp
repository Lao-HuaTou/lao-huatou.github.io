#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
using namespace std;
int n, m, q, u, v, t;
double p;
int a[7000005];
queue<int>bug[4];
const int M = -2147483647;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> q >> u >> v >> t;
	p = (double)u / v;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n, greater<int>());
	for (int i = 1; i <= n; i++) bug[1].push(a[i]);
	for (int i = 0; i < m; i++) {
		auto pa = max({
			make_pair(bug[1].empty() ? M : bug[1].front(), 1),
			make_pair(bug[2].empty() ? M : bug[2].front(), 2),
			make_pair(bug[3].empty() ? M : bug[3].front(), 3)
			});
		long long x = (long long)pa.first + 1ll * i * q;
		int y = pa.second;
		bug[y].pop();
		int b = 1ll * x * u / v, c = x - b;
		bug[2].push(b - q - q * i);
		bug[3].push(c - q - q * i);
		if (i % t == t - 1) cout << x << " ";
	}
	cout << '\n';
	for (int i = 1; i <= m + n; i++) {
		auto pa = max({
			make_pair(bug[1].empty() ? M : bug[1].front(), 1),
			make_pair(bug[2].empty() ? M : bug[2].front(), 2),
			make_pair(bug[3].empty() ? M : bug[3].front(), 3)
			});
		long long x = (long long)pa.first + 1ll * m * q, y = pa.second;
		bug[y].pop();
		if (i % t == 0) cout << x << " ";
	}
	return 0;
}
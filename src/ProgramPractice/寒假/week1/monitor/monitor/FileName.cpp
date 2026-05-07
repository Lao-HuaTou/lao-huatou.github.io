#include<iostream>
#include<vector>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	while (cin >> n >> m) {
		vector<vector<int>>map(n + 2, vector<int>(m + 2, 0));
		int x, y;
		cin >> x;
		vector<vector<short>>diff(n + 2, vector<short>(m + 2, 0));
		while (x--) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			diff[a][b]++;
			diff[c + 1][b]--; diff[a][d + 1]--;
			diff[c + 1][d + 1]++;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++) {
				map[i][j] = map[i - 1][j] + map[i][j - 1] - map[i - 1][j - 1] + diff[i][j];
			}
		}
		vector<vector<int>>sum(n + 2, vector<int>(m + 2, 0));
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++) {
				map[i][j] = (map[i][j] > 0 ? 1 : 0);
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + map[i][j];
			}
		}
		cin >> y;
		while (y--) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			int v = (c - a + 1) * (d - b + 1);
			int area = sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
			if (v == area)cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}
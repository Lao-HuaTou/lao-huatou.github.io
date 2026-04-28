#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
int n, k, m, ans;
int color[110];
int map[110][110];
int check(int x) {
	for (int i = 1; i < x; i++)
		if (map[i][x] && color[i] == color[x])
			return 0;
	return 1;
}
void dfs(int s) {
	if (s > n) {

		ans++;
		return;
	}
	else {
		for (int i = 1; i <= m; i++)
		{
			color[s] = i;
			if (check(s)) {
				if (s == n) ans++;
				else dfs(s + 1);
			}
			else color[s] = 0;
		}
	}
}
int main()
{
	cin >> n >> k >> m;

	for (int i = 0; i < k; i++)
	{
		int a, b;
		cin >> a >> b;
		map[a][b] = 1;
		map[b][a] = 1;
	}
	dfs(1);
	cout << ans;
	return 0;
}
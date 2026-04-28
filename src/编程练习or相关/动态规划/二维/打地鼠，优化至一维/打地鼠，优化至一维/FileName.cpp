#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
int dp[10005];
int d[10005][3];
int mat[1003][1003];
int dis(int x, int y, int xx, int yy) {
	return abs((x - xx) + abs(y - yy));
}
int n, m;
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> d[i][0] >> d[i][1] >> d[i][2];
		dp[i] = 1;
	}
	for (int i = m; i > 1; i--)
		for (int j = i - 1; j >= 1; j--)
		{
			if (d[i][0] - d[j][0] >= abs(d[i][1] - d[j][1]) + abs(d[i][2] - d[j][2]))
			{
				dp[j] = max(dp[i] + 1, dp[j]);
				//若在规定时间内i能达到j，dp更新 
			}
		}
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		ans = max(ans, dp[i]);
	}
	cout << ans;
	return 0;
}
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n;
int ans;
int max1 = -1e8;
int ar[100005],cnt[100005];
int dp[100005];

signed main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ar[i];
		cnt[ar[i]]++;
		max1 = max(max1, ar[i]);
	}
	dp[1] = cnt[1];
	for (int i = 2; i <= max1; i++) {
		dp[i] = max(dp[i - 1], dp[i - 2] + cnt[i] * i);
	}
	cout << dp[max1];
	return 0;
}
//DP
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	int dp[500][500] = {0};
	cin >> n;
	dp[1][1] = 1;
	for (int i = 2; i <= n + n; i++)
		for (int j = (i + 1) >> 1; j <= i; j++)
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % 100;
	printf("%d", dp[n + n][n]);
	return 0;
}



// 方案1：滚动数组（推荐）
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	// 使用滚动数组：只需要两行来存储状态
	// dp[0]和dp[1]交替使用，表示当前行和上一行
	int dp[2][500] = { 0 };
	dp[1][1] = 1;

	for (int i = 2; i <= n + n; i++) {
		// 计算当前行和上一行的索引
		// 使用取模运算实现滚动：0和1交替
		int curr = i % 2;    // 当前行索引 (0或1)
		int prev = (i - 1) % 2;  // 上一行索引 (1或0)

		// 初始化当前行
		for (int j = 0; j < 500; j++) {
			dp[curr][j] = 0;
		}

		// 状态转移：dp[i][j] = dp[i-1][j] + dp[i-1][j-1]
		// j的范围：从(i+1)/2 到 i（有效状态范围）
		for (int j = (i + 1) >> 1; j <= i; j++) {
			dp[curr][j] = (dp[prev][j] + dp[prev][j - 1]) % 100;
		}
	}

	printf("%d", dp[(n + n) % 2][n]);
	return 0;
}





//katelan
#include <iostream>
#define MAXN 1000
long long f[MAXN];
int main()
{
	int n;
	std::scanf("%d", &n);
	f[0] = f[1] = 1;
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
		{
			f[i] += f[j - 1] * f[i - j];
			f[i] %= 100;
		}
	std::printf("%d", f[n]);
	return 0;
}

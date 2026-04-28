#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
int n, k;
int dp[10][100][2000];
int cnt[2000];//状态为i的含1个数
vector<int>allrow;//合理的行的所有情况

int get_1(int x) {
	int tem = 0;
	while (x) {
		if (x & 1) tem++;
		x >>= 1;
	}
	return tem;
}
int ck(int x) {
	if (x & (x << 1)) return 0;
	return 1;
}
signed main() {
	cin >> n >> k;
	for (int i = 0; i < (1 << n); i++) {
		if (ck(i)) {
			allrow.push_back(i);
			cnt[i] = get_1(i);
		}
	}
	//f(i, j, s_i) = \sum f(i-1, j - {count}(s_i), s_{i-1})
	//行 个数 
	for (int row = 1; row <= n; row++) {//当前行数
		for (int i = 0; i <= k; i++) {//要讨论的国王数
			for (int crow : allrow) {//遍历行情况
				int c = cnt[crow];
				//若讨论数不足c 无意义
				if (i >= c) {
					for(int last_crow:allrow)
						if(!(crow&last_crow)&&!(last_crow&(crow<<1))&&!(last_crow&(crow>>1)))
							dp[row][i][crow] += dp[row - 1][i - cnt[last_crow]][last_crow];

				}
			}
		}
	}
	int ans = 0;
	for (int crow : allrow) {
		ans += dp[n][k][crow];
	}
	cout << ans;
	return 0;
}


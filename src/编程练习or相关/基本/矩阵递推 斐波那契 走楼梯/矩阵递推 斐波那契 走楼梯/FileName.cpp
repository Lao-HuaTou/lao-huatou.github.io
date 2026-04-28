#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

const int Mod = 10007;
struct Mat {
	int mat[10][10];
	int size;
	Mat(int s) :size(s) {
		memset(mat,0,sizeof(mat));
	}
	Mat operator*(const Mat& other)const {
		Mat res(size);
		for (int i = 0; i < size; i++) {
			for (int k = 0; k<size; k++) {
				if (mat[i][k] == 0)continue;
				for (int j = 0; j < size; j++) {
					res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % Mod;
				}
			}
		}
		return res;
	}
};
int dp[11];
int main()
{
	int n, m;
	std::cin >> n >> m;
	Mat mat(m),E(m);
	dp[0] = 1;
	int cur = 1;
	for (int i = 1; i < m; i++) {
		dp[i] = cur + 1;
		cur += dp[i];
	}
	for (int i = 0; i < m; i++) std::cout << dp[i]<<" ";
	Mat res(m);
	for (int i = 0; i < m; i++)res.mat[0][i] = 1;
	for (int i = 1; i < m; i++) {
		res.mat[i][i - 1] = 1;
	}
	for (int i = 0; i < m; i++) E.mat[i][i] = 1;
	n=n-m;
	while (n) {
		if (n & 1) E = E * res;
		res =res * res;
		n >>= 1;
	}
	int ans = 0;
	for (int i = 0; i < m ; i++) {
		ans = (ans + E.mat[0][i] * dp[m-i-1]) % Mod;
	}
	std::cout << ans;
	return 0;
}
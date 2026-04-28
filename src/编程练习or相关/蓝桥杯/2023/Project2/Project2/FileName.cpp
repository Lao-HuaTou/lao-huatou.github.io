#include<iostream>
using namespace std;
#define int long long
char t[11][11];
int mat[11][11];
int n, m;
int f = 0;
void print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << mat[i][j];
		}
		cout << endl;
	}
}
bool ck() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (t[i][j]!='_') {
				int cur = t[i][j] - '0';
				int now = 0;
				for (int y = j - 1; y <= j + 1; y++) {
					for (int x = i - 1; x <= i + 1; i++) {
						if (mat[i][j] == 1)now++;
						
					}
				}
				if (now != cur)return false;
			}
		}
	}
	return true;
}
void dfs(int x,int y,int cnt) {
	if (cnt==m*n&&ck()) {
		f = 1;
		print(); return;
	}
	mat[x][y] = 1;
	if (x == m)dfs(1, y + 1, cnt + 1);
	else dfs(x + 1, y, cnt + 1);
	mat[x][y] = 0;
	if (x == m)dfs(1, y + 1, cnt + 1);
	else dfs(x + 1, y, cnt + 1);
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> t[i][j];
		}
		//getchar();
	}
	memset(mat, 2, sizeof(mat));
	dfs(1, 1, 0);
	if (f) {
		return 0;
	}
	dfs(1, 1, 0);
	return 0;
}

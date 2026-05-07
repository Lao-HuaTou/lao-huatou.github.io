#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
int lg2(int x) {
	int a = 0; while ((1 << a) <= (x >> 1)) a++;
	return a;
}
bool cmp(const vector<int>& a, const vector<int>& b) {
	return a[1] < b[1];
}
int n, m;
vector<vector<int>>line;
vector<vector<int>>st;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	int p = lg2(2*n);
	int e = 2 * n + 1;
	line.resize(e + 1, vector<int>(3, 0));
	st.resize(e + 1, vector<int>(p+1, 0));
	for (int i = 1; i <= n; i++) {
		int x, y; cin >> x >> y;
		if (x > y)y += m;
		line[i][0] = i;
		line[i][1] = x;
		line[i][2] = y;
	}
	sort(line.begin() + 1, line.begin() + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		line[i+n][0] = line[i][0];
		line[i+n][1] = line[i][1]+m;
		line[i+n][2] = line[i][2]+m;
	}
	int cur = 1;
	for (int i = 1; i <= 2*n; i++) {
		while (cur <= 2*n && line[i][2] >= line[cur][1]) {
			cur++;
		}
		st[i][0] = cur-1;
	}
	for (int j = 1; j <= p; j++) {
		for (int i = 1; i <= 2 * n; i++) {
			st[i][j]=st[st[i][j - 1]][j - 1];
		}
	}
	vector<int>ans(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		int tar = line[i][1] + m;
		int cnt = 1;
		int now = i;

		for (int j = p; j>=0; j--) {
			if (st[now][j]!=0 && line[st[now][j]][2] < tar) {
				now = st[now][j];
				cnt += 1 << j;
			}
		}
		ans[line[i][0]] = cnt + 1;
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " ";

	}
	return 0;
}
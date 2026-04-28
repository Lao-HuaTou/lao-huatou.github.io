#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//1 1 1 1 2 2 3 4 4 
//1 2 3 4 5 6 7 8 9
//1 1 1 1 2 2 3 4 4
int n, q;
const int N = 1e5 + 5;
int bucket[N];
int ar[N];
int l[N], r[N];
const int F = -1e6;
int st[N][16];
int lg[N];
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	int cnt = 0;
	ar[0] = F;
	l[1] = 1;
	lg[0] = -1;
	for (int i = 1; i <= n; i++) {
		lg[i] = lg[i >> 1] + 1;
	}
	for (int i = 1; i <= n; i++) {
		cin >> ar[i];
		if (ar[i - 1] != ar[i]) {
			cnt++;
			r[cnt-1] = i - 1;
			l[cnt] = i;
		}
		bucket[i] = cnt;
	}
	r[cnt] = n;
	for (int i = 1; i <= cnt; i++) {
		st[i][0] = r[i] - l[i] + 1;
	}
	for (int j = 1; j <= lg[cnt]; j++) {
		for (int i = 1; i + (1 << j) - 1 <= cnt; i++) {
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	while (q--) {
		int x, y;
		cin >> x >> y;
		if (x > y) {
			swap(x, y);
		}
		int lbc = bucket[x], rbc = bucket[y];
		if (lbc == rbc) {
			cout << y - x + 1 << endl;
			continue;
		}
		int a = r[lbc] - x + 1, b = y - l[rbc] + 1;
		int c = 0;
		if (lbc + 1 < rbc) {
			int L = lbc + 1, R = rbc - 1;
			int k = lg[R-L+1];
			c = max(st[L][k], st[R - (1 << k)+1][k]);
		}
		int ans = max(max(a, b), c);
		cout << ans << endl;
	}
	return 0;
}



#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, q;
const int N = 1e5 + 5;
int bucket[N];
int ar[N];
int l[N], r[N];
const int F = -1e6;
int st[N][20]; // 1. 16 改成 20，防止 N=1e5 时越界
int lg[N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	// 这里的 while 是为了应对多组数据（如样例最后有个 0）
	while (cin >> n && n != 0) {
		cin >> q;
		int cnt = 0;
		ar[0] = F;
		// 注意：多组数据时，l[cnt+1] 等数组需要逻辑重置，你的结构是通过 cnt 覆盖实现的
		lg[0] = -1;
		for (int i = 1; i < N; i++) { // 预处理 lg 数组，范围给够
			lg[i] = lg[i >> 1] + 1;
		}
		for (int i = 1; i <= n; i++) {
			cin >> ar[i];
			if (ar[i - 1] != ar[i]) {
				cnt++;
				r[cnt - 1] = i - 1; // 2. 修正上一个块的右边界
				l[cnt] = i;       // 修正当前块的左边界
			}
			bucket[i] = cnt;
		}
		r[cnt] = n;

		for (int i = 1; i <= cnt; i++) {
			st[i][0] = r[i] - l[i] + 1;
		}
		for (int j = 1; j <= lg[cnt]; j++) {
			for (int i = 1; i + (1 << j) - 1 <= cnt; i++) {
				st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}

		while (q--) {
			int x, y;
			cin >> x >> y;
			if (x > y) swap(x, y);

			int lbc = bucket[x], rbc = bucket[y];
			if (lbc == rbc) {
				cout << y - x + 1 << "\n";
				continue;
			}
			int a = r[lbc] - x + 1, b = y - l[rbc] + 1;
			int c = 0;
			if (lbc + 1 < rbc) {
				// 3. 关键修正：中间块的范围是 [L, R] = [lbc + 1, rbc - 1]
				int L = lbc + 1, R = rbc - 1;
				int k = lg[R - L + 1];
				// 公式：max(st[L][k], st[R - (1 << k) + 1][k])
				c = max(st[L][k], st[R - (1 << k) + 1][k]);
			}
			int ans = max({ a, b, c });
			cout << ans << "\n";
		}
	}
	return 0;
}
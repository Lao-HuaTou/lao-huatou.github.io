#include<iostream>
#include<algorithm>
#include<map>
#define int long long

using namespace std;

int n, m;
int ar[100];
int ans = 1e8;
/*
void dfs(int now, int dao, int sum, int way) {//O(3^n)
	if (now == n) {
		if (sum == m) {
			ans = min(ans, dao);
		}
		return;
	}
	if (sum > m)return;
	if (way == 0) {
		sum += ar[now] * 2;
	}
	else if (way == 1) {
		sum += ar[now];
		dao++;
	}
	for (int i = 0; i < 3; i++) {
		dfs(now + 1, dao, sum, i);
	}
}
*/



//折半法
map<int, int>p;
int mid;
void dfs1(int now, int dao, int sum) {//O(3^n/2)
	if (sum > m)return;
	if (now == mid) {
		if (p.find(sum) == p.end() || p[sum] > dao) {
			p[sum] = dao;
			return;
		}
		return;
	}
	if (p.count(sum) && p[sum] < dao) return;
	p[sum] = dao;
	dfs1(now + 1, dao, sum + ar[now] * 2);
	dfs1(now + 1, dao + 1, sum + ar[now]);
	dfs1(now + 1, dao, sum);
}
void dfs2(int now, int dao, int sum) {
	if (sum > m || dao > ans)return;
	if (now == n) {
		int need = m - sum;
		if (p.find(need) != p.end() && dao + p[need] < ans)ans = dao + p[need];
	}
	dfs2(now + 1, dao, sum + ar[now] * 2);
	dfs2(now + 1, dao + 1, sum + ar[now]);
	dfs2(now + 1, dao, sum);
}


signed main() {
	cin >> n >> m; for (int i = 0; i < n; i++)cin >> ar[i];
	m <<= 1;
	mid = n / 2;
	sort(ar, ar + n, greater<int>());
	dfs1(0, 0, 0);
	dfs2(mid, 0, 0);

	if (ans >= 1e8) cout << -1;
	else cout << ans;
	return 0;
}

using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)

int n, m;
int ans = 2147483647; // 对应 INT_MAX
int a[1010101];
map<int, int> mp;

// 完全复刻第一个 dfs
void dfs(int sum, int x, int cnt) {
	if (sum > m || x > n / 2) return;
	if (sum == m) {
		ans = min(ans, cnt);
		return;
	}
	// 关键：若之前到过且代价更小，直接返回；否则更新 mp
	if (mp.count(sum) && mp[sum] < cnt) return;
	mp[sum] = cnt;

	dfs(sum, x + 1, cnt);                 // 状态1：不选
	dfs(sum + a[x + 1] * 2, x + 1, cnt);     // 状态2：原价
	dfs(sum + a[x + 1], x + 1, cnt + 1);     // 状态3：半价
}

// 完全复刻第二个 DFS
void DFS(int sum, int x, int cnt) {
	if (sum > m || x > n) return;
	// 核心逻辑：查表匹配，匹配到立即返回
	if (mp.count(m - sum)) {
		ans = min(ans, cnt + mp[m - sum]);
		return;
	}

	DFS(sum, x + 1, cnt);                 // 状态1
	DFS(sum + a[x + 1] * 2, x + 1, cnt);     // 状态2
	DFS(sum + a[x + 1], x + 1, cnt + 1);     // 状态3
}

signed main() {
	// 基础输入
	if (!(cin >> n >> m)) return 0;
	m *= 2;

	rep(i, 1, n) cin >> a[i];

	// 必须排序，原代码逻辑依赖此顺序
	sort(a + 1, a + 1 + n);

	// 折半搜索
	dfs(0, 0, 0);
	DFS(0, n / 2, 0);

	// 输出结果
	if (ans > 2147483647 / 2) cout << -1 << endl;
	else cout << ans << endl;

	return 0;
}
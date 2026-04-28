#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define mod 998244353
using namespace std;
const int N = 200005;
int n, m, d[N], ans = 1, cnt;
vector<pair<int, int>> e[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int u, v, w; m--;) scanf("%d%d%d", &u, &v, &w),
		e[w].emplace_back(u, v), d[u] ++, d[v]++;
	for (int i = 1; i <= n; i++) cnt += !d[i];
	for (int i = n; i >= 1; i--) {
		if (e[i].empty()) {
			if (!cnt) { ans = 0; break; }
			ans = 1ll * ans * cnt-- % mod;
		}
		if (e[i].size() == 1) {
			auto [u, v] = e[i][0]; d[u] --, d[v]--;
			if (d[u] && d[v]) { ans = 0; break; }
			if (!d[u] && !d[v]) ans = ans * 2 % mod, cnt++;
		}
		if (e[i].size() >= 2) {
			int o = 0;
			auto [u1, v1] = e[i][0];
			auto [u2, v2] = e[i][1];
			if (u1 == u2 || u1 == v2) o = u1;
			if (v1 == u2 || v1 == v2) o = v1;
			if (!o) { ans = 0; break; }
			for (auto [x, y] : e[i])
				if (x != o && y != o) ans = 0;
			if (!ans) break;
			for (auto [x, y] : e[i]) {
				if (x == o) swap(x, y);
				if (!--d[x]) cnt++;
			}d[o] = 0;
		}
	}printf("%d", ans);
}
/*
思考 n 应该填哪儿？
- 没有该限制，只能填在任意未填孤立点上，ans *= cnt, cnt --
- 只有一个该限制
	- 如果该限制两边都有连其它点，则无解
	- 如果该限制只有一边连了其它点，就直接填在另一个点上
	- 否则任意选一个位置填并删去该限制，另一个位置变为未填孤立点，ans *= 2, cnt ++
		-（这里的孤立点是只有以后的点能填的）
- 有两个或以上的该限制
	- 如果是个菊花，就填在中心上，并将所有该限制删去，更新孤立点
	- 如果不是，就无解
- 发现每种有解的情况都能将该限制删光并直接确立该点的位置，于是做完了。

你说得对，但是原根是一个数学符号。设 m 是正整数，a 是整数，
若 a 模 m 的阶等于 φ(m)，则称 a 为模 m 的一个原根。假设一
个数 g 是 P 的原根，那么 g^i mod P 的结果两两不同，且有
1<g<P, 0<i<P，归根到底就是 g^x = 1 (mod P) 当且仅当
x=P-1 的时候成立。（这里 P 是素数）。你的数学很差，我现在
每天用原根都能做 1e5 次数据规模 1e6 的 NTT ，每个月差不多
3e6 次卷积，也就是现实生活中 3e18 次乘法运算，换算过来最少
也要算 1000 年。虽然我只有 14 岁，但是已经超越了中国绝大多
数人（包括你）的水平，这便是原根给我的骄傲的资本。
*/
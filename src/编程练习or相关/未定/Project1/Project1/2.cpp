#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
#include<cstring>
#define int long long
using namespace std;
const int mod = 998244353;
const int N = 2e5 + 5;

//struct edge {
//	int to, nxt, w;
//}e[N];
//int head[N];
int n, m;
//int c;
//int vis[N];
//void add(int u, int v, int w) {
//	e[++c] = { v,head[u],w };
//	head[u] = c;
//}
//bool inq[N];
//int dis[N];
int a[N];
int dp[N];
int fact[N];
int invFact[N];
int cnt[N];
int cc(int x, int y) {
	if (y < x) return 0;
	if (fact[x] == 0) return 0;
	return fact[y] / fact[x] / fact[y - x];
}

int qpow(int x, int y) {
	//if (y == 0)return 1;
	int res = 1;
	while (y) {
		if (y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}
void precompute(int n) {
	fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
	invFact[n] = qpow(fact[n], mod - 2);
	for (int i = n - 1; i >= 0; i--) invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
}
void solve() {
	cin >> n >> m;
	precompute(n);
	int sum = 0;
	for (int i = 1;i <= n;i++) {
		cin >> a[i];cnt[a[i]]++;
		sum += a[i];
	}
	sort(a + 1, a + 1 + n);

	for (int i = 1;i < a[n];i++)
	{
		dp[i] = 0;
	}
	//  cout<<a[n]<<endl<<endl;
	for (int i = a[n];i <= m;i++) {
		dp[i] = 1;
		for (int j = 1;j <= a[n];j++) {
			if (!cnt[j])continue;
			dp[i] = (dp[i] * qpow(cc(j, i), cnt[j])) % mod;
			//	cout << i << " " << dp[i] << endl;
		}
		//	cout << i << " " << dp[i] << endl;
	}

	for (int i = 1;i <= m;i++) {
		cout << dp[i] << "\n";
	}

}

signed main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T = 1;
	int temp = 1;
	fact[0] = 1;
	
	//for (int i = 0;i <= 15;i++)cout << i << " " << chengjie[i] << "\n";
	//cin>>T;
	while (T--) {
		solve();
	}
	return 0;
}

#include<iostream>
#include<algorithm>


#define int long long
using namespace std;

int n, m;
int ans[1000005];
bool vis[10000005];
signed main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		int down = n, up = n * (n + 1) / 2;
		if (m<down || m>up) {
			cout << -1 << "\n";
			continue;
		}
		int leftw=n;
		int stay = 0;
		while (m > 2 * leftw - 1) {
			m -= leftw;
			leftw--;
			stay++;
		}
		for (int i = 0; i < stay; i++) {
			ans[i] = n - i;
		}
		ans[stay] = m - leftw + 1;
		for (int i = stay + 1; i < n; i++) {
			ans[i] = 1;
		}
		//for (int i = 0; i < n; i++) {
		//	cout << ans[i] << " ";
		//}
		cout << ans[0] << "\n";
		int minn = ans[0];
	//	cout << ans[stay] << endl << endl;
		int last=ans[stay];
		
		for (int i = 0; i < stay; i++) {
			int u = ans[i];
			int v = ans[i + 1];
			cout << u << " " << v << "\n";
			vis[u] = vis[v] = true;
			last = v;
		}
		vis[ans[stay]] = true;
		for (int i = 1; i <= n; i++) {
			if (vis[i])continue;
			int u = last;
			int v = i;
			vis[i] = true;
			last = v;
			cout << u << " " << v << "\n";
		}
		

	}
	return 0;
}


//cin >> n >> k;
//for (int i = 0; i < n; i++) {
//	p[i] = i;
//}
//for (int i = 0; i < k; i++) {
//	int ck, x, y; cin >> ck >> x >> y;
//	if (x > n || y > n) {
//		ans++;
//		continue;
//	}
//	if (ck == 2 && x == y) {
//		ans++;
//		continue;
//	}
//	if (ck == 2) {
//
//	}
//	else {
//		if (chi[x] != chi[y]) {
//			ans++;
//			continue;
//		}
//		merge(x, y);
//
//
//	}
//}
//cout << ans;


//int find(int x) {
//	return x == p[x] ? x : p[x] = find(p[x]);
//}
//void merge(int x, int y) {
//	int rx = find(x);
//	int ry = find(y);
//	if (rx != ry) {
//		p[rx] = p[ry];
//	}
//}

//const int N = 5e4 + 5;
//int chi[N];//1 A 2 B 3 C 0 none
//int n, k;
//int ans = 0;
//int p[N];
//int a[N], b[N], c[N];
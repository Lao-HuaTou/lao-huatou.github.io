#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#include<cstdio>

using namespace std;
typedef long long ll;
const int maxn = 5e5 + 5;

int u[4] = { 6,2,4,8 };


int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll T = 1;
	cin >> T;
	while (T--) {
		ll n, m, k;
		cin >> n >> m >> k;
		while (n >= m) {
			n = k + n - m;
		}
		if (n == 0) cout << "1\n";
		else cout << u[n % 4] << '\n';
	}

	return 0;
}




/*using namespace std;
typedef long long ll;
const int maxn = 5e5 + 5;
int line[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

struct Nide {
	int x, y;
}d[10];
bool vis[100005];
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll T = 1;
	//cin >> T;
	while (T--) {
		int n, m; cin >> n >> m;
		int cnt = 0;
		int ef = 0;
		for (int i = 0; i < m; i++) {
			cin >> d[i].x >> d[i].y;
			if (line[i] != -1) {
				cnt++;
			}
			else {
				line[i] = ((d[i].x + d[i].y) % n) == 0 ? n : (d[i].x + d[i].y) % n;
				ef++;
				vis[line[i]] = true;
			}
		}
		while (cnt) {
			for (int i = 1; i <= n; i++) {
				if (!vis[i]) {
					cnt--;
					line[ef++] = i;
				}
			}
		}
		//cout << ef;
		for (int i = 0; i < ef; i++)cout << line[i] << " ";
	}

	return 0;
}

*/
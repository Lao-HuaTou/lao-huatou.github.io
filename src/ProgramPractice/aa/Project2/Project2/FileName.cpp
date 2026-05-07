#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<cstring>
#define int long long
using namespace std;
const int mod = 998244353;
string s;
vector<int>pp;
signed main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T = 1;
	int curx = 1, cury = 1;
	cin >> T;
	
	while (T--) {
		int m, n; cin >> m >> n;
		cin >> s;
		int c = 0;
		curx = 1; cury = 1;
		int ans = 1ll * m * n;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '?') {
				c++;
			}
			else if (s[i] == 'D' && !c) {
				ans -= n - curx;
				cury++;
			}
			else if (s[i] == 'R' && !c) {
				curx++;
				ans -= m - cury;
			}
			else c--;
		}
		cout << ans << "\n";
	}
	return 0;
}
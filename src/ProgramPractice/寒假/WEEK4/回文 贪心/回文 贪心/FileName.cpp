#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
using namespace std;
int n;
int pos[1000005][2];
int cnt[1000005];
vector<int>ar;
string ck(int L, int l, int r, int R) {
	string s = "";
	string back = "";
	for (int i = 1; i < n; i++) {
		if (L < l && ar[L] == ar[l]) {
			s += "L"; back += "L"; L++; l--;
		}
		else if (L <= l && r <= R && ar[L] == ar[r]) {
			s += "L"; back += "R"; L++; r++;
		}
		else if (r < R && ar[R] == ar[r]) {
			s += "R"; back += "R"; R--; r++;
		}
		else if (R >= r && L <= l && ar[R] == ar[l]) {
			s += "R"; back += "L"; R--; l--;
		}
		else return "-1";
	}
	reverse(back.begin(), back.end());
	return s + back;
}
int main() {
	freopen("palin.in", "r", stdin);
	freopen("palin.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i <= n; i++) {
			cnt[i] = 0;
			pos[i][0] = pos[i][1] = 0;
		}
		ar.assign(2 * n + 1, 0);
		for (int i = 1; i <= 2 * n; i++) {
			cin >> ar[i];
			if (cnt[ar[i]] < 2) {
				pos[ar[i]][cnt[ar[i]]++] = i;
			}
		}
		int k1 = pos[ar[1]][1];
		string check = ck(2, k1 - 1, k1 + 1, 2 * n);
		if (check != "-1") {
			cout << "L" << check << "L" << '\n';
			continue;
		}
		int k2 = pos[ar[2 * n]][0];
		string check1 = ck(1, k2 - 1, k2 + 1, 2 * n - 1);
		if (check1 != "-1") {
			cout << "R" << check1 << "L" << '\n';
			continue;
		}
		cout << "-1" << '\n';
	}
	return 0;
}
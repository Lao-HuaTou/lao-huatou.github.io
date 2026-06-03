#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define int long long
#define mod 998244353

int mm[11];

int findmax(int x) {
	int m = 0;
	while (x) {
		int t = x % 10;
		m = max(m, t);
		x /= 10;
	}
	return m;
}

void solve() {
	int l, r;
	cin >> l >> r;
	int len = r - l + 1;
	if (len < 10) {
		int ans = -1;
		int ansn = 0;
		string anss = "9999999999";
		for (int i = l; i <= r; ++i) {
			int m = findmax(i);
			string ts = to_string(i);
			if (m > ans) {
				ans = m;
				ansn = i;
				anss = ts;
			}
			else if (m == ans) {
				if (ts < anss) {
					ansn = i;
					anss = ts;
				}
			}
		}
		cout << ans << " " << ansn << endl;
	}
	else {
		string anss = "9999999999";
		int ansn = -1;
		int w1, w2;
		w1 = w2 = 0;
		int tl = l, tr = r;
		while (tl) {
			w1++;
			tl /= 10;
		}
		while (tr) {
			w2++;
			tr /= 10;
		}
		for (int i = w1; i <= w2; ++i) {
			if (mm[i]<l || mm[i]>r) {
				continue;
			}
			string t = to_string(mm[i]);
			if (t < anss) {
				anss = t;
				ansn = mm[i];
			}
		}
    if(ansn==-1){
        int i=l;
        for(i;findmax(i)!=9;++i){}
        ansn=i;
    }

		cout << 9 << " " << ansn << endl;
	}
}



signed main() {
	mm[1] = 9;
	mm[2] = 19;
	mm[3] = 109;
	mm[4] = 1009;
	mm[5] = 10009;
	mm[6] = 100009;
	mm[7] = 1000009;
	mm[8] = 10000009;
	mm[9] = 100000009;
	mm[10] = 1000000009;
	int t;
	t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
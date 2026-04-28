#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;
const int maxn = 5e5 + 5;
int n, m;
int t1[maxn];
int ar[maxn];
vector<int>ran;
void add(int x, int v) {
	for (; x <= m; x += x & (-x)) t1[x] += v;
}
int sum(int x) {
	int res = 0;
	for(;x>0;x-=x&(-x))res+=t1[x];
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(); cout.tie(0); 
	int T=1;
	            cin >> T;

	while (T--) {
		cin >> n;
		ran.clear();
		memset(ar, 0, sizeof(ar));
		memset(t1, 0, sizeof(ar));

		for (int i = 1; i <= n; i++) {
			cin >> ar[i];
			ran.push_back(ar[i]);
		}
		sort(ran.begin(), ran.end());
		ran.erase(unique(ran.begin(), ran.end()), ran.end());
		m = ran.size();
		for (int i = 1; i <= n; i++) {
			ar[i] = lower_bound(ran.begin(), ran.end(), ar[i]) - ran.begin() + 1;
		}
		for (int i = 1; i <= n; i++) {
			add(ar[i], 1);
		}
		for (int i = 1; i <= n; i++) {
			add(ar[i], -1);
			int count_smaller = sum(ar[i] - 1);
			int count_bigger = (n - i) - sum(ar[i]);
			cout << max(count_smaller, count_bigger) << (i == n ? "" : " ");
		}
		cout << "\n";

	}

	return 0;
}
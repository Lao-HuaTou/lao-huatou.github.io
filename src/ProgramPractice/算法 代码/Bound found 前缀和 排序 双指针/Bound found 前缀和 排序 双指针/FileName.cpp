#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
using namespace std;
typedef long long ll;
struct Prefix {
	ll value;
	int index; 
};
bool cmp(const Prefix& a, const Prefix& b) {
	if (a.value != b.value) return a.value < b.value;
	return a.index < b.index;
}

ll ans = 0;
int l, r;
int main()
{
	int n, k;
	while (1) {
		l = 0, r = 0;
		cin >> n >> k;
		if (n == 0 && k == 0)break;
		vector<int>a(n+1 , 0);
		vector<ll>sum(n + 1, 0);
		int t;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum[i] = sum[i - 1] + a[i];
		}
		vector<Prefix>sorted(n + 1);
		for (int i = 0; i <= n; i++)
		{
			sorted[i].index = i;
			sorted[i].value = sum[i];
		}
		sort(sorted.begin(), sorted.end(),cmp);
		int cl = 0, cr = 1;
		ll cans = LLONG_MAX;

		while (k--) {
			cin >> t;
			cl = 0, cr = 1;
			l = 1, r = 1;
			long long curdiff = LLONG_MAX;
			ans = 0; 
			while (cr <= n) {
				long long diff = sorted[cr].value - sorted[cl].value;
				if (llabs(diff - t) < curdiff) {
					curdiff = llabs(diff - t);
					ans = diff;
					l = min(sorted[cl].index, sorted[cr].index) + 1;
					r = max(sorted[cl].index, sorted[cr].index);
				}
				if (diff < t) cr++;
				else if (diff > t) cl++;
				else break;
				if (cl == cr) cr++;
			}
			printf("%lld %d %d\n", ans, l, r);
		}
	}
	return 0;
}
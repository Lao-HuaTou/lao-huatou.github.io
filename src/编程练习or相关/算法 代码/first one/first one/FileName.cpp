//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<vector>
//typedef long long ll;
//using namespace std;
//int main()
//{
//	int t;
//	cin >> t;
//	while (t--)
//	{
//		ll ans = 0;
//		int n;
//		cin >> n;
//		vector<int> a(n+1,0);
//		vector<ll>sum(n + 1, 0);
//		for (int i = 1; i <= n; i++) {
//			cin >> a[i];
//			sum[i] = sum[i - 1] + a[i];
//		}
//		for (int k = 0; k <= 34; k++) {
//			ll l, r;
//			l = (k == 0 ? 0 : 1LL << k);
//			r = (1LL << (k + 1)) - 1;
//			int p1 = 1, p2 = 0;
//			for (int i = 1; i <= n; i++) {
//				p1 = max(p1, i);
//				while (p1<=n&&sum[p1]-sum[i-1] < l) p1++;
//				if (p1 > n) continue;
//				p2 = max(p2,p1 - 1);
//				while (p2 < n && sum[p2 + 1]-sum[i-1] <= r) p2++;
//				if(p1<=p2)ans += (ll)(k + 1) * (i * (p2 - p1 + 1) + (p1 + p2) * (p2 - p1 + 1) / 2);
//			}
//		}
//		cout << ans << endl;
//
//	}
//	return 0;
//}


#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> sum(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            ll x;
            cin >> x;
            sum[i] = sum[i - 1] + x;
        }
        ll ans = 0;
        ll total = sum[n];
        for (int k = 0; k <= 34; k++) {
            ll L, R;
            L = (k == 0 ? 0 : 1LL << k);
            R = (1LL << (k + 1)) - 1;
            if (L > total) break;
       
            int p1 = 1, p2 = 0;
            for (int i = 1; i <= n; i++) {
                if (p1 < i) p1 = i;
                while (p1 <= n && sum[p1] - sum[i - 1] < L) p1++;
                if (p1 > n) continue;

                if (p2 < p1 - 1) p2 = p1 - 1;
                while (p2 < n && sum[p2 + 1] - sum[i - 1] <= R) p2++;

                if (p1 <= p2) {
                    ll cnt = p2 - p1 + 1;
                    ll add = (ll)i * cnt + (p1 + p2) * cnt / 2;
                    ans += (k + 1) * add;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
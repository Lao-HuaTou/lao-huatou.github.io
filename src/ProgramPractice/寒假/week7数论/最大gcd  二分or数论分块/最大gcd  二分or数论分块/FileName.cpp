#include<iostream>
typedef long long ll;
using namespace std;
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}
void solve() {
    ll L, R;
    cin >> L >> R;
    ll ans = 1;
    for (ll l = 1, r; l <= R; l = r + 1) {
        r = R / (R / l);
        if (L - 1 >= l) {
            r = min(r, (L - 1) / ((L - 1) / l));
        }
        ll count = (R / l) - ((L - 1) / l);
        if (count >= 2) {
            ans = max(ans, r);
        }
    }
    cout << ans << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
#include<iostream>
#include<cmath>
#include<vector>
typedef long long ll;
using namespace std;
const ll mod = 1000000007;
ll jc[500005] = { 1 };
ll inv[500005];
ll ar[500005];
ll cnt[500005];
ll qpow(ll x, ll n) {
	ll res = 1;
	x %= mod;
	while (n) {
		if (n & 1) res = res * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}
ll getinv(ll x) {
	return qpow(x, mod - 2);
}


int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	ll sum; cin >> sum;
	ll scale = sum - 2;
	jc[0] = 1;
	inv[1] = 1;
	for (ll i = 1; i <= scale; i++) {
		jc[i] = jc[i - 1] * i % mod;
		//	cout << jc[i];
	}
	for (ll i = 0; i <= scale; i++) {
		inv[i] = getinv(jc[i]);
	}

	for (ll i = 1; i <= sum; i++) {
		cin >> ar[i];
		cnt[ar[i]]++;
	}

	ll ans = 0;
	for (ll i = 1; i <= sum; i++) {
		if (scale % i == 0 && cnt[i] && cnt[scale / i]) {
			ll n = i, m = scale / i;
			cnt[n]--;
			cnt[m]--;
			//			ans = jc[m] % mod * jc[n] % mod;
			ll now = jc[scale];
			for (ll j = 1; j <= 500000; j++) {
				if (cnt[j] > 1) {
					now = now * inv[cnt[j]] % mod;
				}
			}
			ans = (ans + now) % mod;
			cnt[n]++;
			cnt[m]++;
		}
	}
	cout << ans;
	return 0;


}
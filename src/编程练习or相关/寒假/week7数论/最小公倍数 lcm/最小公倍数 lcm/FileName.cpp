#include <iostream>
#define int long long
using namespace std;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
void solve() {
    int m;
    cin >> m;
    int res;
    cin >> res;
    for (int i = 1; i < m; ++i) {
        int x;
        cin >> x;
        res = res/gcd(res,x)*x;
    }
    cout << res << endl;
}
signed main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
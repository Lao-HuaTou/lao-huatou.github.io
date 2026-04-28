#include<iostream>
#include<cmath>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int x, y;
    cin >> x >> y;

    // 如果y不能被x整除，无解
    if (y % x != 0) {
        cout << 0;
        return 0;
    }

    int n = y / x;  // a * b = n
    int co = 0;

    // 遍历a的可能取值
    for (int a = 1; a * a <= n; a++) {
        if (n % a == 0) {
            int b = n / a;
            // 检查gcd(a, b) == 1
            if (gcd(a, b) == 1) {
                if (a == b) {
                    co++;  // p = x*a, q = x*b，此时p=q
                }
                else {
                    co += 2;  // (p,q)和(q,p)两个数对
                }
            }
        }
    }

    cout << co;
    return 0;
}








using namespace std;
long long m, n, ans;
int main1() {
    cin >> m >> n;
    if (m == n) ans--;
    n *= m;//把两数的积存入n中 
    for (long long i = 1; i <= sqrt(n); i++) {
        if (n % i == 0 && gcd(i, n / i) == m) ans += 2;
    }
    cout << ans;
    return 0;
}

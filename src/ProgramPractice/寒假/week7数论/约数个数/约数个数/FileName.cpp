#include <iostream>
using namespace std;
int main() {
    long long n;
    while (cin >> n && n != 0) {
        long long a = 0, b = 0, c = 0, d = 0;
        while (n % 2 == 0) {
            a++;
            n /= 2;
        }
        while (n % 3 == 0) {
            b++;
            n /= 3;
        }
        while (n % 5 == 0) {
            c++;
            n /= 5;
        }
        while (n % 7 == 0) {
            d++;
            n /= 7;
        }
        long long ans = (a + 1) * (b + 1) * (c + 1) * (d + 1);
        cout << ans << endl;
    }
    return 0;
}
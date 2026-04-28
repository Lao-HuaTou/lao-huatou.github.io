#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long MOD = 998244353;
long long quick_pow(long long base, long long power) {
    long long res = 1;
    while (power) {
        if (power & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        power >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<long long> diff2(n + 2, 0), diff3(n + 2, 0);

        for (int i = 0; i < m; ++i) {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            if (x == 2) {
                diff2[l] += 1;
                diff2[r + 1] -= 1;
            }
            else { 
                diff3[l] += 1;
                diff3[r + 1] -= 1;
            }
        }
        vector<long long> cnt2(n, 0), cnt3(n, 0);
        cnt2[0] = diff2[0];
        cnt3[0] = diff3[0];
        for (int i = 1; i < n; ++i) {
            cnt2[i] = cnt2[i - 1] + diff2[i];
            cnt3[i] = cnt3[i - 1] + diff3[i];
        }
        long long min2 = cnt2[0], min3 = cnt3[0];
        for (int i = 1; i < n; ++i) {
            if (cnt2[i] < min2) min2 = cnt2[i];
            if (cnt3[i] < min3) min3 = cnt3[i];
        }
        long long ans = (quick_pow(2, min2) * quick_pow(3, min3)) % MOD;
        cout << ans << "\n";
    }

    return 0;
}
//#include<iostream>
//#include<vector>
//using namespace std;
//
//int main()
//{
//    int n;
//    cin >> n;
//    while (n != 0) {
//        int a, b, c = 0;
//        vector<int> arr(n, 0);
//        vector<int> diff(n, 0);
//        while (c != n) {
//            cin >> a >> b;
//            int l = a - 1;
//            int r = b - 1;
//            diff[l] += 1;
//            if (r + 1 < n) {
//                diff[r + 1] -= 1;
//            }
//            c++;
//        }
//        arr[0] = diff[0];
//        for (int i = 1; i < n; i++) {
//            arr[i] = arr[i - 1] + diff[i];
//        }
//        for (int i = 0; i < n; i++) cout << arr[i] << " ";
//        cout << endl;
//        cin >> n;
//    }
//    return 0;
//}
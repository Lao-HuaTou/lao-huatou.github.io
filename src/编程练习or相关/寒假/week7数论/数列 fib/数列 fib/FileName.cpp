//#include <iostream>
//#include <vector>
//using namespace std;
//int main() {
//    int a, b, n;
//    while (cin >> a >> b >> n && (a != 0 || b != 0 || n != 0)) {
//        if (n == 1 || n == 2) {
//            cout << 1 << endl;
//            continue;
//        }
//        vector<int> ar(100);
//        ar[1] = 1;
//        ar[2] = 1;
//        int t = 0;
//        for (int i = 3; i < 100; i++) {
//            ar[i] = (a * ar[i - 1] + b * ar[i - 2]) % 7;
//            if (ar[i - 1] == 1 && ar[i] == 1) {
//                t = i - 2;
//                break;
//            }
//        }
//        if (t > 0) {
//            int m = n % t;
//            if (m == 0) m = t;
//            cout << ar[m] << endl;
//        }
//        else {
//            cout << ar[n] << endl;
//        }
//    }
//    return 0;
//}

#include <iostream>
#include <vector>
using namespace std;
struct map {
    long long mat[2][2];
    map() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};
map multiply(map m1, map m2) {
    map res;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res.mat[i][j] = (res.mat[i][j] + m1.mat[i][k] * m2.mat[k][j]) % 7;
            }
        }
    }
    return res;
}
map quick_pow(map a, int n) {
    map res;
    res.mat[0][0] = 1; res.mat[1][1] = 1;
    while (n > 0) {
        if (n & 1) res = multiply(res, a);
        a = multiply(a, a);
        n >>= 1;
    }
    return res;
}
int main() {
    int A, B, n;
    while (cin >> A >> B >> n && (A != 0 || B != 0 || n != 0)) {
        if (n == 1 || n == 2) {
            cout << 1 << endl;
            continue;
        }
        map T;
        T.mat[0][0] = A % 7;
        T.mat[0][1] = B % 7;
        T.mat[1][0] = 1;
        T.mat[1][1] = 0;
        map result_mat = quick_pow(T, n - 2);
        long long ans = (result_mat.mat[0][0] * 1 + result_mat.mat[0][1] * 1) % 7;
        cout << ans << endl;
    }
    return 0;
}
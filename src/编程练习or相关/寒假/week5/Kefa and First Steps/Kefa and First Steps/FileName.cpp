#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
int ar[505];
int dp[505][505];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> ar[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = 505;
        }
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = 1;
                continue;
            }
            if (ar[i] == ar[j]) {
                if (len == 2) dp[i][j] = 1;
                else dp[i][j] = dp[i + 1][j - 1];
            }
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}
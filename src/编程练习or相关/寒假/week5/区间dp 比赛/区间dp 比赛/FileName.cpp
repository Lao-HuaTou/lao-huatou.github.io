#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll s[2005];
ll dp[2005][2005];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    sort(s + 1, s + n + 1);
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = (s[j] - s[i]) + min(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}
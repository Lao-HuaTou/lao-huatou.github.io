#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e9;
int main() {
    int N;
    cin >> N;
    vector<int> a(2 * N + 1, 0);
    vector<int> sum(2 * N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        a[i + N] = a[i];
    }
    for (int i = 1; i <= 2 * N; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    vector<vector<int>> dp1(2 * N + 1, vector<int>(2 * N + 1, INF));
    vector<vector<int>> dp2(2 * N + 1, vector<int>(2 * N + 1, 0));
    for (int i = 1; i <= 2 * N; i++) {
        dp1[i][i] = 0;
    }
    for (int len = 2; len <= N; len++) {
        for (int i = 1; i <= 2 * N - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                int score = sum[j] - sum[i - 1];
                dp1[i][j] = min(dp1[i][j], dp1[i][k] + dp1[k + 1][j] + score);
                dp2[i][j] = max(dp2[i][j], dp2[i][k] + dp2[k + 1][j] + score);
            }
        }
    }
    int minans = INF, maxans = 0;
    for (int i = 1; i <= N; i++) {
        minans = min(minans, dp1[i][i + N - 1]);
        maxans = max(maxans, dp2[i][i + N - 1]);
    }
    cout << minans << endl;
    cout << maxans << endl;
    return 0;
}
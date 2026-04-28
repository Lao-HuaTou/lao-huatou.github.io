#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    sort(h.begin() + 1, h.end());
    int l = 1, r = h[n] - h[1];
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int last = 1; 
        int cnt = 1;
        for (int i = 2; i <= n; i++) {
            if (h[i] - h[last] >= mid) {
                cnt++;
                last = i;
            }
        }
        if (cnt >= m) {
            ans = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    cout << ans;
    return 0;
}
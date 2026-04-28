#include<iostream>
#include<vector>
#include<algorithm>
#define int long long

using namespace std;
struct Boat {
    int a, b;
};
int n;
vector<Boat>ar;
vector<int> compress(vector<Boat>& ar) {
    vector<int>point;
    for (int i = 0; i < n; i++) {
        point.push_back(ar[i].a);
        point.push_back(ar[i].b);
    }
    sort(point.begin(), point.end());
    point.erase(unique(point.begin(), point.end()), point.end());
    return point;
}
vector<int> apply(vector<int>& point) {
    vector<int>line;
    int m = point.size();
    vector<int>diff(m, 0);
    for (int i = 0; i < n; i++) {
        int l = lower_bound(point.begin(), point.end(), ar[i].a) - point.begin();
        int r = lower_bound(point.begin(), point.end(), ar[i].b) - point.begin();
        diff[l]++;
        diff[r]--;
    }
    line.resize(m, 0);
    line[0] = diff[0];
    for (int i = 1; i < m; i++) {
        line[i] = line[i - 1] + diff[i];
    }
    return line;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    ar.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> ar[i].a >> ar[i].b;
    }
    vector<int>point = compress(ar);
    vector<int>line = apply(point);
    int ans = 0;
    int m = point.size();
    for (int i = 0; i < m - 1; i++) {
        if (line[i]) {
            ans += point[i + 1] - point[i];
        }
    }
    cout << ans;
    return 0;
}
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;
string s1, s2;

void solve() {
    if (!(cin >> n)) return;
    cin >> s1 >> s2;
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] == '#') cnt1++;
        if (s2[i] == '#') cnt2++;
    }
    // 逻辑：如果一行全黑而另一行不是，由于构造限制，这种情况无解
    if ((cnt1 == n) ^ (cnt2 == n)) {
        cout << "No" << endl;
        return;
    }

    // 逻辑：两行全黑的情况，直接全填满，这就是一个巨大的实心矩形
    if (cnt1 == n && cnt2 == n) {
        cout << "Yes" << endl;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < n; j++) cout << '#';
            cout << endl;
        }
        return;
    }
    // 初始化 7 行，默认为全 '.'
    vector<string> ans(7, string(n, '.'));
    ans[0] = s1;
    ans[6] = s2;

    // 第 2 行和第 6 行填充：原行是 '.' 的地方填 '#'
    // 这样原行的 '#' 就能通过对角线（8连通）勾住这些新 '#'
    for (int i = 0; i < n; i++) {
        if (s1[i] == '.') ans[1][i] = '#';
        if (s2[i] == '.') ans[5][i] = '#';
    }

    int y = 0, Y = 0;
    // 寻找 y：在第 2 行找一个空位，它左右两边有 #，说明它能勾住第 1 行的 #
    for (int i = 0; i < n; i++) {
        bool has_neighbor = (i > 0 && ans[1][i - 1] == '#') || (i < n - 1 && ans[1][i + 1] == '#');
        if (ans[1][i] == '.' && has_neighbor) {
            y = i;
            break;
        }
    }
    // 同理寻找 Y
    for (int i = 0; i < n; i++) {
        bool has_neighbor = (i > 0 && ans[5][i - 1] == '#') || (i < n - 1 && ans[5][i + 1] == '#');
        if (ans[5][i] == '.' && has_neighbor) {
            Y = i;
            break;
        }
    }

    // 这里的赋值顺序和范围是全题最关键的地方（为了避开 4 连通）
    ans[2][y] = '#';
    ans[4][Y] = '#';

    int l = min(y, Y), r = max(y, Y);
    // 这一段必须严格保持，它是为了让中间行只和上下行通过对角线接触
    if (l == r || l == r - 1) {
        ans[3][l] = '#';
    }
    for (int i = l + 1; i <= r - 1; i++) {
        ans[3][i] = '#';
    }

    cout << "Yes" << endl;
    for (int i = 0; i < 7; i++) {
        cout << ans[i] << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if(!(cin >> T)) T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
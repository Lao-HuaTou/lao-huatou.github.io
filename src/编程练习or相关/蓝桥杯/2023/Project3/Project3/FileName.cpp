#include <iostream>
#include<algorithm>
using namespace std;
int n;
const int N = 1e5 + 5;
struct node {
    int a, b;
    bool operator<(const node& x)const {
        if (b == x.b)return a < x.a;
        return b < x.b;
    }
}s[N];

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i].a >> s[i].b;
    }
    sort(s + 1, s + n + 1);
    int ans = 0; int now = 0;
    for (int i = 1; i <= n; i++) {
        if (now <= s[i].b) {
            now += s[i].a;
            ans++;
        }

    }
    cout << ans;



    return 0;
}
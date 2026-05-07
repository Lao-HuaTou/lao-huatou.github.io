#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m;
long long a[N];
string s;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    if (!(cin >> n >> m)) return 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> s;
    int cur = 0;
    int step = 1;
    int skip = 0;
    int draw = 0;
    int card_ptr = 0; 

    while (card_ptr < m) {

        if (a[cur] <= 0) {
            cur = (cur + step + n) % n;
            continue;
        }


        if (skip) {
            skip = 0;
            cur = (cur + step + n) % n;
            continue; 
        }

        char card = s[card_ptr];
        if (draw) {
            a[cur]++;
            draw = 0; 
        } else {
            a[cur]--; 
        }
        if (card == 'S') skip = 1;
        else if (card == 'R') step = -step;
        else if (card == 'D') draw = 1;
        card_ptr++;
        cur = (cur + step + n) % n;
    }
    if(draw)
        a[(cur + n + step) % n] += 2;
    for (int i = 0; i < n; i++)
        cout << a[i] << "\n";
    return 0;
}
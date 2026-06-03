#include<bits/stdc++.h>
using namespace std;

int m, d1, n, d2, k;

// 判断闰年
bool run(int year)
{
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) return true;
        } else {
            return true;
        }
    }
    return false;
}


int getdays(int m, int d, int year)
{

    int x[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (run(year)) {
        x[2] = 29;
    }
    
    int days = 0;

    for (int i = 1; i < m; i++) {
        days += x[i];
    }
    if (!run(year) && m == 2 && d == 29) {
        d = 28;
    }
    
    return days + d;
}

void solve(){
    cin >> m >> d1 >> n >> d2 >> k;
    int xq = 3; 
    bool has_answer = false;
    
    for (int i = 2025; i <= 2025 + k - 1; i++)
    {
        int day_m = getdays(m, d1, i);
        int day_n = getdays(n, d2, i);

        int wk_m = (day_m + xq - 1) % 7;
        int wk_n = (day_n + xq - 1) % 7;
        
        if (wk_m == wk_n) {
            cout << i << "\n";
            has_answer = true;
        }

        if (run(i)) {
            xq = (xq + 366) % 7;
        } else {
            xq = (xq + 365) % 7;
        }
    }
    
    if (!has_answer) {
        cout << "No Answer\n";
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    // cin >> tt;
    for (int i = 1; i <= tt; i++){
        solve();
    }
    return 0;
}
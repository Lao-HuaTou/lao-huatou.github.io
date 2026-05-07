#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int maxq[N];
int minq[N];
int limit, n;
int maxh, maxt, minh, mint;
vector<pair<int, int>> d;

bool ok(int x){
    int maxv = maxh < maxt ? max(x, d[maxq[maxh]].second) : x;
    int minv = minh < mint ? min(x, d[minq[minh]].second) : x;
    return maxv - minv >= limit;
}

void push(int id){
    int v = d[id].second;
    while(maxh<maxt&&d[maxq[maxt-1]].second<=v){
        maxt--;
    }
    maxq[maxt++] = id;
    while(minh<mint&&d[minq[mint-1]].second>=v){
        mint--;
    }
    minq[mint++] = id;
}
void pop(int id){
    if(maxh<maxt&&maxq[maxh]==id){
        maxh++;
    }
    if(minh<mint&&minq[minh]==id){
        minh++;
    }
}
int get_diff() {
    if (maxh < maxt && minh < mint) 
        return d[maxq[maxh]].second - d[minq[minh]].second;
    return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> limit;
    d.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> d[i].first >> d[i].second;
    }
    sort(d.begin(), d.end());
    int ans = 2e9;
    for (int l = 0, r = 0; l < n; l++)
    {
        while(r < n && get_diff() < limit){
            push(r++);
        }

       if (get_diff() >= limit) {//若为到达边界而跳出 则说明没有雨滴能实现时间差大于limit 不能更新ans
            ans = min(ans, d[r-1].first - d[l].first);
        } 
        pop(l);
    }
    if (ans == 2e9) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
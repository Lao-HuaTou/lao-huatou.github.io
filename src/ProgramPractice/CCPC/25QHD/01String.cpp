#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct node
{
    int l, r, p;
};
string s;
int pos[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    vector<int> st;
    int m = s.length();
    if(m&1){
        cout << -1 << endl;
        return 0;
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < m; i++)
    {
        if(!st.empty()&&s[i]!=s[st.back()]){
            pos[st.back()] = i;
            st.pop_back();
        }
        else {
            st.push_back(i);
        }
    }
    if(!st.empty()){
        cout << -1 << endl;
        return 0;
    }
    vector<node> d;
    d.push_back({0, m - 1, 1});
    while(!d.empty()){
        node cur = d.back();
        d.pop_back();
        int l = cur.l;
        int r = cur.r;
        int p = cur.p;
        if (l > r)
            continue;
        int op = s[l] == '0' ? 1 : 2;
        ans.push_back({p, op});
        int lenA = pos[l] - l + 1;
        d.push_back({l+1, pos[l]-1, p});
        d.push_back({pos[l] + 1, r, p + (lenA / 2) + 1});
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
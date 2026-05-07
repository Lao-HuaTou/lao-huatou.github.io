#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    if(s.find("isallyouneed")!=string::npos){
        cout << "Yes\n";
        string ans = s.substr(0, s.find("isallyouneed"));
        cout << ans;
    }
    else
        cout << "No\n";
    return 0;
}
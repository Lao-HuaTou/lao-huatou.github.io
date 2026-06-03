#include<bits/stdc++.h>
using namespace std;

string s, p;
int n, m;
int dp[25][25];// 0 not 1 yes  2 no

int f1(int i,int j){
    if(i==n){
        if(j==m){
            return 1;
        }
        else
            return j + 1 < m && p[j+1] == '*' && f1(i, j + 2);
    }
    else {
        if(j==m){
            return 0;
        }
        if(j+1==m||p[j+1]!='*'){
            return (s[i] == p[j]||p[j+1]=='.') && f1(i + 1, j + 1);
        }
        else {
            bool ck1 = f1(i, j + 2);
            bool ck2 = (p[j] == '.' || s[i] == p[j]) && f1(i + 1, j);
            return ck1 || ck2;
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s >> p;
    n = s.length();
    m = p.length();
    int ans = f1(0, 0);
    if(ans)
        cout << "TRUE";
    else
        cout << "FALSE";
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

string n1, n2;
int ck(int x,int y){
    if((x==0&&y==0)||(x==2&&y==0)||(x==0&&y==2)||(x==2&&y==2)){
        return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    cin >> n1 >> n2;
    for (int i = 0; i < n;i++){
        if(!ck(n1[i],n2[i])){
            cout << 0;
            return 0;
        }
    }
    cout << 1;
    return 0;
}
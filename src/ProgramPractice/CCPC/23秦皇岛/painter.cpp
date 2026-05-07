#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct edge
{
    int to, nxt;
} e[N << 1];
int c = 0;
int head[N];
void add(int u,int v){
    e[++c] = {v, head[u]};
    head[u] = c;
}
int disa[N], disb[N];
int cnta, cntb;
int n, a, b;
int ck = 1;
void dfs(int u,int f, int d,int type)
{
    if(type){
        for (int i = head[u]; i;i=e[i].nxt){
            int v = e[i].to;
            if(v!=f){
                disa[v] = d + 1;
                dfs(v, u, d + 1, type);
            }
        }
    }
    else {
        for (int i = head[u]; i;i=e[i].nxt){
            int v = e[i].to;
            if(v!=f){
                disb[v] = d + 1;
                dfs(v, u, d + 1, type);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> a >> b;
    for (int i = 0,u,v; i < n - 1;i++){
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(a,0,0,1);
    dfs(b,0,0,0);
    for (int i = 1; i <= n;i++){
        if(disa[i]<=disb[i])
            cnta++;
        else
            cntb++;
    }
    if(cnta>=cntb)
        cout << "Alice";
    else
        cout << "Bob";
    return 0;
}
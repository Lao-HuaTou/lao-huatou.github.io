#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
#define int long long
const int INF = 1e18;
const int N = 100025;
using namespace std;

struct edge {
	int u, v, w, nxt;
}e[2*N];
int head[N];
int c;
void add(int u, int v, int w) {
	e[++c] = { u,v,w,head[u] };
	head[u] = c;
}


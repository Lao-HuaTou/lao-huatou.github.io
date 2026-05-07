#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int n, m;
int inde[305],dp[305];

struct edge {
	int to, nxt, w;
}e[305];
int head[305];
int s[305];
int cnt = 0;
void add(int u, int v, int w) {
	e[++cnt].to = v;
	inde[v]++;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
priority_queue<pair<int,int>>q;
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int v,w; cin >> v >> w;
		s[i] = w;
		add(i,v,w);
	}
	for (int i = 1; i <= n; i++) {
		if (inde[i] == 0)q.push({s[i],i});
	}
	int now = 0;
	while (!q.empty() && now <= m) {
		int s = q.top().first,cur=q.top().second;
		q.pop();
		
	}
}

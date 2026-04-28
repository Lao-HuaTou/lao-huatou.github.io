#include<iostream>
#include<vector>
typedef long long ll;
using namespace std;
int n;
char c[500005];
int nxt[500005], to[500005], head[500005];
int cnt=1;
int p[500005];
ll sum[500005], diff[500005];
void add(int u, int v)//u father      v  son
{
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt++;

}
int top=0,s[500005];
void dfs(int x) {//x 为节点 
	int temp = 0;
	if (c[x] == ')') {
		if (top) {
			temp = s[top];
			diff[x] = diff[p[temp]] + 1;
			top--;
		}
	}
	else if(c[x]=='(') {
		s[++top]=x;
	}
	sum[x] = sum[p[temp]] + diff[x];
	for (int i = head[x]; i; i = nxt[i])
		dfs(to[i]);
	if (temp) s[++top] = temp;//回溯 若本次用‘）’消耗了一个‘（’ 则在原位置加上‘（’
	else if (top) top--;//若本次为‘（’ 则撤回
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> c[i];
	}
	for (int i = 2; i <= n; i++)//i son     
	{
		int u;//father
		cin >> u;
		add(u, i);
		p[i] = u;
	}
	dfs(1);
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans ^= sum[i]*(ll)i;
	}
	cout << ans << "\n";
	return 0;
}
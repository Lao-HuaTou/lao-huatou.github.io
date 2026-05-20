#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<algorithm>
#include<string>
using namespace std;
#define int long long

const int N = 2e5 + 5;

vector<pair<int, int>> mat[N];
int n, q;
int f[N];
int deg[N];
int ans[N];
void build(int n)
{
	for (int i = 0; i <= n;i++){
		f[i] = 0;
		deg[i] = 0;
		ans[i] = 0;
	}
}

void solve()
{
	cin >> n >> q;
	build(n);
	for (int i = 2; i <= n; i++)
	{
		cin >> f[i];
	}
	int w;
	for (int i = 2; i <= n;i++){
		cin >> w;
		mat[f[i]].push_back({i, w});
	}
	int s = 0;
	int mod = mat[1].size();
	while (q--)
	{
		cin >> s;
        int ss=s;
		int cur = 1;
		s %= mod;
		if(ans[ss]){
			cout << ans[ss] << "\n";
			continue;
		}
		while(mat[cur].size()){
			cur = mat[cur][s % mat[cur].size()].first;
			s += mat[cur][s % mat[cur].size()].second;
		}
        ans[ss]=cur;
		cout << cur<<"\n";
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int tt;
	cin >> tt;
	tt = 1;
	while (tt--) {
		solve();
	}
	return 0;
}



	// cin >> n >> m;
	// int D = n + 1;
	// for (int x = 1; x <= n; x++)
	// {
	// 	for (int y = 1; y <= m;y++){
	// 		cin >> mat[(x - 1) * D + y];//(x,y)
	// 	}
	// }
	// for (int x = 1; x <= n; x++)
	// {
	// 	for (int y = 1; y <= m;y++){
	// 		for (int d = 0; d <= 3;d++){
	// 			if(d==0){
	// 				dp[(x-1)*D+y][d]=mat[(x-1)*D+y]=='A':
	// 			}
	// 		}
	// 	}
	// }


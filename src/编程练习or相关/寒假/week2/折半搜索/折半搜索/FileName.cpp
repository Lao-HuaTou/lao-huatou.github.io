//#include<iostream>
//#include<vector>
//using namespace std;
//typedef long long ll;
//ll ans = 0;
//ll m;
//int n;
//vector<ll>ar;
//void solve(ll m,int start){
//	if (start == n) {
//		ans++;
//		return;
//	}
//	solve(m, start + 1);
//
//	if (m >= ar[start]) solve(m - ar[start], start + 1);
//}
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> n >> m;
//	ar.resize(n);
//
//	for (int i = 0; i < n; i++) cin >> ar[i];
//	solve(m,0);
//	cout << ans << endl;
//}

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
ll ans = 0;
ll m;
int n;
vector<ll>ar;
vector<ll>sumA, sumB;
void dfs(int start,int end,ll carry,vector<ll>&tem) {
	if (start == end) {
		tem.push_back(carry);
		return;
	}
	dfs(start + 1, end, carry, tem);
	if (carry <= m - ar[start]) {
		dfs(start + 1, end, carry + ar[start], tem);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	ar.resize(n);
	for (int i = 0; i < n; i++) cin >> ar[i];
	dfs(0, n / 2, 0,sumA);
	dfs(n / 2, n, 0,sumB);
	sort(sumB.begin(), sumB.end());
	for (ll t : sumA) {
		if(t<=m)
		ans += upper_bound(sumB.begin(),sumB.end(),m-t) - sumB.begin();
	}
	cout << ans << endl;
}

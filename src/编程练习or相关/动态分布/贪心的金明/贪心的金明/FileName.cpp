#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct item {
	int price;
	int imp;
};
int main()
{
	int n, m;
	cin >> n >> m;
	vector<item>goods(m+1);
	for (int i = 1; i <= m; i++)
		cin >> goods[i].price>> goods[i].imp;
	vector<int>ans(n + 1, 0);
	for (int i = 1; i <= m; i++)
	{
		for (int j = n; j >= goods[i].price; j--)
		{
			ans[j] = max(ans[j], ans[j - goods[i].price] + goods[i].price*goods[i].imp);
		}
	}
	cout << ans[n];
	return 0;
}
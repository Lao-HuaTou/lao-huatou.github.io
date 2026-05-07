#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main()
{
	int a, b, m;

	cin >> a >> b >> m;
	int lv[40] = { 0,990,1010,1970,2030,2940,3060,3930,4060,4970,5030,5990,6010,7000 };
	lv[0] = 0;

	for (int i = 0; i < m; i++)
	{
		cin >> lv[14 + i];
	}
	sort(lv, lv + m+14);
	int t = 14 + m;
	vector<int>f(t, 0);
	f[0] = 1;
	for (int i = 1; i < 14 + m; i++) {//枚举所有点 
		for (int j = 0; j < i; j++) {//枚举这个点之前的点 
			if (lv[i] - lv[j] >= a && lv[i] - lv[j] <= b) {//如果这两个点之间的距离符合要求 
				f[i] += f[j];//这个点可以获得前面那个点的所有可能 
			}
		}
	}
	cout << f[t-1];
	return 0;
}
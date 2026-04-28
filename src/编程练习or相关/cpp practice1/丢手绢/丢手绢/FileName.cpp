#include<iostream>
using namespace std;
int cnt[100005];
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		if (x == 0)
			cnt[i]++;
		else if (x > 0)
		{
			int y = (i + x) % n;
			if (y == 0)//注意这里如果是第n个人，会被模成0，要特判
				y = n;
			cnt[y]++;
		}
		else
		{
			x %= n;
			int y = i + x;
			if (y < 1)
				y += n;//这部分同上
			cnt[y]++;
		}
	}
	int maxn = 0;
	for (int i = 1; i <= n; i++)
		maxn = max(maxn, cnt[i]);//找最大值
	for (int i = 1; i <= n; i++)
		if (cnt[i] == maxn)
			cout << i << " ";//相同就输出
	return 0;
}

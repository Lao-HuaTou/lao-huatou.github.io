#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[50000];
int main()
{
	int w, n,ans=0;
	cin >> w >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + 1 + n);
	int l = 1, r = n;
	while (l < r)
	{
		if (a[l] + a[r] > w) {
			ans++;
			r--;
		}
		else {
			ans++;
			l++;
			r--;
		}
	}
	cout << ans;
	return 0;
}
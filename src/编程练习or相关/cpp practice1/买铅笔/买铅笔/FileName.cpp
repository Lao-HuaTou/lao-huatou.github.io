#include<iostream>
using namespace std;
int main()
{
	int n;
	int m, c;
	cin >> n ;
	int tem = 3;
	int ans=0, cost;
	while(tem--)
	{
		cin >> m >> c;
		if (n % m == 0)
			cost = n / m * c;
		else cost = (n / m + 1) * c;
		ans = ans > cost ? cost : ans;
	}
	cout << ans;
	return 0;
}
#include<iostream>
using namespace std;	
int main()
{
	int n;
	cin >> n;
	if (n >= 0)
	{
		int m = n;
		int tem=0;
		while (m)
		{
			tem *= 10;
			tem = m % 10;
			m /= 10;
		}
		cout << tem;
	}
	else
	{
		n = -n;
		int m = n;
		int tem = 0;
		while (m)
		{
			tem *= 10;
			tem += m % 10;
			m /= 10;
		}
		cout << -tem;
	}
	return 0;
}
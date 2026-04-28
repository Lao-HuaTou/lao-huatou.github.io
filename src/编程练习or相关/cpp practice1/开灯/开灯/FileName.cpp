#include <iostream>
#include<vector>
using namespace std;
int main()
{
	int n;
	cin >> n;
	vector<int>ar(2000000, 0);
	for (int l = 0; l < n; l++)
	{
		
		double a;
		cin >> a;
		int t;
		cin >> t;
		for (int i = 1; i <= t; i++)
		{
			ar[(int)(a * i)]++;
		}
	}
	for (int i = 0; i < 2000000; i++)
	{
		if (ar[i] % 2 == 1)
		{
			cout << i;
			break;
		}
	}
	return 0;
}
#include<iostream>
#include<cmath>
using namespace std;
int zs(int n) {
	if (n == 4) return 0;
	else {
		for (int i = 2; i <= (int)sqrt(n); i++)
		{
			if (n % i == 0)
				return 0;
		}
		return 1;
	}
}
int main()
{
	int a;
	cin >> a;
	for (int i = 4; i <= a; i += 2)
	{
		for (int j = 2; j <= i / 2; j++) {
			if (zs(j) == 1)
			{
				if (zs(i - j) == 1) {
					cout << i << "=" << j << "+" << i - j << endl;
					break;
				}
			}
		}
	}
	return 0;
}
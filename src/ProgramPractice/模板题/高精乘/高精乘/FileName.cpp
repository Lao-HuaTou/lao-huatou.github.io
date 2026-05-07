#include<iostream>
using namespace std;
int a[10000];
int n,l=1;
void mul(int x) {
	for (int i = 0; i < l; i++)
	{
		a[i] *= 2;
	}
	for (int i = 0; i < l; i++)
	{
		if (a[i] >= 10) {
			a[i] %= 10;
			a[i + 1]++;
		}
	}
	if (a[l] > 0) l++;
}
int main()
{
	cin >> n;
	a[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		mul(i);
	}
	a[0]--;
	for (int i = l - 1; i >= 0; i--)
		cout << a[i];
	return 0;
}
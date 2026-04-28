#include<iostream>
using namespace std;
int main()
{
	int g, boy, n;
	cin >> g >> boy >> n;
	int x1 = 1;
	while (x1 <= 100000)
	{
		if (g % x1 == 0 && boy % (n - x1) == 0&&n-x1>=0)
		{
			printf("%d %d", x1, n - x1);
			return 0;
		}
		else x1++;
		if (n - x1 < 0)break;
	}
	printf("No Solution");
	return 0;
}
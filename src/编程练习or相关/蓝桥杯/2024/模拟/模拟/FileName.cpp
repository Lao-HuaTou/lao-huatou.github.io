#include<iostream>
using namespace std;
int s[11] = { 13,1,2,3,5,4,4,2,2,2 };//每个数字的笔画
int main()
{
	int a = 0, b = 0, y = 2000, m = 1, d = 1;
	while (1)
	{
		if (m % 2 == 1 && m <= 7)//大月
		{
			if (d > 31)
			{
				m++;
				d = 1;
			}
		}
		else if (m % 2 == 0 && m >= 8)//大月
		{
			if (d > 31)
			{
				m++;
				d = 1;
			}
		}
		else if (m == 2)//二月
		{
			if (y % 100 == 0 && y % 400 == 0)//闰年
			{
				if (d > 29)
				{
					m++;
					d = 1;
				}
			}
			else if (y % 100 != 0 && y % 4 == 0)//闰年
			{
				if (d > 29)
				{
					m++;
					d = 1;
				}
			}
			else//平年
			{
				if (d > 28)
				{
					m++;
					d = 1;
				}
			}
		}
		else//小月
		{
			if (d > 30)
			{
				m++;
				d = 1;
			}
		}
		if (m > 12)
		{
			y++;
			m = 1;
		}
		if (y == 2024 && m == 4 && d == 14)
		{
			cout << b;//输出
			return 0;
		}
		int sum = s[y % 10];//统计笔画
		sum += s[(y % 100) / 10] + s[(y % 1000) / 100] + s[y / 1000];
		sum += s[m % 10] + s[m / 10];
		sum += s[d % 10] + s[d / 10];
		if (sum > 50)
		{
			b++;
		}
		else
		{
			a++;
		}
		d++;
	}
}

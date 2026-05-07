#include<stdio.h>
int a[100];
void bubble(int n)
{
	for (int i = 0; i < n - 1; i++)  // 控制轮数
	{
		int flag = 0;
		for (int j = 0; j < n - i - 1; j++)  // ✅ 每轮减少比较次数
			if (a[j] > a[j + 1])
			{
				int r = a[j];
				a[j] = a[j + 1];
				a[j + 1] = r;
				flag = 1;
			}
		if (!flag) break;  // 提前终止
	}
}
int cha(int n)
{
	for (int i = 1; i < n; i++)
	{
		int k = a[i];
		int j = i - 1;
		while (j >= 0 && k < a[j])
		{
			
			a[j + 1] = a[j];
			j--;
		}
		a[j+1] = k;
	}
}
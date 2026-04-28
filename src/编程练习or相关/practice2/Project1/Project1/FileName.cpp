#include<stdio.h>
int result[20];int n;
void chai(int left, int first, int d)
{
	if (left == 0)
	{
		printf("%d=", n);
		for (int i = 0; i < d; i++)
		{
			printf("%d", result[i]);
			if (i != d-1) printf("+");
			else 
			printf("\n");
		}
	}
	else
	{
		for (int i = first; i >= 1; i--)
		{
			if (i > left)continue;
			result[d] = i;
			chai(left - i, i, d+1);
		}
	}
	
}
int main()
{
	
	scanf_s("%d", &n);
	for (int first = n - 1; first >= 1; first--)
	{
		result[0] = first;
		chai(n - first, first, 1);
	}
	return 0;
}
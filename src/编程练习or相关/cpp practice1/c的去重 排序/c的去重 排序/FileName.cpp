#include<stdio.h>
#define max(a,b)(a>b?a:b)
#define min(a,b)(a>b?b:a)
int main()
{
	int n; long long s[105000];
	scanf_s("%d", &n);
	long long min1 = 1e18 + 1, max1 = -1;
	for (int i = 0; i < n; i++)
	{
		scanf_s("%lld", &s[i]);
		max1 = max(max1, s[i]);
		min1 = min(min1, s[i]);
	}
	printf("%lld\n", max1 - min1);
	return 0;
}
//int main()
//{
//	long long n; scanf_s("%lld", &n);
//	int c1 = 0, c2 = 0; 
//	long long a[2500], b[2500];
//	for (int i = 1; i * i <= n; i++) {
//		if (n % i == 0) {
//			a[c1++] = i;
//			if (i * i != n)b[c2++] = n / i;
//		}
//	}
//	for (int i = 0; i < c1; i++)
//		printf("%lld ", a[i]);
//	for (int i = c2 - 1; i >= 0; i--)
//	{
//		printf("%lld", b[i]);
//		if (i != 0)printf(" ");
//	}
//	printf("\n");
//	return 0;
//}
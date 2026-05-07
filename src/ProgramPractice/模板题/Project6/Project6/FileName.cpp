#include<stdio.h>
int a, b, c, d;
double f(int x)
{
	return a * x * x * x + b * x * x + c * x + d;
}
double get(double l, double r)
{
	double mid;
	while (r - l > 1e-4)
	{
		double mid = (l + r) / 2;
		if (f(mid) * f(l) <= 0) r = mid;
		else l = mid;
	}
	return mid;
}
int main()
{
	scanf_s("%d %d %d %d", &a, &b, &c, &d);
	double root[3];
	int cnt = 0;
	for (int i = -100; i <= 100; i++)
	{
		double l = i, r = i + 1.0;
		if (f(l) < 1e-8) root[cnt++] = l; continue;
		if (cnt == 3) break;
		if (f(l) * f(r) < 0) root[cnt++] = get(l, r);
	}
	printf("%.2lf %.2lf %.2lf", root[0], root[1], root[2]);
	return 0;
}
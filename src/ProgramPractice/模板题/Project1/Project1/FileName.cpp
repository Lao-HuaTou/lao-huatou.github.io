#include<stdio.h>
#include<stdlib.h>
char shu[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void change(int n, int b)
{
	if (n >= b)
		change(n / b, b);
	printf("%c", shu[n % b]);
}
int main()
{
	int n, b;
	scanf_s("%d%d", &n, &b);
	change(n, b);
	return 0;
}
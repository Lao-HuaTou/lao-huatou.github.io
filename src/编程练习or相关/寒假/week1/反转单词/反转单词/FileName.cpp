#include<stdio.h>
#include<string.h>
void reverseword(char *w,int l,int r)
{
	char temp[1100];
	int len = r - l;
	for (int i = 0; i <= len; i++)
	{
		temp[i] = w[r - i];
	}
	for (int i = 0; i <= len; i++)
	{
		w[l+i] = temp[i];
	}
}
int main()
{
	int t;
	scanf_s("%d", &t);
	getchar();
	while (t--)
	{
		char line[1001];
		gets_s(line, 1001);
		int start = 0;
		int len = strlen(line);
		for (int i = 0; i <= len; i++)
		{	
			if (line[i] == ' ' || line[i] == '\0')
			{
				reverseword(line, start, i - 1);
				start = i + 1;
			}
		}
		printf("%s\n", line);
	}
	return 0;
}
#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	for (char c : s)
	{
		c = 'a' + (c + n - 'a') % 26;
		cout << c;
	}
	return 0;
}



/*
#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    char s[51];
    scanf("%s", s);

    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        s[i] = 'a' + (c - 'a' + n) % 26;
        printf("%c", s[i]);
    }
    return 0;
}
*/
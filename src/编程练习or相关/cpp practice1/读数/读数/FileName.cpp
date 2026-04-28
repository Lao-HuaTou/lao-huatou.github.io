#include<iostream>
#include<string>

using namespace std;
char C;
string S;
int n, A, B;
void Work(int Lim)
{
	for (char i : S)
	{
		if (i == 'W')A++;
		if (i == 'L')B++;
		if (max(A, B) >= Lim && abs(A - B) >= 2)
		{
			cout << A << ":" << B << endl;
			A = 0, B = 0;
		}
	}
	printf("%d:%d\n\n", A, B);
	A = B = 0;
}
int main()
{
	while (cin >> C)
	{
		if (C == 'E')break;
		S += C;
	}
	Work(11), Work(21);
	return 0;
}









#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char C;
char S[100000];  // 需要预定义数组大小
int len = 0;     // 字符串长度
int A, B;

void Work(int Lim)
{
    for (int i = 0; i < len; i++)  // C语言的标准循环



    {
        char current = S[i];
        if (current == 'W') A++;
        if (current == 'L') B++;

        if ((A >= Lim || B >= Lim) && abs(A - B) >= 2)
        {
            printf("%d:%d\n", A, B);
            A = 0, B = 0;
        }
    }
    printf("%d:%d\n\n", A, B);
    A = B = 0;
}

int main()
{
    while (scanf("%c", &C) != EOF)
    {
        if (C == 'E') break;
        S[len++] = C;
    }
    Work(11);
    Work(21);
    return 0;
}




while (scanf("%c ", &c[cnt]) != EOF) {// 使用scanf进行读入
    cnt++;// 计数器++
}

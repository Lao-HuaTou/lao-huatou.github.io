#include<iostream>
#include<string>

using namespace std;
int main()
{
	int num1 = 1, num2 = 1;
	string one, two;
	cin >> one >> two;
	for (char c : one)//***********************************遍历one中的元素，c++11特性
	{
		num1 *= c - 'A' + 1;
	}
	for (char c : two)
	{
		num2 *= c - 'A' + 1;
	}
	if ((num1 % 47) == (num2 % 47))
		cout << "GO";
	else
		cout << "STAY";
	return 0;
}



/*                    C

#include <stdio.h>

int main()
{
    int num1 = 1, num2 = 1;
    char one[100], two[100];
    char *p;
    
    scanf("%s%s", one, two);
    
    // 用指针遍历第一个字符串
    p = one;
    while(*p != '\0') {
        num1 *= (*p - 'A' + 1);
        p++;
    }
    
    // 用指针遍历第二个字符串
    p = two;
    while(*p != '\0') {
        num2 *= (*p - 'A' + 1);
        p++;
    }
    
    if ((num1 % 47) == (num2 % 47))
        printf("GO");
    else 
        printf("STAY");
    
    return 0;
}*/
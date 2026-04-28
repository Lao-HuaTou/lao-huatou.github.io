#include<iostream>
using namespace std;
int area(int n) {
	int i = 1;
	while (1) {
		if (n > i * (i + 1) / 2 && n <= (i + 1) * (i + 2) / 2) return i;
		i++;
	}
}
int main()
{
	int n;
	cin >> n;
	int a = area(n);
	if (a & 1) {//ÆæÊı
		int left = n - a * (a + 1) / 2;
		cout << left << "/" << a+2-left;
	}
	else {//Å¼Êı
		int left = n - a * (a + 1) / 2;
		cout << a+2-left << "/" <<  left;
	}
	return 0;
}
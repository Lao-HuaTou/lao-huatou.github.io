#include<iostream>
#include<cmath>
using namespace std;
int a;
void print(int n) {
	for (int i = 14; i >= 0; i--)
	{
		if (pow(2, i) <= n) {
			
			if (i == 0) cout << "2(0)";
			else if (i == 1) cout << "2";
			else {
				cout << "2(";
				print(i);
				cout << ")";
			}
			n -= pow(2, i);
			if (n != 0) cout << "+";
		}
	}
}
int main()
{
	cin >> a;
	print(a);
	return 0;
}
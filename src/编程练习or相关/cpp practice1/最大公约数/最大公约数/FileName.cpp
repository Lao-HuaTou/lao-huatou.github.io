#include<iostream>
using namespace std;
int yueshu(int a, int b) {
	int tem;
	while (b != 0)
	{
		tem = a % b;
		a = b;
		b = tem;
	}
	return a;
}
int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int n = a * c, m = b * d;
	int tem=yueshu(m,n);
	n /= tem;
	m /= tem;
	cout << n << " " << m << endl;
	return 0;
}
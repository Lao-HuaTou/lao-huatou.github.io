#include<iostream>
using namespace std;
int a, n, m, x;
int fib(int n) {
	int a1 = 1, a2 = 1;
	if (n == 1 || n == 2) return 1;
	for (int i = 3; i <= n; i++)
	{
		int tem = a1 + a2;
		a1 = a2;
		a2 = tem;
	}
	return a2;
}
int hefib(int n) {
	int sum = 0;
	if (n == 0) return 0;
	for (int i = 1; i <= n; i++) sum += fib(i);
	return sum;
}
int main() {
	cin >> a >> n >> m >> x;
	if (n <= 2) {
		cout << a;
		return 0;
	}
	else if (n == 3) {
		if (x <= 2)cout << a;
		else cout << 2 * a;
		return 0;
	}
	else if (n == 4)
	{
		if (x <= 2)cout << a;
		else cout << 2 * a;
		return 0;
	}
	else
	{
		int t = (m - (2 + hefib(n - 1 - 4)) * a) / hefib(n - 1 - 3);
		if (x <= 2)cout << a;
		else if (x == 3)cout << 2 * a;
		else if (x < n - 1)cout << (2 + hefib(x - 4)) * a + hefib(x - 3) * t;
		else cout << m;
	}
	return 0;
}
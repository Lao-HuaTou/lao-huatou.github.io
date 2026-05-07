#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned long long ull;
void solve(int n, ull k)
{
	if (n == 0) return;
	ull half = 1ull << (n - 1);
	if (k < half) {
		putchar('0');
		solve(n - 1, k);
	}
	else {
		putchar('1');
		solve(n - 1, (half - 1) - ( k - half));
	}
}
int main()
{
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
	int n; ull k;
	cin >> n >> k;
	solve(n, k);
	return 0;
}
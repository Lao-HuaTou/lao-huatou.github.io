#include<iostream> 
using namespace std;
int main() {
	long long n = 2021041820210418, a[1000000], x = 0, ans = 0;
	for (long long i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			a[x++] = i;
			if ((n / i) != i) {
				a[x++] = n / i;// 如果 i*i=n话  i就会被记录两次,所以加个条件 (n/i)!=i。
			}
		}

	}
	for (long long i = 0; i < x; i++) {
		for (long long j = 0; j < x; j++) {
			if (a[i] * a[j] > n)continue;//这里有个优化,如果前两个数的乘积已经大于n了,第三个数就没必要乘了。
			for (long long k = 0; k < x; k++) {
				if (a[i] * a[j] * a[k] == n)ans++;
			}
		}
	}
	cout << ans;
	return 0;
}

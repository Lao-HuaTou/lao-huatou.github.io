#include<iostream>
using namespace std;
#define int long long
int q;

int quickpower(int a, int b)
{
    int ans = 1, base = a % q;  // 初始时先取模
    while (b > 0)
    {
        if (b & 1)  // 如果b是奇数
        {
            ans = (ans * base) % q;
        }
        base = (base * base) % q;
        b = b >> 1;  // 或者 b /= 2;
    }
    return ans;
}

signed main() {
    int a, b;
    cin >> a >> b >> q;

    // 处理特殊情况
    if (q == 1) {
        cout << a << "^" << b << " mod " << q << "=0";
        return 0;
    }

    int ans = quickpower(a, b);
    cout << a << "^" << b << " mod " << q << "=" << ans;
    return 0;
}





long long qpow(int base, int p) {
	if (p == 1) {
		return base;
	}
	else if (p == 0) {
		return 1;
	}
	else {
		long long ans = qpow(base, p / 2) ;
		long long ans1 = ans * ans ;
		if (p % 2 == 1) {
			ans1 = ans1 * base;
		}
		return ans1;
	}
}




int quickpower(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1)
			ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}



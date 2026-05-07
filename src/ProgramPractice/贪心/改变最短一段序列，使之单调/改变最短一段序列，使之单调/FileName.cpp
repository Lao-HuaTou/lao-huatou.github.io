#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	int n; cin >> n;
	int maxn = 0;
	int r = 0;
	int ar[200000];
	for (int i = 0; i < n; i++) {
		cin >> ar[i];
		if (ar[i] >= maxn) {
			maxn = ar[i];
		}
		else {
			r = i;
		}
	}
	int l = n - 1, minn = 1e9;;
	for (int i = n - 1; i >= 0; i--) {
		if (ar[i] <= minn) {
			minn = ar[i];
		}
		else l = i;
	}
	cout << max(0, r - l + 1);
	return 0;
}
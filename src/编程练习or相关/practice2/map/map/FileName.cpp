#include<iostream>
#include<map>
using namespace std;
const int N = 2e5 + 10;
int n, x;
map<int, int>mp;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &x), ++mp[x];
	for (auto it = mp.begin(); it != mp.end(); ++it)
		printf("%d %d\n", it->first, it->second);
	return 0;
}

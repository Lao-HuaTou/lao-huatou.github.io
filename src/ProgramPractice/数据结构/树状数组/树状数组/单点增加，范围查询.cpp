#include<iostream>
using namespace std;
const int N = 1e5;
int tree[N], int ar[N];
int n;
int lowbit(int x) { return x & (-x); }
void add(int i, int val) {
	while (i <= n) {
		tree[i] += val;
		i -= lowbit(i);
	}
}
int sum(int i) {
	int ans = 0;while (i > 0) {
		ans += tree[i];
		i -= lowbit(i);
	}return ans;
}
#include<iostream>
#include<vector>
#include<climits>
using namespace std;
vector<int> ar;
int l, r;

int kadane(int n) {
	int max_sum = INT_MIN; 
	int current_sum = 0; 
	int temp_l = 0;  

	for (int i = 0; i < n; ++i) {
		current_sum += ar[i];
		if (current_sum > max_sum) {
			max_sum = current_sum;
			l = temp_l;
			r = i;
		}
		if (current_sum < 0) {
			current_sum = 0;
			temp_l = i + 1; 
		}
	}
	return max_sum;
}

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int n; cin >> n;
		ar.resize(n);
		for (int j = 0; j < n; j++)
		{
			cin >> ar[j];
		}
		int ans = kadane(n);
		cout << "Case " << i + 1 << ":" << endl;
		printf("%d %d %d\n\n", ans, l+1, r+1);
	}
	return 0;
}


//DP
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
vector<int>ar;
int l, r;
int dp(int n, int start, int tar, int carry, int c) {
	int ans = INT_MIN;
	if (start >= n) {
		return ans;
	}
	if (c == tar) {
		if(carry > ans) {
			ans = carry;
			l = start - tar + 1;
			r = start;
		}
	}
	else {
			carry += ar[start];
			ans = max(ans, dp(n, start + 1, tar, carry, c + 1));
	}
	return ans;
}
int main()
{
	int t;
	cin >> t;

	for(int i=0;i<t;i++)
	{
		int n; cin >> n;
		ar.resize(n);
		for (int j = 0; j < n; j++)
		{
			cin >> ar[j];
		}
		int ans = INT_MIN;
		l = -1; r = -1;
		for (int j = 1; j <= n; j++)
		{
			for (int start = 0; start <= n - j; start++) {
				int current = dp(n, start, j, 0, 0);
				ans = max(ans, current);
			}
		}
		cout << "Case " << i + 1 << ":"<<endl;
		printf("%d %d %d\n\n", ans, l, r);
	}
	return 0;
}
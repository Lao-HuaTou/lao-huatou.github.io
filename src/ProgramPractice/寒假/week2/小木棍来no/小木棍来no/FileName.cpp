#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n;	
int ans = 0,sum=0,Max=0;
vector<int>ar;
vector<bool>used;
int ck(int L,int cur,int start,int c)
{
	if (c == sum / L) return 1;
	for (int i = start; i < n; i++) {
		if (used[i] || cur + ar[i] > L) continue;
		used[i] = true;
		if (cur + ar[i] < L) {
			
			if (ck(L, cur+ar[i], i + 1, c)) return 1;
		}
		if (cur + ar[i] == L) {
			if (ck(L, 0 , 0 , c+1)) return 1;
		}
		used[i] = false;
		if (cur == 0) return 0;                         //¼ôÖ¦
		while (i + 1 < n && ar[i] == ar[i + 1]) {       //¼ôÖ¦
			i++;
		}
	}
	return 0;
}
int main()
{
	 cin >> n;
	 ar.resize(n, 0);
	 used.resize(n, false);

	for (int i = 0; i < n; i++) {
		cin >> ar[i];
		sum += ar[i];
		Max = max(Max, ar[i]);
	}
	sort(ar.rbegin(), ar.rend());
	for (int i = Max; i <= sum; i++) {
		if (sum % i != 0) continue;
		fill(used.begin(),used.end(),false);
		if (ck(i,0,0,0)) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}
#include<iostream>
using namespace std;
int mat[26];
int l, r;
int ans = 0;
void ck() {
	if (!((mat[1] + mat[2] + mat[3] + mat[4] + mat[5]) % 5))return;
	if (!((mat[6] + mat[7] + mat[8] + mat[9] + mat[10]) % 5))return;
	if (!((mat[11] + mat[12] + mat[13] + mat[14] + mat[15]) % 5))return;
	if (!((mat[16] + mat[17] + mat[18] + mat[19] + mat[20]) % 5))return;
	if (!((mat[21] + mat[22] + mat[23] + mat[24] + mat[25]) % 5))return;
	if (!((mat[1] + mat[6] + mat[11] + mat[16] + mat[21]) % 5))return;
	if (!((mat[2] + mat[7] + mat[12] + mat[17] + mat[22]) % 5))return;
	if (!((mat[3] + mat[8] + mat[13] + mat[18] + mat[23]) % 5))return;
	if (!((mat[4] + mat[9] + mat[14] + mat[19] + mat[24]) % 5))return;
	if (!((mat[5] + mat[10] + mat[15] + mat[20] + mat[25]) % 5))return;
	if (!((mat[1] + mat[7] + mat[13] + mat[19] + mat[25]) % 5))return;
	if (!((mat[5] + mat[9] + mat[13] + mat[17] + mat[21]) % 5))return;

	ans++;

}
void dfs(int x) {
	if (x == 26) {
		ck();
		return;
	}
	else {
		if (l <= 12) {
			l++;
			mat[x] = 1;
			dfs(x + 1);
			l--;
		}
		if(r<=11){
			r++;
			mat[x] = 0;
			dfs(x + 1);
			r--;
		}
	}

}
int main() {
	dfs(1);
	cout << ans;
	return 0;
}
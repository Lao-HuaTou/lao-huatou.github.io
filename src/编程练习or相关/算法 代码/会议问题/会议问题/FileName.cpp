#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct mt {
	int x, y;
};
bool cmp(const mt& a, const mt& b) {
	return a.y < b.y;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	if (n == 0) {
		printf("0");
		return 0;
	}
	vector<mt>mting(n);
	for (int i = 0; i < n; i++)
	{
		cin >> mting[i].x >> mting[i].y;
	}
	sort(mting.begin(), mting.end(), cmp);
	int ans = 1;
	int cur = 0;
	for (int nxt = 1; nxt < n; nxt++) {
		if (mting[nxt].x >= mting[cur].y) {
			ans++;
			cur = nxt;
		}
	}
	cout << ans;
	return 0;
}
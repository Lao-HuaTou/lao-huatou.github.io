#include<iostream>
#include<vector>
#include<algorithm>
typedef struct OP {
	int a, b;
}op;
using namespace std;
vector<op>ar;
int n;
vector<int> compress() {
	vector<int>point;
	for (int i = 0; i < n; i++) {
		point.push_back(ar[i].a);
		point.push_back(ar[i].b + 1);
	}
	sort(point.begin(), point.end());
	point.erase(unique(point.begin(), point.end()), point.end());
	return point;//point[i] ÊÇ³õÊ¼Öµ
}
vector<int> apply(vector<int>&point)
{
	vector<int>line;
	int m = point.size();
	vector<int>diff(m, 0);
	diff[0] = 0;
	for (int i = 0; i < n; i++) {
		int l = lower_bound(point.begin(), point.end(), ar[i].a) - point.begin();
		int r = lower_bound(point.begin(), point.end(), ar[i].b + 1) - point.begin();
		diff[l] += 1;
		if (r < m)
			diff[r] -= 1;
	}
	line.resize(m);
	line[0] = diff[0];
	for (int i = 1; i < m; i++) {
		line[i] = line[i - 1] + diff[i];
	}
	return line;
}
int main()
{
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		ar.resize(n);
		for (int i = 0; i < n ; i++) {
			cin >> ar[i].a>>ar[i].b;
		}
		vector<int>point = compress();
		vector<int>line = apply(point);
		int ans = -1,id=-1;
		for (int i = 0; i < line.size(); i++) {
			if (line[i] > ans) {
				ans = line[i];
				id = i;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
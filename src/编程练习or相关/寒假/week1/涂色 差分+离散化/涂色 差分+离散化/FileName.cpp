#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct opration {
	int a, b;
	char c;
}op;
vector<op>dot;
vector<int> compress(){		//去重
	vector<int> point;
	for (int i = 0; i < dot.size(); i++) {
		point.push_back(dot[i].a);
		point.push_back(dot[i].b+1);
	}
	sort(point.begin(), point.end());
	point.erase(unique(point.begin(), point.end()), point.end());
	return point;
}
vector<int> apply(vector<int>& point) {
	int m = point.size();
	vector<int> color(m - 1, 0);      // 颜色数组
	vector<bool> covered(m - 1, false); // 标记是否被覆盖

	// 从后往前处理操作
	for (int i = dot.size() - 1; i >= 0; i--) {
		int l = lower_bound(point.begin(), point.end(), dot[i].a) - point.begin();
		int r = lower_bound(point.begin(), point.end(), dot[i].b + 1) - point.begin();

		// 只覆盖还未被覆盖的段
		for (int j = l; j < r; j++) {
			if (!covered[j]) {    
				covered[j] = true;   
				color[j] = (dot[i].c == 'w') ? 1 : 0; 
			}
		}
	}
	return color;
}
//vector<int> apply(vector<int>& point) {
//	int l, r;
//	int m = point.size();
//	vector<int>diff(m,0);
//	for (int i = 0; i < dot.size();i++) {
//		l = lower_bound(point.begin(), point.end(),dot[i].a)-point.begin();
//		r = lower_bound(point.begin(), point.end(), dot[i].b + 1) - point.begin();
//		int val = (dot[i].c == 'b' ? -1 : 1);
//		diff[l] += val;
//		if (r < m) diff[r] -= val;
//	}
//	vector<int> sum(m,0);//前缀和
//	sum[0] = diff[0];
//	for (int i = 1; i < m; i++) {
//		sum[i] = sum[i - 1] + diff[i];
//	}
//	vector<int> color(m - 1, 0);
//	for (int i = 0; i < m - 1; i++) {
//		color[i] = (sum[i] > 0 ? 1 : 0);
//	}
//	return color;
//}
int main()
{
	int t;
	while (cin>>t)
	{
		dot.clear();
		dot.resize(t);
		for (int i = 0; i < t; i++)
		{
			cin >> dot[i].a >> dot[i].b >> dot[i].c;
		}
		vector<int> point = compress();
		vector<int> color = apply(point);
		long long ans = -1, cur = 0;
		int l = -1, r = -1;
		int start = -1;
		for (int i = 0; i < color.size(); i++) {
			if (color[i] == 1) {
				if (cur == 0) start = point[i];
				cur += point[i + 1] - point[i];
				if (cur > ans) {
					ans = cur;
					l = start;
					r = point[i + 1] - 1;
				}
			}
			else {
				cur = 0;
			}
		}
		if (ans == -1) cout << "Oh, my god" << endl;
		else cout << l << " " << r << endl;
	}
	return 0;
}
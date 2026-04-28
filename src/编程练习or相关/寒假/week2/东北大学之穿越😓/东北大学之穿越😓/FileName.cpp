#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
string tob(int n) {
	string s="";
	for (int i = 7; i >= 0; i--) {
		s += (n >> i) & 1 ? '1' : '0';
	}
	return s;
}
string rever(string s) {
	string temp = s;
	reverse(temp.begin(), temp.end());
	return temp;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<string>ans;
	set<string>ck;
	for (int i = 0; i < 256; i++) {
		string s = tob(i);
		string res = rever(s);
		string f = min(s, res);
		if (ck.find(f) == ck.end()) {//没找到f
			ck.insert(f);
			ans.push_back(f);
		}
	}
	sort(ans.begin(), ans.end());
	string opration; cin >> opration;
	if (opration == "write") {
		int year;
		cin >> year;
		int tar = year - 1923;
		cout << ans[tar] << endl;
	}
	else {
		string s; cin >> s;
		string res = rever(s);
		string f = min(s, res);
		for (int i = 0; i < ans.size(); i++)
		{
			if (ans[i] == f) {
				cout << 1923 + i << endl;
				break;
			}
		}
	}
	return 0;
}
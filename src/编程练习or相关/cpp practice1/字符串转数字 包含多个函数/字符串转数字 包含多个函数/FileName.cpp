#include <iostream>
#include<string>
using namespace std;

string s1, s2;

int y(string s) {
	if (s.find("BC") != string::npos) {//判断是不是 BC
		int pos = s.find(' ');
		int num = stoi(s.substr(0, pos));//取数
		return -num + 1;
	}
	else {
		int pos = s.find(' ');
		int num = stoi(s.substr(pos + 1));
		return num;
	}
}

signed main()
{
	getline(cin, s1);//整行读入
	getline(cin, s2);
	cout << abs(y(s1) - y(s2));
	return 0;
}

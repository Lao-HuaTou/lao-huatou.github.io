#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
int f(int n) {
	int back = 1;
	while (n % 2 == 0)
	{
		n /= 2;
		back *= 2;
	}
	return back;
}
int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	string s3, s4;
	s3 = s1; s4 = s2;
	sort(s3.begin(), s3.end());
	sort(s4.begin(), s4.end());
	if (s3 != s4) {
		cout << "NO";
		return 0;
	}
    else {
        int len1 = s1.length();
        int groupCount = f(len1);     // 组数
        int groupSize = len1 / groupCount;  // 每组长度

        vector<string> c1(groupCount);
        vector<string> c2(groupCount);

        for (int i = 0; i < groupCount; i++) {
            c1[i] = s1.substr(i * groupSize, groupSize);
            c2[i] = s2.substr(i * groupSize, groupSize);
        }

        // 对子串排序后再比较
        sort(c1.begin(), c1.end());
        sort(c2.begin(), c2.end());

        if (c1 == c2) {
            cout << "YES";
        }
        else {
            cout << "NO";
        }
        return 0;
    }
}
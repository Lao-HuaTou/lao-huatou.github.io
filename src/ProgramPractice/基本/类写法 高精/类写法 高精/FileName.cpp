#include <iostream>
#include<string>
#include<vector>
using namespace std;
class BINT {         //类类型，这里可以替换成struct
private:                              //私有成员
	string s;
public:                               //公有成员
	BINT(string x = "0") : s(x) {};    //初始化构造函数
	const BINT operator+(const BINT& t) { //重载加法运算
		string sa = s, sb = t.s;
		int la = sa.size(), lb = sb.size();
		int m = max(la, lb);         //获得最大数字长度
		vector<int> a(m + 1, 0), b(m + 1, 0), c(m + 1, 0);
		for (int i = 0; i < la; i++) //逆序存数a
			a[i] = sa[la - 1 - i] - '0';
		for (int i = 0; i < lb; i++) //同上
			b[i] = sb[lb - 1 - i] - '0';
		for (int i = 0; i < m; i++) {
			c[i] += a[i] + b[i];     //对位相加
			c[i + 1] += c[i] / 10;   //处理进位
			c[i] = c[i] % 10;        //去掉进位
		}
		while (!c[m] && m) m--;      //去除前导零
		string res;
		for (int i = m; i >= 0; i--)
			res += char(c[i] + '0');
		return BINT(res);            //临时BINT类型
	}
	const BINT operator*(const BINT& t) {
		string sa = s, sb = t.s;
		int la = sa.size(), lb = sb.size();
		int m = la + lb;
		vector<int>a(m + 1, 0), b(m + 1, 0), c(m + 1, 0);
		for (int i = 0; i < la; i++)   //逆序存数
			a[i] = sa[la - 1 - i] - '0';
		for (int i = 0; i < lb; i++)
			b[i] = sb[lb - 1 - i] - '0';
		for (int i = 0; i < la; i++)
			for (int j = 0; j < lb; j++) {
				c[i + j] += a[i] * b[j];
				c[i + j + 1] += c[i + j] / 10;
				c[i + j] %= 10;
			}
		while (!c[m] && m) m--;
		string res;
		for (int i = m; i >= 0; i--)
			res += char(c[i] + '0');
		return BINT(res);
	}
	bool operator<(const BINT& t) {
		string b = t.s;
		if (s.size() < b.size()) return true;
		if (s.size() == b.size() && s < b) return true;
		return false;
	}
	void operator=(const string& x) {      //重载赋值运算符
		s = x;
	}
	void operator=(const long long& x) {   //重载赋值运算符
		s = to_string(x);
	}
	void operator=(const int& x) {   //重载赋值运算符
		s = to_string(x);
	}
	friend istream& operator>>(istream& in, BINT& t) {
		in >> t.s;         //友元函数 重载>>右移运算符为输入
		return in;
	}
	friend ostream& operator<<(ostream& out, const BINT& t) {
		out << t.s;        //友元函数 重载 <<左移运算符为输出
		return out;        //const允许输出常量
	}
};
//但如果你想把这个 BINT 存进你的个人代码库，当成一个以后随时能用的“大整数万能模板”，
//你还需要花时间把 operator-（减法）、operator / （除法）、operator % （取模）以及对负数的判断给补充完整才行。










int n, m;
string s;
BINT dp[45][45], D[45][45];
int main() {
	cin >> n >> m >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			D[i][j] = s.substr(i, j - i + 1);
			//			cout << D[i][j] << " ";
		}
	for (int i = 1; i <= n; i++)
		dp[i][0] = D[1][i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (j >= i) break;
			for (int k = j; k < i; k++)
				if (dp[i][j] < dp[k][j - 1] * D[k + 1][i])
					dp[i][j] = dp[k][j - 1] * D[k + 1][i];
		}

	cout << dp[n][m];
	return 0;
}

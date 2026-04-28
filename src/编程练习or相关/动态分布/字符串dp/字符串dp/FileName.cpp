#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
int main()
{
	int n;
	cin >> n;
	vector<string>s(n + 1);
	for (int i = 1; i <= n; i++)cin >> s[i];
	vector<int>dp(n + 1, 1);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1;j<=n; j++)
		{
			if (s[i][0] == s[j][0] && s[j].find(s[i])==0)
				dp[j] = max(dp[j], dp[i] + 1);  // 修正：赋值和正确的状态转移
			ans = max(ans, dp[j]);
		}
	}
	cout <<ans;
	return 0;
}








using namespace std;
int n, f[2010], ans;
string s[2010];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		cin >> s[i];

	for (int i = 1; i <= n; i++)
	{
		f[i] = 1;
		for (int j = 1; j < i; j++)
			if (s[j] == s[i].substr(0, s[j].size())) //从s[i]的0号位置截取s[j]长度的子串，判断是否与s[j]相等。
				f[i] = max(f[j] + 1, f[i]);
		ans = max(f[i], ans);
	}
	printf("%d", ans);
	return 0;
}





//字典树
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 2010;
struct edge {
	int link[27];
	int s;
}t[MAXN];
int n, m, cnt;
int ans;
void zbr(char* c)
{
	int ansm = 0;
	int p = 0;
	int i;
	int len = strlen(c);
	for (int i = 0; i < len; i++)
	{
		int zz = c[i] - 'a' + 1;
		if (t[p].link[zz] == 0)
			t[p].link[zz] = ++cnt;
		p = t[p].link[zz];
		ansm += t[p].s;
	}
	if (ansm >= ans)
		ans = ansm + 1;
	t[p].s++;
}
int main()
{
	int i;
	char c[110] = "";
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", c);
		zbr(c);
	}
	printf("%d\n", ans);
	return 0;
}


//map

using namespace std;
map <string, int> f;
int n, ans;
string s[2005];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
		f[s[i]]++;
	}
	for (int i = 1; i <= n; i++)
	{
		int sum = 0; string a = "";
		for (int j = 0; j < s[i].size(); j++) a += s[i][j], sum += f[a];
		ans = max(ans, sum);
	}
	cout << ans;
	return 0;
}
f["i"] = 1

f["int"] = 1

f["integer"] = 1

f["intern"] = 1

f["internet"] = 1

2. 计算每个字符串的前缀出现次数总和
字符串 "i"：
前缀 "i"：出现1次

总和：1

字符串 "int"：
前缀 "i"：出现1次

前缀 "in"：出现0次（不存在）

前缀 "int"：出现1次

总和：1 + 0 + 1 = 2

字符串 "integer"：
前缀 "i"：出现1次

前缀 "in"：出现0次

前缀 "int"：出现1次

前缀 "inte"：出现0次

前缀 "integ"：出现0次

前缀 "intege"：出现0次

前缀 "integer"：出现1次

总和：1 + 0 + 1 + 0 + 0 + 0 + 1 = 3

字符串 "intern"：
前缀 "i"：出现1次

前缀 "in"：出现0次

前缀 "int"：出现1次

前缀 "inte"：出现0次

前缀 "inter"：出现0次

前缀 "intern"：出现1次

总和：1 + 0 + 1 + 0 + 0 + 1 = 3

字符串 "internet"：
前缀 "i"：出现1次

前缀 "in"：出现0次

前缀 "int"：出现1次

前缀 "inte"：出现0次

前缀 "inter"：出现0次

前缀 "intern"：出现1次

前缀 "interne"：出现0次

前缀 "internet"：出现1次

总和：1 + 0 + 1 + 0 + 0 + 1 + 0 + 1 = 4


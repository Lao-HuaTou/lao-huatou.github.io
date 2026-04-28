#include <iostream>
#include <string>
using namespace std;
const int maxN = 105;
char sixt[20] = "0123456789ABCDEF";
int n;
string m;
bool hw(string a) { //判断回文
	string s = a; //把 a 赋值给 s
	reverse(s.begin(), s.end()); //反转字符串 s
	return s == a; //判断 a 和 s 是否相等
}
string add(int k, string b) { //高精度加法过程，推广到 k 进制
	string a = b;
	reverse(a.begin(), a.end());
	int numa[maxN], numb[maxN], numc[maxN];
	int len = a.length(), lenc = 1;
	string ans;
	for (int i = 0; i < len; i++) {
		if (isdigit(a[i])) numa[len - i] = a[i] - '0'; //对于十六进制的特判，如果是数字减去 0 ，下同
		else numa[len - i] = a[i] - 'A' + 10; //如果不是数字减去 A 再加上 10
		if (isdigit(b[i])) numb[len - i] = b[i] - '0';
		else numb[len - i] = b[i] - 'A' + 10;
	}
	int x = 0;
	while (lenc <= len) {
		numc[lenc] = numa[lenc] + numb[lenc] + x;
		x = numc[lenc] / k; //把除以 10 修改为除以 k
		numc[lenc] %= k; //这里把对 10 取模修改为对 k 取模
		lenc++;
	}
	numc[lenc] = x;
	while (numc[lenc] == 0) lenc--;
	for (int i = lenc; i >= 1; i--) ans += sixt[numc[i]];
	return ans;
}
int main() {
	cin >> n >> m;
	for (int i = 0; i <= 30; i++) { //模拟过程
		if (hw(m)) { //如果是回文数就输出步骤数
			printf("STEP=%d", i);
			return 0;
		}
		else m = add(n, m);
	}
	printf("Impossible!"); //如果超过 30 步则输出 Impossible!
	return 0;
}


















#include <cstdio>
#include <cstring>
const int S = 303;//一次加法顶多多一位，所以顶多多30位，也就是130位左右。我开大一点，开到300.
int n, a[S], l;
char c[S], d[S];
inline void add()
{
	for (int i = 0; i < l; ++i)
		d[l - i - 1] = c[i];
	l += 2;//可能有进位，所以我们干脆在前面先多空个两位
	for (int i = 0; i < l; ++i)
	{
		c[i] += d[i];
		if (c[i] >= n) c[i + 1]++, c[i] -= n;
	}
	while (!c[l - 1]) --l;//大不了多余的前导0再减回来嘛~~简化思维~~
}
inline bool pd()
{
	for (int i = 0; i < l; ++i)
		if (c[i] != c[l - 1 - i]) return false;
	return true;
}
int main()
{
	scanf("%d%s", &n, c); l = strlen(c);
	for (int i = 0; i < l; ++i)
	{
		if (c[i] >= '0' && c[i] <= '9') c[i] -= '0';
		else c[i] = c[i] - 'A' + 10;
	}
	int step = 0;
	while (!pd())
	{
		++step;
		if (step > 30) break;
		add();
	}
	if (step <= 30) printf("STEP=%d\n", step);
	else puts("Impossible!");
	return 0;
}
































#include <bits/stdc++.h> 
using namespace std;
int n, q[1000001], l, w[1000001], ans;
string s;
void init()
{
	int j = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			q[++j] = s[i] - '0';
		}
		else
		{
			q[++j] = s[i] - 'A' + 10;
		}
	}
}
void add(int a[], int b[])
{
	for (int i = 1; i <= l; i++)
	{
		a[i] += b[i];
		a[i + 1] += a[i] / n;
		a[i] %= n;
	}
	if (a[l + 1] > 0)
	{
		l++;
	}
}
bool f(int a[])
{
	int ln = l;
	int i = 1;
	int j = l;
	while (ln--)
	{
		if (ln < l / 2)
		{
			break;
		}
		if (a[i] != a[j])
		{
			return false;
		}
		i++;
		j--;
	}
	return true;
}
void turn(int a[])
{
	int j = 0;
	for (int i = l; i >= 1; i--)
	{
		w[++j] = a[i];
	}
}
int main()
{
	cin >> n >> s;
	init();
	l = s.length();
	while (!f(q))
	{
		turn(q);
		add(q, w);
		ans++;
		if (ans > 30)
		{
			break;
		}
	}
	if (ans > 30)
	{
		printf("Impossible!");
	}
	else
	{
		printf("STEP=%d", ans);
	}
	return 0;
}

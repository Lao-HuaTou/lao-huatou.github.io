#include<iostream>
#include<string>
char sixt[20] = "0123456789ABCDEF";
using namespace std;
#define maxN 300
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
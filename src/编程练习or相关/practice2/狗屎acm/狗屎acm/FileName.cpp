#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 1e3 + 5, rate = 1200;//rate代表小时化为分钟的进率 
int n, m, down;
int intt(char x) {//巧用ASCII码进行char类转int类 
	return x - '0';
}
struct node {
	string name;
	int AC, miao;
}a[MAXN];
char ch[MAXN];
bool cmp(node x, node y) {
	if (x.AC == y.AC) {//正确数相等 
		if (x.miao == y.miao) return x.name < y.name;//时间相等就比较名字字典序 
		return x.miao < y.miao;//否则比较时间 
	}
	return x.AC > y.AC;//通用的判断 
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n + 1; i++) {
		cin >> a[i].name;
		if (i != n + 1 && a[i].name == "NijeZivotJedanACM") down = i;//如果检测到了NijeZivotJedanACM的做题记录，就记录当前下标 
		for (int j = 1; j <= m; j++) {
			cin >> ch + 1;
			if (ch[1] == '-') continue;//没通过就删了吧 
			else {
				a[i].miao += 3600 * intt(ch[5]) + 60 * (10 * intt(ch[7]) + ch[8]) + 10 * intt(ch[10]) + intt(ch[11]);
				a[i].miao += (intt(ch[2]) - 1) * rate;
				a[i].AC++;
			}
		}
	}
	a[down] = a[n + 1];//把最后一位的数据全部塞进NijeZivotJedanACM的记录中 
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		if (a[i].name == "NijeZivotJedanACM") {
			printf("%d", i);
			return 0;
		}
	}
	return 0;
}

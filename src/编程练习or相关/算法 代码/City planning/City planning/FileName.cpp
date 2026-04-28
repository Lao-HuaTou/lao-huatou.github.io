#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct building {
	int a, b, c, d;
	int value;
}bu;
long long ans;
bool cmp(const bu& a, const bu& b) {
    return a.value > b.value;
}
vector<bu>bl;
void cut(bu cur, int id,int val) {
    if (id < 0) {
        ans += (long long)(cur.d - cur.b) * (cur.c - cur.a) * val;
        return;
    }
    bu& high = bl[id];
    if (cur.a >= high.c || cur.c <= high.a || cur.b >= high.d || cur.d <= high.b) {
        cut(cur, id - 1, val);
		return;
    }
    if (cur.d > high.d){ 
        bu up = { cur.a,high.d,cur.c,cur.d, val };
        cut(up, id - 1, val);
        cur.d = high.d;
    }
    if (cur.b < high.b) {
		bu down = { cur.a,cur.b,cur.c,high.b, val };
        cut(down, id - 1, val);
		cur.b = high.b;
    }
    if (cur.a < high.a) {
        bu left = { cur.a,cur.b,high.a,cur.d,val };
        cut(left, id - 1, val);
		cur.a = high.a;
    }
    if (cur.c > high.c) {
		bu right = { high.c,cur.b,cur.c,cur.d,val };
		cut(right, id - 1, val);

    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t; cin >> t;
    for (int number = 1; number <= t;number++) {
		int n; cin >> n;
        bl.clear();
        bl.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> bl[i].a >> bl[i].b >> bl[i].c >> bl[i].d >> bl[i].value;
		}
        sort(bl.begin(), bl.end(), cmp);
        ans = 0;
        for (int i = 0; i < n; i++) {
            cut(bl[i], i - 1, bl[i].value);
        }
		cout << "Case " << number << ": "<<ans<<'\n';
	}
}


/**
 * 矩形切割核心递归函数
 * @param r: 当前正在处理的矩形（或者是切碎后的子矩形）
 * @param rects: 排序后的矩形数组
 * @param idx: 当前正在与哪个高价值矩形进行比对
 * @param val: 当前矩形的单位价值
 */
// 如果已经和所有更高价值的矩形比对完了，剩下的面积就是纯贡献
    // 如果两个矩形完全不相交，直接跳过当前高价值矩形，去比对下一
   // 如果有交集，开始切割。将当前矩形 r 分解成最多 4 个不与 high 重叠的子矩形
    // 1. 上方部分
// 更新当前矩形边界，避免重复计算
   
    // 2. 下方部分

    // 3. 左侧部分

    // 4. 右侧部分

    // 切割剩下的中心部分就是重叠部分，直接抛弃（因为它归属于更高价值的矩形）



#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int a,b,n;
double memory[11][11][11][11][11];
int sum(vector<vector<int>>&pre,int x1, int y1, int x2, int y2) {
	return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
}
double cut(int k, int x1, int y1, int x2, int y2, vector<vector<int>>& pre) {
	if (memory[k][x1][y1][x2][y2]>=0) return memory[k][x1][y1][x2][y2];
	if (k == 1) {
		double s = sum(pre, x1, y1, x2, y2);
		memory[k][x1][y1][x2][y2] = s * s;
		return s * s;
	}
	double res = 1e18;
	for (int i = x1; i < x2; i++) {//hang
		res = min(res, cut(k - 1, i + 1, y1, x2, y2, pre) + cut(1, x1, y1, i, y2,pre));
		res = min(res, cut(k - 1, x1, y1, i, y2, pre) + cut(1, i + 1, y1, x2, y2, pre));
	}
	for (int i = y1; i < y2; i++) {//lie
		res = min(res, cut(k - 1, x1, i+1, x2, y2, pre) + cut(1, x1, y1, x2, i, pre));
		res = min(res, cut(k - 1, x1, y1, x2, i, pre) + cut(1, x1, i+1, x2, y2, pre));
	}
	memory[k][x1][y1][x2][y2] = res;
	return res;
}
int main()
{
	freopen("separation.in", "r", stdin);
	freopen("separation.out", "w", stdout);
	cin >> a >> b >> n;
	vector<vector<int>>map(a + 1, vector<int>(b + 1,0));
	vector<vector<int>>pre(a + 1, vector<int>(b + 1, 0));
	for (int x = 1; x <= a; x++) {
		for (int y = 1; y <= b; y++) {
			cin >> map[x][y];
			pre[x][y] = map[x][y];
		}
	}
	for (int x = 1; x <= a; x++) {
		for (int y = 1; y <= b; y++) {
			pre[x][y] += pre[x - 1][y] + pre[x][y - 1] - pre[x - 1][y - 1];
		}
	}
	for (int k = 0; k <= n; k++)
		for (int x1 = 0; x1 <= a; x1++)
			for (int y1 = 0; y1 <= b; y1++)
				for (int x2 = 0; x2 <= a; x2++)
					for (int y2 = 0; y2 <= b; y2++)
						memory[k][x1][y1][x2][y2] = -1.0;

	double minsum = cut(n, 1, 1, a, b, pre);
	double total = (double)pre[a][b];
	double ave = total / n;
	double ans = sqrt(minsum/n-ave*ave);
	printf("%.2f", ans);
	return 0;
}

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int a, b, n;
double memory[15][15][15][15][15];
int sum(vector<vector<int>>& pre, int x1, int y1, int x2, int y2) {
    return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
}
double cut(int k, int x1, int y1, int x2, int y2, vector<vector<int>>& pre) {
    if (memory[k][x1][y1][x2][y2] >= 0) return memory[k][x1][y1][x2][y2];
    if (k == 1) {
        double s = (double)sum(pre, x1, y1, x2, y2);
        return memory[k][x1][y1][x2][y2] = s * s;
    }
    double res = 1e18;
    for (int i = x1; i < x2; i++) {
        res = min(res, cut(k - 1, i + 1, y1, x2, y2, pre) + cut(1, x1, y1, i, y2, pre));
        res = min(res, cut(k - 1, x1, y1, i, y2, pre) + cut(1, i + 1, y1, x2, y2, pre));
    }
    for (int i = y1; i < y2; i++) {
        res = min(res, cut(k - 1, x1, i + 1, x2, y2, pre) + cut(1, x1, y1, x2, i, pre));
        res = min(res, cut(k - 1, x1, y1, x2, i, pre) + cut(1, x1, i + 1, x2, y2, pre));
    }
    return memory[k][x1][y1][x2][y2] = res;
}

int main() {
    freopen("separation.in", "r", stdin);
    freopen("separation.out", "w", stdout);
	cin >> a >> b >> n;
    vector<vector<int>> pre(a + 1, vector<int>(b + 1, 0));
    for (int x = 1; x <= a; x++) {
        for (int y = 1; y <= b; y++) {
            int val;
            cin >> val;
            pre[x][y] = val + pre[x - 1][y] + pre[x][y - 1] - pre[x - 1][y - 1];
        }
    }
    for (int k = 0; k < 15; k++)
        for (int x1 = 0; x1 < 15; x1++)
            for (int y1 = 0; y1 < 15; y1++)
                for (int x2 = 0; x2 < 15; x2++)
                    for (int y2 = 0; y2 < 15; y2++)
                        memory[k][x1][y1][x2][y2] = -1.0;

    double min_sq_sum = cut(n, 1, 1, a, b, pre);
    double total = (double)pre[a][b];
    double ave = total / (double)n;
    double ans = sqrt(max(0.0, min_sq_sum / (double)n - ave * ave));
    printf("%.2f\n", ans);
    return 0;
}



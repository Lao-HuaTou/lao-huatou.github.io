#include <iostream>
#include <algorithm>

using namespace std;

// 绝对差不超过限制的最长连续子数组
const int MAXN = 100005;

// 窗口内最大值的更新结构（单调队列）
int maxDeque[MAXN];
// 窗口内最小值的更新结构（单调队列）
int minDeque[MAXN];

int maxh, maxt, minh, mint;
int arr[MAXN];
int n, limit_val;

// 判断如果加入数字number，窗口最大值 - 窗口最小值是否依然 <= limit
// 依然 <= limit，返回true
bool ok(int limit, int number) {
    // max_val : 如果number进来，新窗口的最大值
    int max_val = (maxh < maxt) ? max(arr[maxDeque[maxh]], number) : number;
    // min_val : 如果number进来，新窗口的最小值
    int min_val = (minh < mint) ? min(arr[minDeque[minh]], number) : number;
    return max_val - min_val <= limit;
}

// r位置的数字进入窗口，修改窗口内最大/最小值的更新结构
void push(int r) {
    while (maxh < maxt && arr[maxDeque[maxt - 1]] <= arr[r]) {
        maxt--;
    }
    maxDeque[maxt++] = r;
    while (minh < mint && arr[minDeque[mint - 1]] >= arr[r]) {
        mint--;
    }
    minDeque[mint++] = r;
}

// 窗口要吐出l位置的数了！检查过期！
void pop(int l) {
    if (maxh < maxt && maxDeque[maxh] == l) {
        maxh++;
    }
    if (minh < mint && minDeque[minh] == l) {
        minh++;
    }
}

int solve() {
    maxh = maxt = minh = mint = 0;
    int ans = 0;
    for (int l = 0, r = 0; l < n; l++) {
        // [l,r)，r永远是没有进入窗口的、下一个数所在的位置
        while (r < n && ok(limit_val, arr[r])) {
            push(r++);
        }
        // 从while出来的时候，[l,r)是l开头的子数组能向右延伸的最大范围
        ans = max(ans, r - l);
        pop(l);
    }
    return ans;
}

int main() {
    // 协议：标准 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 针对测试链接或标准 ACM 输入
    if (cin >> n >> limit_val) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << solve() << endl;
    }

    return 0;
}
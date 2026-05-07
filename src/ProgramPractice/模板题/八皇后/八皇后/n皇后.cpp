#include<cmath>
const int N = 10;
int col[N];
int ans = 0;
//图为0~n-1
int n;
int queen[N];
bool ck(int x,int y) {
    for (int i = 0; i < x; i++) {
        if (queen[i] == y || abs(y - queen[i]) == abs(x - i))
            return false;
    }
    return true;
}
void search(int i) {//当前行
    if (i == n) {
        ans++;
        return;
    }
    for (int j = 0; j < n; j++) {//枚举列
        if (ck(i, j)) {
            queen[i] = j;
            search(i + 1);
        }
        
    }
}
#include <iostream>
using namespace std;

int n, ans = 0;
int limit; // 全局掩码，例如 n=4 时，limit=1111(二进制)

// col: 当前哪些列不能放
// left: 当前哪些左对角线不能放
// right: 当前哪些右对角线不能放
void bi_search(int col, int left, int right) {
    if (col == limit) { // 所有列都填满了
        ans++;
        return;
    }

    // ban 得到所有冲突位置
    int ban = col | left | right;

    // limit & (~ban) 得到当前行所有可以放的位置（1表示可以放）
    int candidate = limit & (~ban);

    while (candidate) {
        // 提取最右侧的 1 (你刚学到的 lowbit!)
        int place = candidate & (-candidate);

        // 把这个位置从候选里去掉 (等同于 candidate ^= place)
        candidate -= place;

        // 递归下一行
        // col | place: 更新列冲突
        // (left | place) << 1: 更新左对角线冲突（向左移一位）
        // (right | place) >> 1: 更新右对角线冲突（向右移一位）
        bi_search(col | place, (left | place) << 1, (right | place) >> 1);
    }
}

int main() {
    cin >> n;
    limit = (1 << n) - 1; // 修正优先级问题
    bi_search(0, 0, 0);
    cout << ans << endl;
    return 0;
}
#include<stdio.h>

int count = 0;

/**
 * 使用位运算解决N皇后问题
 * @param row: 当前已占用的列（二进制位表示）
 * @param ld: 当前已占用的左对角线（二进制位表示）
 * @param rd: 当前已占用的右对角线（二进制位表示）
 * @param n: 棋盘大小
 */
void solve(int row, int ld, int rd, int n) {
    // 如果所有行都放置了皇后，找到一个解
    if (row == (1 << n) - 1) {
        count++;
        return;
    }

    // pos: 当前行可以放置皇后的位置（1表示可以放置）
    // ~(row | ld | rd): 排除已被占用的列和对角线
    // & ((1 << n) - 1): 只保留n位，避免高位干扰
    int pos = ((1 << n) - 1) & ~(row | ld | rd);

    // 遍历所有可以放置皇后的位置
    while (pos) {
        // p: 取最低位的1（即尝试最右边的可用位置）
        int p = pos & -pos;
        // 移除这个位置，表示我们已经尝试过
        pos -= p;
        // 递归处理下一行：
        // row | p: 新占用的列
        // (ld | p) << 1: 左对角线影响下一行（向左移动）
        // (rd | p) >> 1: 右对角线影响下一行（向右移动）
        solve(row | p, (ld | p) << 1, (rd | p) >> 1, n);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    // 初始状态：没有占用任何列和对角线
    solve(0, 0, 0, n);
    printf("%d\n", count);
    return 0;
}






#include<stdio.h>

/**
 * 检查在(row, col)位置放置皇后是否安全
 * @param queens: 数组，queens[i]表示第i行皇后所在的列
 * @param row: 要检查的行
 * @param col: 要检查的列
 * @return: 1表示安全，0表示不安全
 */
int isSafe(int queens[], int row, int col) {
    for (int i = 0; i < row; i++) {
        // 检查同一列或同一对角线
        // 对角线检查：行差 == 列差 说明在同一对角线
        if (queens[i] == col ||
            abs(queens[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    int queens[20] = { -1 }; // 初始化所有位置为-1（表示未放置皇后）
    int row = 0, col = 0, count = 0;

    // 使用迭代模拟递归回溯
    while (row >= 0) {
        // 在当前行寻找安全位置
        while (col < n) {
            if (isSafe(queens, row, col)) {
                queens[row] = col;  // 放置皇后
                col = 0;            // 重置列指针，为下一行做准备
                break;
            }
            col++; // 尝试下一列
        }

        // 如果找到安全位置
        if (queens[row] != -1) {
            // 如果是最后一行，找到一个解
            if (row == n - 1) {
                count++;
                // 回溯：移除当前行的皇后，继续寻找其他解
                queens[row] = -1;
                row--; // 回到上一行
                if (row >= 0) col = queens[row] + 1; // 从上一皇后的下一列开始
            }
            else {
                // 继续处理下一行
                row++;
            }
        }
        else {
            // 当前行没有安全位置，需要回溯
            row--; // 回到上一行
            if (row >= 0) {
                // 移除上一行的皇后，从它的下一列继续尝试
                col = queens[row] + 1;
                queens[row] = -1;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}













#include<stdio.h>

int n, count = 0;
// col[i]: 第i列是否被占用
// diag1[i]: 主对角线i是否被占用（主对角线：行+列=常数）
// diag2[i]: 副对角线i是否被占用（副对角线：行-列=常数）
int col[20], diag1[40], diag2[40];

/**
 * 递归搜索所有可能的皇后放置方式
 * @param y: 当前正在处理的行（从0开始）
 */
void search(int y) {
    // 如果已经处理完所有行，找到一个解
    if (y == n) {
        count++;
        return;
    }

    // 尝试在当前行的每一列放置皇后
    for (int x = 0; x < n; x++) {
        // 检查列、主对角线、副对角线是否被占用
        // col[x]: 检查第x列是否有皇后
        // diag1[x+y]: 检查主对角线（行+列相同的对角线）
        // diag2[x-y+n-1]: 检查副对角线（行-列相同的对角线）
        // 加n-1是为了避免负数组索引
        if (col[x] || diag1[x + y] || diag2[x - y + n - 1])
            continue; // 如果被占用，跳过这个位置

        // 放置皇后，标记占用的列和对角线
        col[x] = diag1[x + y] = diag2[x - y + n - 1] = 1;

        // 递归处理下一行
        search(y + 1);

        // 回溯：移除皇后，取消标记
        col[x] = diag1[x + y] = diag2[x - y + n - 1] = 0;
    }
}

int main() {
    scanf("%d", &n);
    search(0); // 从第0行开始搜索
    printf("%d\n", count);
    return 0;
}
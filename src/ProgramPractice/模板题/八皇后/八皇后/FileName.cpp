#include<stdio.h>
#include<string.h>
int tem[8];
int ans = 0;
int solutions[12][8];
int ck(int cnt, int x) {
    for (int i = 0; i < cnt; i++) {
        if (tem[i] == x ||
            tem[i] - i == x - cnt ||
            tem[i] + i == x + cnt)
            return 0;
    }
    return 1;
}
int is_duplicate() {
    int arr[8];
    for (int i = 0; i < 8; i++) arr[i] = tem[i];
    for (int idx = 0; idx < ans; idx++) {
        for (int t = 0; t < 8; t++) {
            int flag = 1;
            for (int i = 0; i < 8; i++) {
                int row = i, col = arr[i];
                int new_row, new_col;
                switch (t) {
                case 0:  // 原始
                    new_row = row; new_col = col;
                    break;
                case 1:  // 旋转90度
                    new_row = col; new_col = 7 - row;
                    break;
                case 2:  // 旋转180度
                    new_row = 7 - row; new_col = 7 - col;
                    break;
                case 3:  // 旋转270度
                    new_row = 7 - col; new_col = row;
                    break;
                case 4:  // 水平翻转（左右对称）
                    new_row = row; new_col = 7 - col;
                    break;
                case 5:  // 垂直翻转（上下对称）
                    new_row = 7 - row; new_col = col;
                    break;
                case 6:  // 主对角线翻转（转置）
                    new_row = col; new_col = row;
                    break;
                case 7:  // 副对角线翻转
                    new_row = 7 - col; new_col = 7 - row;
                    break;
                }
                if (solutions[idx][new_row] != new_col) {
                    flag = 0;
                    break;
                }
            }
            if (flag) return 1;
        }
    }
    return 0;
}

void dfs(int cnt) {
    if (cnt == 8) {
        if (!is_duplicate()) {
            for (int i = 0; i < 8; i++) solutions[ans][i] = tem[i];
            printf("No%d:", ans + 1);
            for (int i = 0; i < 8; i++)
                printf("%d ", tem[i] + 1);
            printf("\n");
            ans++;
        }
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (ck(cnt, i)) {
            tem[cnt] = i;
            dfs(cnt + 1);
        }
    }
}
int main() {
    dfs(0);
    return 0;
}
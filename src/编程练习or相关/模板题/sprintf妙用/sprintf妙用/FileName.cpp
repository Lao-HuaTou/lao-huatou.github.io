#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char s[100];
        scanf("%s", s);

        // 如果第一个字符是数字，在前面加上"P"
        if (isdigit(s[0])) {
            char temp[100];
            strcpy(temp, s);  // 保存原字符串
            sprintf(s, "P%s", temp);  // 在前面加上P     nb
        }

        printf("https://www.luogu.com.cn/problem/%s\n", s);
    }

    return 0;
}
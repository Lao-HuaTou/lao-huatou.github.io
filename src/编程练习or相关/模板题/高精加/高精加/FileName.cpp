#include<stdio.h>
#include<string.h>

char ans[510];

void highplus(char* a, char* b) {
    int len1 = strlen(a), len2 = strlen(b);
    int i = len1 - 1, j = len2 - 1, k = 0, carry = 0;
    char temp[510];

    // 从低位到高位逐位相加
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';

        temp[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    // 反转结果
    for (int i = 0; i < k; i++) {
        ans[i] = temp[k - 1 - i];
    }
    ans[k] = '\0';
}

int main() {
    char a[510], b[510];
    scanf("%s %s", a, b);

    highplus(a, b);
    printf("%s\n", ans);

    return 0;
}
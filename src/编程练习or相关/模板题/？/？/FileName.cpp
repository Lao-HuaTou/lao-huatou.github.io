//#include<stdio.h>
//#include<string.h>
//#define MAX 1000  // 增加数组大小
//long long a[MAX], b[MAX];
//int la = 1, lb = 1;
//void mul(long long* a, int n)
//{
//    for (int i = 1; i <= la; i++)
//        a[i] *= n;
//    for (int i = 1; i <= la + 10; i++) {
//        if (i >= MAX) break;  // 防止越界
//        if (a[i] >= 10) {
//            a[i + 1] += a[i] / 10;
//            a[i] %= 10;
//        }
//    }
//    la += 10;
//    while (la > MAX - 1) la = MAX - 1;  // 确保不越界
//    while (la > 1 && a[la] == 0)
//        la--;
//}
//void plus(long long* a, long long* b)
//{
//    int max_len = (la > lb) ? la + 10 : lb + 10;
//    if (max_len >= MAX) max_len = MAX - 1;  // 确保不越界
//    for (int i = 1; i <= max_len; i++)
//        b[i] += a[i];
//    for (int i = 1; i <= max_len; i++) {
//        if (b[i] >= 10) {
//            b[i + 1] += b[i] / 10;
//            b[i] %= 10;
//        }
//    }
//    lb = max_len;
//    while (lb > 1 && b[lb] == 0)
//        lb--;
//}
//int main()
//{
//    memset(a, 0, sizeof(a));
//    memset(b, 0, sizeof(b));
//    a[1] = 1, b[1] = 1;
//    int n;
//    printf("请输入n: ");
//    scanf_s("%d", &n);
//    for (int i = 2; i <= n; i++) {
//        mul(a, i);
//        plus(a, b);
//    }
//    printf("1! + 2! + ... + %d! = \n", n);
//    for (int i = lb; i >= 1; i--)
//        printf("%lld", b[i]);
//    printf("\n");
//    return 0;
//}
#include<stdio.h>
long long a[1000], b[1000], la = 1, lb = 1;
void mul(long long* a, int n)
{
    for (int i = 1; i <= la; i++)
        a[i] *= n;
    for (int i = 1; i <= la + 10; i++) {
        if (a[i] >= 10) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
    }
    la += 10;
    while (la > 1 && a[la] == 0)
        la--;
}
void plus(long long* a, long long* b)
{
    for (int i = 1; i <= 500; i++)
        b[i] += a[i];
    for (int i = 1; i <= 500; i++)
        b[i + 1] += b[i] / 10, b[i] %= 10;
    lb = 1;
    for (int i = 500; i >= 1; i--)
        if (b[i] != 0) {
            lb = i; break;
        }
}
int main()
{
    a[1] = 1, b[1] = 1;
    int n; scanf_s("%d", &n);
    for (int i = 2; i <= n; i++)
        mul(a, i), plus(a, b);
    for (int i = lb; i >= 1; i--)
        printf("%lld", b[i]);
}
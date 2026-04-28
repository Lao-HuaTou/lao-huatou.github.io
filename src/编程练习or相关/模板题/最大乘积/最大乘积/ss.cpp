#include<stdio.h>
int ans[100000] = { 0 }, a[10000] = { 0 };
int n, index, l = 1;

void mul(int x)  // 改为直接传入数值而不是索引
{
    // 乘法
    for (int i = 0; i < l; i++)
    {
        ans[i] *= x;
    }

    // 进位处理 - 简化版本
    for (int i = 0; i < l + 10; i++)
    {
        if (ans[i] >= 10)
        {
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
        }
    }

    // 更新长度
    for (int i = l + 10; i >= 0; i--)
    {
        if (ans[i] > 0)
        {
            l = i + 1;
            break;
        }
    }
}

int main()
{
    ans[0] = 1;
    scanf("%d", &n);
    int st = 1, m = 0;
    while (st++)
    {
        if (n >= st) {
            a[m++] = st;
            n -= st;
        }
        else {
            if (n == st - 1) {
                for (int i = m - 1; i >= 0; i--) a[i] += 1;
                a[m - 1]++;
                break;
            }
            else {
                for (int i = m - 1, j = 0; j < n; j++, i--) a[i] += 1;
                break;
            }

        }
    }
    index = m;

    // 调用mul时直接传入数值
    for (int i = 0; i < index; i++)
        mul(a[i]);

    for (int i = 0; i < index; i++)
    {
        printf("%d ", a[i]);
    }
    putchar('\n');
    for (int i = l - 1; i >= 0; i--)
        printf("%d", ans[i]);
    return 0;
}



#include<iostream>
using namespace std;
int a[10001] = {};
int s[10001] = {};
int n, len = 1;
void mul(int x)
{
    for (int i = 1; i <= len; i++)s[i] *= x;
    for (int i = 1; i <= len; i++)
    {
        s[i + 1] += s[i] / 10;
        s[i] %= 10;
    }
    while (s[len + 1] > 0)
    {
        len++;
        s[len + 1] += s[len] / 10;
        s[len] %= 10;
    }
}
int main()
{
    cin >> n;
    if (n == 3)
    {
        cout << 3 << endl;
        cout << 3 << endl;
        return 0;
    }
    if (n == 4)
    {
        cout << 4 << endl;
        cout << 4 << endl;
        return 0;
    }
    s[0] = s[1] = 1;
    int Sum = 0, tot = 0;
    for (int i = 2; Sum < n; Sum += i, i++)a[++tot] = i;
    if (Sum > n + 1)a[Sum - n - 1] = 0;
    else if (Sum == n + 1)a[tot]++, a[1] = 0;
    for (int i = 1; i <= tot; i++)
    {
        if (a[i])
        {
            cout << a[i] << ' ';
            mul(a[i]);
        }
    }
    cout << endl;
    for (int i = len; i >= 1; i--)
        cout << s[i];
    cout << endl;
    return 0;
}

#include<stdio.h>
int map[505][505], n;
void cs(int x)
{
    int a = 1;
    for (int i = 1; i <= x; i++)
        for (int j = 1; j <= x; j++)
            map[i][j] = (a++);
}
void ni(int x, int y, int r)
{
    int tem[505][505];
    int p = 1, q = 1;
    for (int i = x - r; i <= x + r; i++)
    {
        q = 1;
        for (int j = y - r; j <= y + r; j++)
            tem[p][q++] = map[i][j];
        p++;
    }
    int R = 2 * r + 1;
    int x1 = x - r, y1 = y - r;
    for (int i = 1; i <= R; i++)
    {
        x1 = x + r;
        for (int j = 1; j <= R; j++)
            map[x1--][y1] = tem[i][j];
        y1++;
    }
}
void shun(int x, int y, int r)
{
    int tem[505][505];
    int p = 1, q = 1;
    for (int i = x - r; i <= x + r; i++)
    {
        q = 1;
        for (int j = y - r; j <= y + r; j++)
            tem[p][q++] = map[i][j];
        p++;
    }
    int R = 2 * r + 1;
    int x1 = x - r, y1 = y + r;
    for (int i = 1; i <= R; i++)
    {
        x1 = x - r;
        for (int j = 1; j <= R; j++)
            map[x1++][y1] = tem[i][j];
        y1--;
    }
}
int main()
{
    int m;
    scanf_s("%d %d", &n, &m);
    cs(n);
    while (m--)
    {
        int x, y, r, f;
        scanf("%d %d %d %d", &x, &y, &r, &f);
        if (f == 0) shun(x, y, r);
        else ni(x, y, r);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            printf("%d ", map[i][j]);
        putchar('\n');
    }
}
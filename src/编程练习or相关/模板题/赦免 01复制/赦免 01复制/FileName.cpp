#include<stdio.h>
#include<math.h>

int n;
int map[1025][1025];
void copy(int n)
{
    int x = pow(2, n);
    int y = x;
    for (int i = 1; i <= pow(2, n); i++)
        for (int j = 1; j <= pow(2, n); j++)
        {
            map[i + x][j] = map[i][j];
            map[i][j + y] = map[i][j];
        }
}
int main()
{
    map[1][1] = 1;
    scanf_s("%d", &n);
    int k = pow(2, n);
    for (int i = 0; i < n; i++) copy(i);
    for (int i = k; i >= 1; i--)
    {
        for (int j = k; j >= 1; j--)
            printf("%d ", map[i][j]);
        putchar('\n');
    }
    return 0;
}
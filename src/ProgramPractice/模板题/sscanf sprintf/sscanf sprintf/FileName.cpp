#include <iostream> //cin & cout ”√iostream
#include <cstring> //memset & strlen ”√cstring
#include <cstdio> //sscanf & sprintf ”√cstdio
int n;
char a;
char s[1000], t[10];
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int c, d;
        scanf("%s", t);
        if (t[0] >= 'a' && t[0] <= 'z') {
            a = t[0];
            scanf("%d %d", &c, &d);
        }
        else {
            sscanf(t, "%d", &c);
            scanf("%d", &d);
        }
        memset(s, 0, sizeof(s));

        if (a == 'a') sprintf(s, "%d+%d=%d", c, d, c + d);
        else if (a == 'b')sprintf(s, "%d-%d=%d", c, d, c - d);
        else if (a == 'c')sprintf(s, "%d*%d=%d", c, d, c * d);
        printf("%s\n%d\n", s, strlen(s));

    }
    return 0;
}
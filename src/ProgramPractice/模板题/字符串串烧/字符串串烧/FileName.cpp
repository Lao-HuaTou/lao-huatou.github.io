#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int n;
    scanf("%d", &n);
    char s1[15000];
    scanf("%s", s1);
    while (n--)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            char s2[10500];
            scanf("%s", s2);
            strcat(s1, s2);
            printf("%s\n", s1);
        }
        if (op == 2)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            char tem[15000];
            strncpy(tem, s1 + a, b);
            tem[b] = '\0';
            strcpy(s1, tem);
            printf("%s", s1);
            putchar('\n');
        }
        if (op == 3)
        {
            int c;
            char s3[1000];
            scanf("%d %s", &c, s3);
            char temp[15000];
            strncpy(temp, s1, c);
            temp[c] = '\0';
            strcat(temp, s3);
            strcat(temp, s1 + c);
            strcpy(s1, temp);
            printf("%s\n", s1);
        }
        if (op == 4) {
            char ck[1500];
            scanf("%s", ck);
            char* p = strstr(s1, ck);
            if (p != NULL)printf("%d\n", (int)(p - s1));
            else printf("-1\n");
        }
    }
    return 0;
}

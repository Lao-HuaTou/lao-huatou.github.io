#include<stdio.h>
#include<string.h>
#define max(a,b) (a>b?a:b)
int count[26];
char tar[500];
int main()
{
    char s[4][100];
    for (int i = 0; i < 4; i++) {
        fgets(s[i], sizeof(s[i]), stdin);
        // È¥³ý»»ÐÐ·û
        s[i][strcspn(s[i], "\n")] = '\0';
    }
    int k;
    for (int i = 0; i < 4; i++)
    {
        k = strlen(s[i]);
        for (int j = 0; j < k; j++)
        {
            if (s[i][j] >= 'A' && s[i][j] <= 'Z')
                count[s[i][j] - 'A']++;
        }
    }
    int ma = -1;
    for (int i = 0; i < 26; i++)
    {
        ma = max(ma, count[i]);
    }
    for (int i = ma; i >= 1; i--)
    {
        for (int j = 0; j < 26; j++) {
            if (count[j] == i) {
                printf("* ");
                count[j]--;
            }
            else printf("  ");
        }
        putchar('\n');
    }
    for (int i = 0; i < 26; i++) printf("%c ", i + 'A');
}
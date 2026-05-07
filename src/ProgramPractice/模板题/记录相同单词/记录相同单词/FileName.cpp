#include <stdio.h>

#define MAX_LINE 1000001
#define val(a) (a<'a' ? (a-'A'+'a') : a)

int main()
{
    // declaration
    int i = 0, j, count = 0, first = -1;
    char c, w[11], s[MAX_LINE];

    // input
    scanf("%s", w);
    c = getchar();
    while ((c = getchar()) != EOF && i < MAX_LINE) {
        if (c == '\n') break;
        s[i++] = c;
    } s[i] = '\0';

    // calculate
    for (i = 0, j = 0; s[i] != '\0'; ++i) {
        if ((i == 0 || s[i - 1] == ' ' || j) && val(s[i]) == val(w[j]) && ++j > -1) {
            if (w[j] == '\0' && (s[i + 1] == '\0' || s[i + 1] == ' ')) {
                if (first == -1) first = i + 1 - j;
                count++;
            }
        }
        else j = 0;
    }

    // output
    if (count == 0) printf("-1\n");
    else printf("%d %d\n", count, first);
    return 0;
}


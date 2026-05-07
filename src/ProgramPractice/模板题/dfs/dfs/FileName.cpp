#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef long long ll;
int s[30], visited[30];
ll ans;
int k;
void dfs(int start, int count, int current_sum, int target) {
    if (count == target) {
        ans += current_sum;
        return;
    }

    for (int i = start; i < k; i++) {
        dfs(i + 1, count + 1, current_sum + s[i], target);
    }
}
signed main()
{

    int a;
    while (scanf("%d", &a) != EOF)
    {
        s[k] = a;
        k++;
    }
    for (int i = 1; i <= k; i++)
    {
        dfs(0, 0, 0, i);
    }
    printf("%lld", ans);
    return 0;
}

#include<stdio.h>

typedef long long ll;

int main() {
    int s[30], k = 0;
    int a;
    ll total_sum = 0;

    while (scanf("%d", &a) != EOF) {
        s[k++] = a;
        total_sum += a;
    }

    ll ans = total_sum * (1LL << (k - 1));
    printf("%lld", ans);

    return 0;
}
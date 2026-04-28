#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int a[101], f[101][10001] = { 0 };
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)cin >> a[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            // 要第i个菜+不要
            if (j == a[i])f[i][j] = f[i - 1][j] + 1;
            if (j > a[i]) f[i][j] = f[i - 1][j] + f[i - 1][j - a[i]];
            if (j < a[i]) f[i][j] = f[i - 1][j]+0;
        }
    cout << f[n][m];
    return 0;
}


#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 110
using namespace std;
int n, m, a[N], F[10010];
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    F[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= a[i]; j--)
            F[j] = F[j] + F[j - a[i]];
    cout << F[m];
    return 0;
}





//********************************************DP法
#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    vector<int> dp(m + 1, 0);
    dp[0] = 1;  // 关键区别：这里初始化为1

    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= a[i]; j--) {
            dp[j] += dp[j - a[i]];  // 关键区别：这里是累加而不是取max
        }
    }

    cout << dp[m];  // 直接输出方案数
    return 0;
}


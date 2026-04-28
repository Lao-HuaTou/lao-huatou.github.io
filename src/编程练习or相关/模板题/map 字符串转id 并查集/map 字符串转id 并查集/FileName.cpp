#include <iostream>
#include<map>
using namespace std;

const int N = 2e5 + 9;
map<string, int> mp;
int pre[2 * N], cnt[2 * N];

int root(int x)
{
    return pre[x] = (pre[x] == x ? x : root(pre[x]));
}


void merge(int x, int y)
{
    int rx = root(x), ry = root(y);
    if (rx == ry)    return;
    pre[rx] = ry;
}


int main()
{
    int n, idx = 0; cin >> n;
    for (int i = 1; i <= 2 * N; i++)   pre[i] = i;
    while (n--)
    {
        string str1, str2; cin >> str1 >> str2;
        // 将字符串转为下标
        if (!mp[str1])   mp[str1] = ++idx;
        if (!mp[str2])   mp[str2] = ++idx;
        cnt[mp[str1]]++, cnt[mp[str2]]++;
        merge(mp[str1], mp[str2]);
    }
    int num = 0;    // 代表并查集的个数
    for (int i = 1; i <= idx; i++)
    {
        if (i == root(i))    num++;
        if (cnt[i] % 2)  // 如果某一字符串出现的次数为奇数，则不能构成环
        {
            cout << "NO" << '\n';
            return 0;
        }
    }
    if (num == 1) cout << "YES" << '\n';   //若并查集的数量为一个，说明可以形成一个整体，可以形成首尾相连的环
    else    cout << "NO" << '\n';

    return 0;
}
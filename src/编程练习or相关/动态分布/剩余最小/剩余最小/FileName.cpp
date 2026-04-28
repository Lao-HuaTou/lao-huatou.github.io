#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int v, n;
int main()
{
    cin >> v >> n;
    vector<int>per(n), cover(v + 1, 0);
    for (int i = 0; i < n; i++)
        cin >> per[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = v; j >= per[i]; j--)
            cover[j] = max(cover[j], cover[j - per[i]] + per[i]);
    }
    cout << v - cover[v];
    return 0;
}
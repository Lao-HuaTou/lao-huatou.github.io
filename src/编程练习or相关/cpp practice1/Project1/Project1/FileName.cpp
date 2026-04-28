#include<iostream>
using namespace std;
int main()
{
    int m, n, t, ar[10] = { 0 };
    cin >> m >> n;
    for (int i = m; i <= n; i++)
    {
        t = i;
        if (t == 0)ar[0]++;
        while (t != 0)
        {
            ar[t % 10]++;
            t /= 10;
        }
    }
    for (int i = 0; i < 10; i++) cout << ar[i] << " ";
    return 0;
}
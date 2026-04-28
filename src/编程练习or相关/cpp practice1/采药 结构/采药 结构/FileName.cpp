//分数问题
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct yao {
    int time;
    int value;
    double per;
};
int main()
{
    int t, m;
    cin >> t >> m;
    vector<yao>caoyao(m);
    for(int i=0;i<m;i++)
    {
        cin >> caoyao[i].time >> caoyao[i].value;
		caoyao[i].per = (double)caoyao[i].value / caoyao[i].time;
    }
    //*****************************************************************************************
    sort(caoyao.begin(), caoyao.end(), [](const yao& a, const yao& b)
    {
			return a.per > b.per;//降序排列
	});
	//*****************************************************************************************
    double ans = 0;
    for(int i=0;i<m;i++)
    {
        if(t >= caoyao[i].time)
        {
            ans += caoyao[i].value;
            t -= caoyao[i].time;
        }
        else
        {
            ans += caoyao[i].per * t;
            break;
        }
    }
    printf("%.2f", ans);
	return 0;
}



//0-1背包问题
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int t, m;
    cin >> t >> m;

    vector<int> time(m), value(m);
    for (int i = 0; i < m; i++) {
        cin >> time[i] >> value[i];
    }

    // 动态规划数组
    vector<int> dp(t + 1, 0);

    // 0-1背包动态规划
    for (int i = 0; i < m; i++) {
        for (int j = t; j >= time[i]; j--) {
            dp[j] = max(dp[j], dp[j - time[i]] + value[i]);
        }
    }

    cout << dp[t] << endl;
    return 0;
}
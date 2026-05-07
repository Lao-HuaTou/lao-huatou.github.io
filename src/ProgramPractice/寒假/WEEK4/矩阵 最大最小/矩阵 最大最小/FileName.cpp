#include<vector>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n, m,q;
const int maxn = (int)1e5 + 5;
const int maxm = (int)1e5 + 5;
int amx[maxn][25], amn[maxn][25], afx[maxn][25], azn[maxn][25];
int bmx[maxm][25], bmn[maxm][25];
int lg[maxn];
const int maxinf = 2e18, mininf = -2e18;

signed main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m>>q;
	vector<int>x(n + 1);
	vector<int>y(m + 1);
    lg[1] = 0;
    for (int i = 2; i < maxn; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        amx[i][0] = amn[i][0] = x[i];
        afx[i][0] = (x[i] <= 0 ? x[i] : mininf);
        azn[i][0] = (x[i] >= 0 ? x[i] : maxinf);
    }
    for (int i = 1; i <= m; i++) {
        cin >> y[i];
        bmx[i][0] = bmn[i][0] = y[i];
    }
    for (int j = 1; j <= 20; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            int p = i + (1 << (j - 1));
            amx[i][j] = max(amx[i][j - 1], amx[p][j - 1]);
            amn[i][j] = min(amn[i][j - 1], amn[p][j - 1]);
            afx[i][j] = max(afx[i][j - 1], afx[p][j - 1]);
            azn[i][j] = min(azn[i][j - 1], azn[p][j - 1]);
        }
    }
    for (int j = 1; j <= 20; j++) {
        for (int i = 1; i + (1 << j) - 1 <= m; i++) {
            int p = i + (1 << (j - 1));
            bmx[i][j] = max(bmx[i][j - 1], bmx[p][j - 1]);
            bmn[i][j] = min(bmn[i][j - 1], bmn[p][j - 1]);
        }
    }
	while(q--){
		int l1, r1, l2, r2;
		cin >> l1 >> r1 >> l2 >> r2;
        int sa = lg[r1 - l1 + 1], sb = lg[r2 - l2 + 1];
        int pa = r1 - (1 << sa) + 1, pb = r2 - (1 << sb) + 1;

        int amax = max(amx[l1][sa], amx[pa][sa]);
        int amin = min(amn[l1][sa], amn[pa][sa]);
        int afmx = max(afx[l1][sa], afx[pa][sa]);
        int azmn = min(azn[l1][sa], azn[pa][sa]);
        int bmax = max(bmx[l2][sb], bmx[pb][sb]);
        int bmin = min(bmn[l2][sb], bmn[pb][sb]);
        int ans = mininf;
        ans = max(ans, amax * (amax >= 0 ? bmin : bmax));
        ans = max(ans, amin * (amin >= 0 ? bmin : bmax));
        if (afmx != mininf)ans = max(ans, afmx * (afmx >= 0 ? bmin : bmax));
        if (azmn != maxinf) ans = max(ans, azmn * (azmn >= 0 ? bmin : bmax));
        cout << ans << '\n';
	}
	return 0;
}

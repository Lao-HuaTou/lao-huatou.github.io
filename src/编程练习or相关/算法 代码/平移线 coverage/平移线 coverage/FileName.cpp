//#include<iostream>
//#include<vector>
//#include<cstdlib>
//#include<algorithm>
//typedef long long ll;
//using namespace std;
//int n, L, k;
//int l[600005];
//int diff[1000005];
//
//
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int T; cin >> T;
//	while (T--) {
//
//		int ans1 = 0;
//		cin >> n >> L >> k;
//		int max1=-1e8;
//		for (int i = 0; i < n; i++) {
//			int x; cin >> x;
//			l[i] = x;
//			max1 = max(max1, x + L);
//			diff[x] += 1; diff[x + L] -= 1;
//		}
//		int M = L + max1 + 5;
//		vector<int>line(M,0);
//		int cur = 0;
//		for (int i = 0; i < M; i++) {
//			cur += diff[i];
//			line[i] = cur;
//			if (line[i] == k) ans1++;
//		}
//		vector<int>add(M+1, 0), remv(M+1, 0);//add k-1   remv k+1
//		for (int i = 0; i < M; i++) {
//			int vr = 0, va = 0;
//			if (line[i] == k + 1) vr = 1;
//			else if (line[i] == k) vr = -1;
//			if (line[i] == k - 1) va = 1;
//			else if (line[i] == k) va = -1;
//			add[i + 1] = add[i] + va;
//			remv[i + 1] = remv[i] + vr;
//		}
//		int del1 = -1e8,del2=-1e8;
//		for (int i = 0; i < n; i++) {
//			del1 = max(del1, remv[l[i] + L] - remv[l[i]]);
//		}
//		for (int i = 0; i < M - L; i++) {
//			del2 = max(del2, add[i + L] - add[i]);
//		}
//		cout << ans1 + del1 + del2<<'\n';
//		for (int i = 0; i <= M; i++) diff[i] = 0;
//	}
//	return 0;
//}

#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
typedef long long ll;
using namespace std;
const int MAXM = 1000005; 
int n, L, k;
int l[200005];
int diff[MAXM];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        ll ans1 = 0;
        cin >> n >> L >> k;
        int max_pos = 0;
        for (int i = 0; i < n; i++) {
            cin >> l[i];
            max_pos = max(max_pos, l[i]);
        }
        int M = max_pos + L + 5;
        for (int i = 0; i < n; i++) {
            diff[l[i]] += 1;
            if (l[i] + L < M) diff[l[i] + L] -= 1;
        }
        vector<int> line(M, 0);
        int cur = 0;
        for (int i = 0; i < M; i++) {
            cur += diff[i];
            line[i] = cur;
            if (line[i] == k) ans1++;
        }
        vector<ll> add(M + 1, 0), remv(M + 1, 0);
        for (int i = 0; i < M; i++) {
            ll vr = 0, va = 0;
            if (line[i] == k + 1) vr = 1;
            else if (line[i] == k) vr = -1;
            if (line[i] == k - 1) va = 1;
            else if (line[i] == k) va = -1;
            add[i + 1] = add[i] + va;
            remv[i + 1] = remv[i] + vr;
        }
        int num = M - L + 1;
        vector<ll> val_add(num);
        for (int i = 0; i < num; i++) {
            val_add[i] = add[i + L] - add[i];
        }
        ll k1_extra = (k == 1) ? L : 0;
        vector<ll> pre_m(num + 1, -1e18), suf_m(num + 1, -1e18);
        for (int i = 0; i < num; i++) pre_m[i + 1] = max(pre_m[i], val_add[i]);
        for (int i = num - 1; i >= 0; i--) suf_m[i] = max(suf_m[i + 1], val_add[i]);
        ll max_final = 0;
        for (int i = 0; i < n; i++) {
            ll del1 = remv[l[i] + L] - remv[l[i]];
            int bad_l = max(0, l[i] - L + 1);
            int bad_r = min(num- 1, l[i] + L - 1);
            ll best_va = 0;
            if (bad_l > 0) best_va = max(best_va, pre_m[bad_l]);
            if (bad_r + 1 < num) best_va = max(best_va, suf_m[bad_r + 1]);
            best_va = max(best_va, k1_extra);//k==1
            max_final = max(max_final, ans1 + del1 + best_va);
        }
        cout << max_final << '\n';
        for (int i = 0; i <= M; i++) diff[i] = 0;
    }
    return 0;
}
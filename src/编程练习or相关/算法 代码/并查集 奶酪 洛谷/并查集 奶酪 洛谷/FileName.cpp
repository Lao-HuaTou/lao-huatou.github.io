#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
typedef long long ll;
typedef struct dot {
	ll x, y, z;
}d;
using namespace std;

int n, h;
ll r;
int p[1100],s[1100];
ll dist(ll x1, ll x2, ll y1, ll y2, ll z1, ll z2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
}
void init(int x) {
	for (int i = 0; i <= x; i++) {
		p[i] = i;
		s[i] = 1;
	}
}
int find(int x) {
	if (x == p[x]) return x;
	else return p[x] = find(p[x]);
}
void union1(int x, int y) {
	int rx = find(x);
	int ry = find(y);
	if (rx != ry) {
		if (s[rx] < s[ry]) {
			p[rx] = ry;
			s[ry] += s[rx];
		}
		else {
			p[ry] = rx;
			s[rx] += s[ry];
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	//freopen("cheese.in", "r", stdin);
	//freopen("cheese.out", "w", stdout);
	int T; cin >> T;
	while (T--) {
		cin >> n >> h >> r;
		init(n);
		vector<d>hole(n+1);
		vector<int>low, high;
		for (int i = 1; i <= n; i++) {
			cin >> hole[i].x >> hole[i].y >> hole[i].z;
			if (hole[i].z - r <= 0) low.push_back(i);
			if (hole[i].z + r >= h) high.push_back(i);
			for (int j = 1; j < i; j++) {
				if (dist(hole[i].x, hole[j].x, hole[i].y, hole[j].y, hole[i].z, hole[j].z) <= 4LL * r * r) {
					union1(i, j);
				}
			}
		}
		int flag = 0;
		for (int i = 0; i < low.size(); i++) {
			for (int j = 0; j < high.size(); j++) {
				if (find(low[i]) == find(high[j])) {
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		if (flag) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}


#include<iostream>
#include<vector>
#include<algorithm>
typedef long long ll;
using namespace std;

struct dot {
    ll x, y, z;
};
int n;
ll h, r;
int p[1105], s[1105];
void init(int x) {
    for (int i = 0; i <= x; i++) {
        p[i] = i;
        s[i] = 1;
    }
}
int find(int x) {
    if (x == p[x]) return x;
    return p[x] = find(p[x]);
}
void union1(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        if (s[rx] < s[ry]) {
            p[rx] = ry;
            s[ry] += s[rx];
        }
        else {
            p[ry] = rx;
            s[rx] += s[ry];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        cin >> n >> h >> r;
        init(n);
        vector<dot> hole(n + 1);
        vector<int> low, high;
        for (int i = 1; i <= n; i++) {
            cin >> hole[i].x >> hole[i].y >> hole[i].z;
            if (hole[i].z <= r) low.push_back(i);
            if (hole[i].z + r >= h) high.push_back(i);
            for (int j = 1; j < i; j++) {
                ll dx = hole[i].x - hole[j].x;
                ll dy = hole[i].y - hole[j].y;
                ll dz = hole[i].z - hole[j].z;
                if ((long double)dx * dx + (long double)dy * dy + (long double)dz * dz <= (long double)4 * r * r) {
                    union1(i, j);
                }
            }
        }
        int flag = 0;
        for (int i = 0; i < (int)low.size(); i++) {
            for (int j = 0; j < (int)high.size(); j++) {
                if (find(low[i]) == find(high[j])) {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        if (flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
int n, m, k;
ll score[2510];
vector<int>G[2510];
bool ck[2510][2510];
vector<int>best[2510];
void bfs(int start){
	vector<int>dist(n + 1, -1);//-1要访问，每次加一表边长
	queue<int>q;
	dist[start] = 0;
	q.push(start);
	while (!q.empty()) {
		int cur = q.front();
		if (cur != start) {
			ck[cur][start] = true;
			ck[start][cur] = true;
		}
		q.pop();
		if (dist[cur] == k + 1) continue;
		for (int nxt : G[cur]) {
			if (dist[nxt] == -1) {
				dist[nxt] = dist[cur] + 1;
				q.push(nxt);
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	freopen("holiday.in", "r", stdin);
	freopen("holiday.out", "w", stdout);
	cin >> n >> m >> k;
	for (int i = 2; i <= n; i++)
		cin >> score[i];
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) bfs(i);//建图 无向图
	for (int b = 2; b <= n; b++) {
		for (int a = 2; a <= n; a++) {
			if ((ck[a][b] || ck[b][a]) && ck[1][a] && b != 1) {
				best[b].push_back(a);
			}

		}	
		sort(best[b].begin(), best[b].end(), [](int a, int b) {
				return score[a] > score[b];
				});
		if (best[b].size() > 3) best[b].resize(3);
	}
ll ans = 0;
	for (int b = 2; b <= n; b++) {
		for (int c = 2; c <= n; c++) {
			if (b == c||!ck[b][c]) continue;
			for (auto a : best[b]) {
	
				for (auto d : best[c]) {
					if (a != c && a != d && b != d && a != b && c != d)
						ans = max(ans, score[a] + score[b] + score[c] + score[d]);
				}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}


#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring> // 用于 memset

using namespace std;

typedef long long ll;

const int MAXN = 2510;
const int MAXM = 20010;

int n, m, k;
ll score[MAXN];
bool ck[MAXN][MAXN];
vector<int> best[MAXN];

// --- 链式前向星部分 ---
int head[MAXN], cnt;
struct Edge {
    int to, next;
} edge[MAXM];

void add_edge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
// --------------------

void bfs(int start) {
    // 使用数组代替 vector 提高速度
    int dist[MAXN];
    memset(dist, -1, sizeof(dist));

    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur != start) {
            ck[start][cur] = true;
        }

        if (dist[cur] == k + 1) continue;

        // 遍历链式前向星
        for (int i = head[cur]; i; i = edge[i].next) {
            int nxt = edge[i].to;
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
}

int main() {
    // 基础优化
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 文件操作
    // freopen("holiday.in", "r", stdin);
    // freopen("holiday.out", "w", stdout);

    cin >> n >> m >> k;
    for (int i = 2; i <= n; i++) cin >> score[i];

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
        add_edge(y, x);
    }

    // BFS 预处理两点间可达性
    for (int i = 1; i <= n; i++) bfs(i);

    // 预处理 best 数组（每个点作为 B 时，可选的最佳 A 点）
    for (int b = 2; b <= n; b++) {
        for (int a = 2; a <= n; a++) {
            if (a != b && ck[a][b] && ck[1][a]) {
                best[b].push_back(a);
            }
        }
        sort(best[b].begin(), best[b].end(), [](int x, int y) {
            return score[x] > score[y];
            });
        if (best[b].size() > 3) best[b].resize(3);
    }

    ll ans = 0;
    // 枚举 B 和 C
    for (int b = 2; b <= n; b++) {
        for (int c = 2; c <= n; c++) {
            if (b == c || !ck[b][c]) continue;
            for (int a : best[b]) {
                for (int d : best[c]) {
                    // 确保 A, B, C, D 互不相同
                    if (a != c && a != d && b != d) {
                        ans = max(ans, score[a] + score[b] + score[c] + score[d]);
                    }
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
#include<iostream>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;
struct Node {
	int b;
	int k;
	int peo;
	bool operator<(const Node& other)const {
		return (b+k*(2*peo+1))<(other.b + (2*other.peo+1) * other.k);
	}
};
int get(Node &a) {
	return a.b + (2*a.peo+1) * a.k;
}

priority_queue<Node>q;
int n, m;
Node p[(int)1e5 + 5];
signed main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> p[i].k >> p[i].b;
		p[i].peo = 1;
		q.push(p[i]);
	}
	int ans = 0;
	while (n) {
		Node cur = q.top();
		q.pop();
		if (get(cur) <= 0) break;
		n--;
		ans += get(cur);
		cur.peo++;
		q.push(cur);
	}
	cout << ans;
	return 0;
}
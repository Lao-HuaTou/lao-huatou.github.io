//n点 m边 k个question
//q[i]有u，v，limit
//表示从u到v的路径是否严格小于limit
//并查集
#include "FileName.cpp"
//按q中的limit升序排序
#include<algorithm>
const int K = 10000;
vector<Edge>q(K),edge(N);
void solve2() {
	sort(q.begin(),q.end());
	for (int i = 0, j = 0; i < n; i++) {
		for (; edge[j].w < q[i].w; j++) {
			merge(edge[i].v, edge[i].u);

		}
		if (find(q[i].u) != find(q[i].v)) {

		}
	}
}
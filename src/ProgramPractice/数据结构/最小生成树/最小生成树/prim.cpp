#include "FileName.cpp"
#include<queue>
struct Node {
	int x, w;
	bool operator<(const Node& x) {
		return w < x.w;
	}
};
priority_queue<Node>q;
void prim() {
	q.push({ edge[0].v,edge[0].w });
	while (!q.empty()) {

	}

}

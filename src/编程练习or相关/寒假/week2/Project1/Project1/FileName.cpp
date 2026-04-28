#include<vector>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
struct opration {
	string act;
	int x,y;
};
vector<opration>op;
bool vis[10010][256];
bool finish;
int r;
void apply(int n,int tar) {
	if (n == tar + 1) {
		cout << "Yes\n";
		finish = true;
		return;
	}
	if (vis[n][r] || finish) return;
	vis[n][r] = true;
	opration* cur = &op[n-1];
	if (cur->act == "add") {
		r = (r + cur->x) % 256;
		apply(n + 1, tar);
	}
	else if (cur->act == "beq") {
		if (r == cur->x) apply(cur->y,tar);
		else apply(n + 1,tar);
	}
	else if (cur->act == "bne") {
		if(r!=cur->x) apply(cur->y,tar);
		else apply(n + 1,tar);
	}
	else if (cur->act == "blt") {
		if(r<cur->x) apply(cur->y,tar);
		else apply(n + 1,tar);
	}
	else {
		if (r > cur->x) apply(cur->y,tar);
		else apply(n + 1,tar);
	}
}
int main()
{
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		op.clear();
		op.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> op[i].act;
			if (op[i].act == "add") {
				cin >> op[i].x;
				op[i].y = 0;
			}
			else {
				cin >> op[i].x >> op[i].y;
			}
		}
		r = 0;
		finish = false;
		memset(vis,0,sizeof(vis));
		apply(1,n);
		if (!finish) cout << "No\n";
	}
	return 0;
}
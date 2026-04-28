#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
#include<cstring>
using namespace std;
int dist[100000];
string change(string s,int i,int op) {
	int x = s[i] - '0';
	if (op == 1) {
		if(x==9) x = 1;
		else x++;
	}
	else {
		if (x == 1) x = 9;
		else x--;
	}
	s[i] = x + '0';
	return s;
}
int bfs() {
	memset(dist, -1, sizeof(dist));
	string init, tar;
	cin >> init >> tar;
	if (init == tar) return 0;
	queue<string>q;
	q.push(init);
	dist[stoi(init)] = 0;
	while (!q.empty())
	{
		string now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			for (int op : {-1, 1}) {
				string next = change(now, i, op);
				if (dist[stoi(next)] == -1) {
					dist[stoi(next)] = dist[stoi(now)] + 1;
					if (next == tar) return dist[stoi(next)];
					q.push(next);
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			string next=now;
			swap(next[i], next[i + 1]);
			if (dist[stoi(next)] == -1) {
				dist[stoi(next)] = dist[stoi(now)] + 1;
				if (next == tar) return dist[stoi(next)];
				q.push(next);
			}
		}
	}
	return -1;
}
int main()
{
	int t; cin >> t;
	while (t--) {
		cout << bfs() << endl;
	}
	return 0;
}
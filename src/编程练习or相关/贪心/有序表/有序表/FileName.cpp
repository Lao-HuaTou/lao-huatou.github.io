#include<iostream>
#include<set>
using namespace std;
struct Node {
	int x;// value
	int y;//arr
	int z;//arr[i]
	bool operator<(const Node& other) const {
		return x == other.x ? y < other.y : x < other.x;
	}
};
set<Node>ar;
int main()
{
	int n; cin >> n;
	

}
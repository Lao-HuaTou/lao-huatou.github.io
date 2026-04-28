#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int n, k;
const int N = 5e4 + 5;


int p[N];
int dpt[N];
void build(int x) {
	for (int i = 0;i < n;i++) {
		p[i] = i;
		dpt[i] = 1;
	}
}
void merge() {

}




int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> k;


}
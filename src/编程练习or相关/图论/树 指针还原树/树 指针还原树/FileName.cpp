#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include<cstdio>

using namespace std;
struct node {
	bool valued;
	int v;
	node* left, * right;
	node() :valued(false), v(0), left(NULL), right(NULL) {}
    //node() {
    //    valued = false;
    //    v = 0;
    //    left = right = NULL;
    //}
};
struct Node {
    int v = 0;
    int left = 0;
    int right = 0;
    bool have_value = false;

    // 依然可以保留构造函数用于特殊用途
    Node() = default;
};
node* root;
bool failed;

node* newnode() { return new node(); }

void addnode(int v, string s) {
    node* u = root;
    for (int i = 0;i < s.length();i++) {
        if (s[i] == 'L') {
            if (u->left == NULL)u->left = newnode();
            u = u->left;
        }
        if (s[i] == 'R') {
            if (u->right == NULL)u->right = newnode();
            u = u->right;
        }
        if (u->valued)failed = true;
        u->v = v;
        u->valued = true;
    }

}
void solve() {
    vector<int> ans;
    queue<node*> q;
    if (root) q.push(root);

    while (!q.empty()) {
        node* u = q.front(); q.pop();
        if (!u->valued) { failed = true; break; }
        ans.push_back(u->v);
        if (u->left) q.push(u->left);
        if (u->right) q.push(u->right);
    }

    if (failed) cout << "not complete" << endl;
    else {
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i] << (i == ans.size() - 1 ? "" : " ");
        cout << endl;
    }
}


int main() {
    string s;cin >> s;
    while (cin >> s) {
        failed = false;
        root = newnode();
        while (s != "()") {
            int v = stoi(s.substr(1, s.find(',') - 1));
            string path = "";
            size_t comma = s.find(',');
            if (s.find(')') - comma > 1) {
                path = s.substr(comma + 1, s.find(')') - comma - 1);
            }
            addnode(v, path);
            cin >> s;

        }
        solve();

    }
    return 0;
}
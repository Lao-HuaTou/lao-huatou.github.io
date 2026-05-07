#include <vector>
#include <string>
using namespace std;
// 另一棵树的子树
// 给你两棵二叉树root和subRoot
// 检验root中是否包含和subRoot具有相同结构和节点值的子树
// 如果存在，返回true
// 否则，返回false
// 测试链接 : https://leetcode.cn/problems/subtree-of-another-tree/
class Solution {
public:
    // 不要提交这个类
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    // 方法1
    // 暴力递归
    // 时间复杂度O(n * m)
    bool isSubtree(TreeNode* t1, TreeNode* t2) {
        if (t1 != nullptr && t2 != nullptr) {
            return same(t1, t2) || isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
        }
        return t2 == nullptr;
    }

    // 判断a和b这两棵树是否完全一样
    bool same(TreeNode* a, TreeNode* b) {
        if (a == nullptr && b == nullptr) {
            return true;
        }
        if (a != nullptr && b != nullptr) {
            return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
        }
        return false;
    }

    // 方法2
    // 二叉树先序序列化 + KMP算法匹配
    // 时间复杂度O(n + m)
    bool isSubtree2(TreeNode* t1, TreeNode* t2) {
        if (t1 != nullptr && t2 != nullptr) {
            vector<string> s1;
            vector<string> s2;
            serial(t1, s1);
            serial(t2, s2);
            return kmp(s1, s2) != -1;
        }
        return t2 == nullptr;
    }

    void serial(TreeNode* head, vector<string>& path) {
        if (head == nullptr) {
            path.push_back("null"); // 用字符串"null"代替 Java 的 null
        }
        else {
            path.push_back(to_string(head->val));
            serial(head->left, path);
            serial(head->right, path);
        }
    }

    int kmp(const vector<string>& s1, const vector<string>& s2) {
        int n = s1.size(), m = s2.size(), x = 0, y = 0;
        if (m == 0) return 0;
        vector<int> next = nextArray(s2, m);
        while (x < n && y < m) {
            if (isEqual(s1[x], s2[y])) {
                x++;
                y++;
            }
            else if (y == 0) {
                x++;
            }
            else {
                y = next[y];
            }
        }
        return y == m ? x - y : -1;
    }

    vector<int> nextArray(const vector<string>& s, int m) {
        if (m == 1) {
            return { -1 };
        }
        vector<int> next(m);
        next[0] = -1;
        next[1] = 0;
        int i = 2, cn = 0;
        while (i < m) {
            if (isEqual(s[i - 1], s[cn])) {
                next[i++] = ++cn;
            }
            else if (cn > 0) {
                cn = next[cn];
            }
            else {
                next[i++] = 0;
            }
        }
        return next;
    }

    // 比对两个字符串是否相等
    // 在 C++ 序列化中统一使用 "null" 字符串，逻辑简化
    bool isEqual(const string& a, const string& b) {
        return a == b;
    }
};





#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ---------------------------------------------------------
// 全局静态空间：对应 Java 的 static 成员
// 假设节点最大数量为 20001 (根据题目数据量调整)
const int MAXN = 20005;
string s1[MAXN];
string s2[MAXN];
int next_arr[MAXN];
int size1, size2;

// 二叉树结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

// ---------------------------------------------------------
// 方法1：暴力递归 (Same 逻辑)
bool same(TreeNode* a, TreeNode* b) {
    if (a == nullptr && b == nullptr) return true;
    if (a != nullptr && b != nullptr) {
        return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
    }
    return false;
}

bool isSubtree(TreeNode* t1, TreeNode* t2) {
    if (t1 != nullptr && t2 != nullptr) {
        return same(t1, t2) || isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
    }
    return t2 == nullptr;
}

// ---------------------------------------------------------
// 方法2：序列化 + KMP

// 序列化函数：直接操作全局数组 s1/s2 和计数器 size
void serial(TreeNode* head, string* path, int& size) {
    if (head == nullptr) {
        path[size++] = "null";
    }
    else {
        path[size++] = to_string(head->val);
        serial(head->left, path, size);
        serial(head->right, path, size);
    }
}

// KMP next 数组计算
void getNextArray(string* s, int m) {
    if (m <= 1) {
        if (m == 1) next_arr[0] = -1;
        return;
    }
    next_arr[0] = -1;
    next_arr[1] = 0;
    int i = 2, cn = 0;
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            next_arr[i++] = ++cn;
        }
        else if (cn > 0) {
            cn = next_arr[cn];
        }
        else {
            next_arr[i++] = 0;
        }
    }
}

// KMP 主匹配逻辑
int kmp() {
    if (size2 == 0) return 0;
    getNextArray(s2, size2);
    int x = 0, y = 0;
    while (x < size1 && y < size2) {
        if (s1[x] == s2[y]) {
            x++; y++;
        }
        else if (y == 0) {
            x++;
        }
        else {
            y = next_arr[y];
        }
    }
    return (y == size2) ? (x - y) : -1;
}

// 统一调用入口
bool isSubtree2(TreeNode* t1, TreeNode* t2) {
    if (t1 == nullptr) return t2 == nullptr;
    if (t2 == nullptr) return true;

    // 重置全局计数器
    size1 = 0;
    size2 = 0;

    serial(t1, s1, size1);
    serial(t2, s2, size2);

    return kmp() != -1;
}


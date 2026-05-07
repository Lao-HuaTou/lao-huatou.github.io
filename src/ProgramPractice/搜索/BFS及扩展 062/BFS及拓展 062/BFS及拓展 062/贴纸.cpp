#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

// 贴纸拼词
// 我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
// 您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切割单个字母并重新排列它们
// 如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。
// 返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 -1
// 注意：在所有的测试用例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选择的
// 并且 target 被选择为两个随机单词的连接。
// 测试链接 : https://leetcode.cn/problems/stickers-to-spell-word/
class Solution {
public:
    static const int MAXN = 401;

    // 使用 static 处理大数据量
    static string queue[MAXN];
    static int l, r;

    // 下标0 -> a
    // 下标1 -> b
    // 下标2 -> c
    // ...
    // 下标25 -> z
    static vector<vector<string>> graph;
    static unordered_set<string> visited;

    // 宽度优先遍历的解法
    // 也可以使用动态规划
    // 后续课程会有动态规划专题讲解
    int minStickers(vector<string>& stickers, string target) {
        // 初始化全局容器
        if (graph.empty()) graph.resize(26);
        for (int i = 0; i < 26; i++) {
            graph[i].clear();
        }
        visited.clear();

        for (string str : stickers) {
            str = sortString(str);
            for (int i = 0; i < str.length(); i++) {
                if (i == 0 || str[i] != str[i - 1]) {
                    graph[str[i] - 'a'].push_back(str);//每次只处理剩余部分首字母  剪枝
                }
            }
        }

        target = sortString(target);
        visited.insert(target);
        l = r = 0;
        queue[r++] = target;//queue储存过程中所有的种类
        int level = 1;

        // 使用队列的形式是整层弹出
        while (l < r) {
            int size = r - l;//队列大小
            for (int i = 0; i < size; i++) {
                string cur = queue[l++];
                // graph.get(cur.charAt(0) - 'a') -> graph[cur[0] - 'a']
                for (const string& s : graph[cur[0] - 'a']) {//遍历以剩余首字母开头的贴纸
                    string nxt = nextString(cur, s);
                    if (nxt == "") {
                        return level;
                    }
                    else if (visited.find(nxt) == visited.end()) {//没找到
                        visited.insert(nxt);
                        queue[r++] = nxt;
                    }
                }
            }
            level++;
        }
        return -1;
    }

    // 对应 Java 的 sort 方法
    string sortString(string str) {
        sort(str.begin(), str.end());
        return str;
    }

    // 对应 Java 的 next 方法
    string nextString(const string& t, const string& s) {
        string res = "";
        for (int i = 0, j = 0; i < t.length();) {
            if (j == s.length()) {
                res += t[i++];
            }
            else {
                if (t[i] < s[j]) {
                    res += t[i++];
                }
                else if (t[i] > s[j]) {
                    j++;
                }
                else {
                    i++;
                    j++;
                }
            }
        }
        return res;
    }
};

// 静态成员变量初始化
string Solution::queue[MAXN];
int Solution::l = 0;
int Solution::r = 0;
vector<vector<string>> Solution::graph;
unordered_set<string> Solution::visited;
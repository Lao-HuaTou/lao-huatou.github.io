#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MAXN = 1000005;
int nxt[MAXN];
void buildNext(const string& p, int m) {
    if (m == 0) return;
    nxt[0] = -1;
    if (m == 1) return;

    nxt[1] = 0;
    int i = 2;  // 当前要求的 next 值位置
    int cn = 0; // 跳动指针：当前要与 p[i-1] 比对的下标

    while (i <= m) {
        if (p[i - 1] == p[cn]) {
            // 情况一：匹配成功，当前位置的 next 值是前一个匹配长度 + 1
            nxt[i++] = ++cn;
        }
        else if (cn > 0) {
            // 情况二：匹配失败，但还能往回跳（利用已知的最长前缀后缀）
            cn = nxt[cn];
        }
        else {
            // 情况三：跳到头了也没匹配上，当前位置 next 值为 0
            nxt[i++] = 0;
        }
    }
}

int kmpSearch(string s, string p) {
    int n = s.length();
    int m = p.length();

    // 边界处理
    if (m == 0) return 0;
    if (n < m) return -1;

    // 1. 预处理模式串
    buildNext(p, m);

    // 2. 开始比对
    int x = 0; // 主串指针
    int y = 0; // 模式串指针

    while (x < n && y < m) {
        if (s[x] == p[y]) {
            x++;
            y++;
        }
        else if (y == 0) {
            // 模式串第一位就没对上，主串只能硬着头皮往前走
            x++;
        }
        else {
            // 核心跳转：y 跳到当前能复用的最长前缀之后
            y = nxt[y];
        }
    }

    // 如果 y 跑完了模式串全程，说明匹配成功
    return (y == m) ? (x - y) : -1;
}

vector<int> findAllOccurrences(string s, string p) {
    vector<int> positions;
    int n = s.length();
    int m = p.length();

    if (m == 0) return positions;
    buildNext(p, m);

    int x = 0; // 主串指针
    int y = 0; // 模式串指针

    while (x < n) {
        if (s[x] == p[y]) {
            x++;
            y++;
        }
        else if (y == 0) {
            x++;
        }
        else {
            y = nxt[y];
        }

        // --- 核心改动点 ---
        if (y == m) {
            // 记录当前匹配成功的起始下标
            positions.push_back(x - y);
            // 关键：匹配成功后，y 像失败一样跳回 nxt[y]，继续找下一个匹配
            // 这样可以处理“重叠匹配”，如在 "aaaaa" 中找 "aaa"
            y = nxt[y];

            // 注意：如果你的 nxt 数组只算到 m-1，
            // 且你想找的是非重叠匹配，也可以令 y = 0。
            // 但在竞赛中，y = nxt[y] 是最通用的做法（需保证 buildNext 处理了相关逻辑）。
            // 如果 buildNext 没算 nxt[m]，这里最稳妥的做法是手动对比或跳回。
        }
    }

    return positions;
}
int main() {


    return 0;
}
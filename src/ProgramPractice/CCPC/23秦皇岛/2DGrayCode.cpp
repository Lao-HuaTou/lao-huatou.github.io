#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int size = 1 << n;
    vector<int> gray(size);
    // 1. 生成长度为 2^n 的一维格雷码
    for (int i = 0; i < size; ++i) {
        gray[i] = i ^ (i >> 1);
    }
    // 2. 构造并输出矩阵
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // 将第 i 个格雷码左移 n 位作为高位，拼上第 j 个格雷码作为低位
            int result = (gray[i] << n) | gray[j];
            cout << result << (j == size - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
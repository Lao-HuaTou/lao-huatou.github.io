#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// 子矩阵最大累加和问题
// 给定一个二维数组grid，找到其中子矩阵的最大累加和
// 返回拥有最大累加和的子矩阵左上角和右下角坐标
// 如果有多个子矩阵都有最大累加和，返回哪一个都可以
// 测试链接 : https://leetcode.cn/problems/max-submatrix-lcci/
class Code06_MaximumSubmatrix {
public:
    // 如果行和列的规模都是n，时间复杂度O(n^3)，最优解了
    static vector<int> getMaxMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        long long max_sum = LLONG_MIN; // 涉及累加，使用 long long 防止溢出风险
        int a = 0, b = 0, c = 0, d = 0;

        // 使用 static 优化，避免频繁分配内存
        static int nums[201];

        for (int up = 0; up < n; up++) {
            // 每次更换上边界，重置压缩数组
            for (int i = 0; i < m; i++) nums[i] = 0;

            for (int down = up; down < n; down++) {
                // 如下代码就是题目1的附加问题 :
                // 子数组中找到拥有最大累加和的子数组
                // pre 记录当前子数组的累加和
                for (int l = 0, r = 0; r < m; r++) {
                    static long long pre; // 逻辑内部变量
                    if (r == 0) pre = LLONG_MIN; // 每一层 down 扫描时，l, r 的逻辑初始化

                    nums[r] += grid[down][r];
                    if (r == l) { // 初始或强制换头
                        pre = nums[r];
                    }
                    else if (pre >= 0) {
                        pre += nums[r];
                    }
                    else {
                        pre = nums[r];
                        l = r;
                    }

                    if (pre > max_sum) {
                        max_sum = pre;
                        a = up;
                        b = l;
                        c = down;
                        d = r;
                    }
                }
            }
        }
        return { a, b, c, d };
    }
};
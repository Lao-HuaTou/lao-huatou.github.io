#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 使用 __int128 防止乘法溢出，但在输出和输入时需要转换
typedef long long ll;
typedef unsigned long long int128;

int N;
ll M;
// 40以内的质数
int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
vector<ll> valid_lcms;

// DFS 生成所有满足条件的 LCM < M
// p_idx: 当前处理到第几个质数
// current_val: 当前的 LCM 值
void dfs(int p_idx, ll current_val) {
    if (p_idx == 12) {
        valid_lcms.push_back(current_val);
        return;
    }

    // 选项1: 当前质数不参与 (即指数为0，相对于增加因子而言)
    // 或者说，我们保持当前的数值，去处理下一个质数
    dfs(p_idx + 1, current_val);

    // 选项2: 当前质数贡献 p^1, p^2 ... p^k，前提是 p^k <= N
    ll p = primes[p_idx];
    ll p_pow = p; // p 的幂次
    ll next_val = current_val;

    // 尝试乘以 p 的更高次幂
    while (p_pow <= N) {
        // 检查溢出和是否 >= M
        if ((int128)next_val * p >= M) break;

        // 更新 LCM 值。注意这里逻辑：LCM是取各质因数最高次幂。
        // 因为我们是按质数顺序遍历，直接乘上去即可。
        next_val *= p;

        dfs(p_idx + 1, next_val);

        // 准备下一次循环，检查更高的幂次 (例如从 2^1 变成 2^2)
        // 只有当 p^(k+1) <= N 时，这个更高的幂次才可能存在于 1..N 的某个数中
        if (p_pow * p > N) break;
        p_pow *= p;
    }
}

ll solve() {
    valid_lcms.clear();
    // 从 LCM = 1 开始搜索
    dfs(0, 1);

    // 排序并去重 (虽然DFS逻辑通常不会产生重复，但为了保险)
    sort(valid_lcms.begin(), valid_lcms.end());
    valid_lcms.erase(unique(valid_lcms.begin(), valid_lcms.end()), valid_lcms.end());

    ll count_less_than_M = 0;

    for (ll L : valid_lcms) {
        // 1. 找出 L 的所有质因子
        vector<ll> factors;
        ll temp = L;
        for (int p : primes) {
            if (temp % p == 0) {
                factors.push_back(p);
                while (temp % p == 0) temp /= p;
            }
        }

        // 2. 容斥原理计算 LCM 恰好为 L 的方案数
        ll ways_exact = 0;
        int k = factors.size();
        int num_subsets = 1 << k; // 2^k 种容斥组合

        for (int mask = 0; mask < num_subsets; mask++) {
            ll divisor = 1;
            int set_bits = 0;
            // 构建容斥的除数 (例如 L/p, L/(p*q) ...)
            for (int i = 0; i < k; i++) {
                if ((mask >> i) & 1) {
                    divisor *= factors[i];
                    set_bits++;
                }
            }

            // 计算 target = L / (选中的质因子积)
            // 我们需要找出 1..N 中有多少个数能整除 target
            ll target = L / divisor;
            int count_divisors = 0;
            for (int x = 1; x <= N; x++) {
                if (target % x == 0) {
                    count_divisors++;
                }
            }

            // 这些数的任意组合(子集)的 LCM 都会是 target 的约数
            // 子集数为 2^count_divisors
            ll subsets = 1LL << count_divisors;

            // 容斥：奇减偶加
            if (set_bits % 2 == 1) {
                ways_exact -= subsets;
            }
            else {
                ways_exact += subsets;
            }
        }

        // 特殊处理：如果 L=1，上面的容斥计算出的 ways_exact 是 2 (空集和{1})
        // 但题目要求非空子集，且空集不算在 LCM=1 的统计中(或者说我们只减去合法的非空集合)
        // 实际上，如果 L=1，子集只有 {1} 这一种情况。
        // 上述公式算出 2^1 = 2。包含了空集。我们需要减去空集带来的 1。
        // 对于 L > 1，空集不会被算作 LCM=L，因为空集 LCM 通常定义为 1 或 0。
        // 在容斥公式中，mask=0 时加上的 2^count 包含了空集。
        // 只有当 L=1 时，我们需要把空集剔除。
        if (L == 1) ways_exact--;

        count_less_than_M += ways_exact;
    }

    // 总方案数 (2^N - 1) - (LCM < M 的方案数)
    ll total_subsets = (1LL << N) - 1;
    return total_subsets - count_less_than_M;
}

int main() {
    int t;
    if (cin >> t) {
        int case_num = 1;
        while (t--) {
            cin >> N >> M;
            cout << "Case #" << case_num++ << ": " << solve() << endl;
        }
    }
    return 0;
}

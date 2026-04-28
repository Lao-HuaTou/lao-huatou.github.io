#include<iostream>
#include<vector>
using namespace std;
vector<int>ar;
long long merge(int l,int mid,int r)
{
    long long inv = 0;
    vector<int>temp(r - l + 1);
    int i = l, j = mid + 1,k=0;
    while (i <= mid && j <= r) {
        if (ar[i] <= ar[j]) {
            temp[k++] = ar[i++];
        }
        else {
            temp[k++] = ar[j++];
            inv += (mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = ar[i++];
    while (j <= r) temp[k++] = ar[j++];
    for (int i = 0; i < k; i++)
        ar[l + i] = temp[i];
    return inv;
}
long long mergesort(int l,int r)
{
    long long inv = 0;
    if (l >= r) return 0;
    int  mid = (l + r) / 2;
        inv+=mergesort(l, mid);
        inv+=mergesort(mid + 1, r);
        inv+=merge(l, mid, r);
    return inv;
}
int main()
{
    int n; long long k;
    while (cin >> n >> k)
    {
        ar.resize(n);
        for (int i = 0; i < n; i++)
            cin >> ar[i];
        long long ans = 0;
        ans = mergesort(0, n - 1);
        if ((ans - k) <= 0) ans = 0;
        else ans = ans - k;
        cout << ans << endl;

    }
    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 树状数组类
class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};

// 离散化函数
void compress(vector<int>& arr) {
    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    for (int& val : arr) {
        val = lower_bound(sorted.begin(), sorted.end(), val) - sorted.begin() + 1;
    }
}

long long countInversions(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp = arr;
    compress(temp);  // 离散化

    FenwickTree ft(n);
    long long inversions = 0;

    // 从后往前遍历，统计每个元素前面有多少比它大的
    for (int i = n - 1; i >= 0; i--) {
        inversions += ft.query(temp[i] - 1);  // 比当前元素小的数量
        ft.update(temp[i], 1);
    }

    return inversions;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    while (cin >> n >> k) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        long long inversions = countInversions(arr);
        long long result = max(0LL, inversions - k);

        cout << result << "\n";
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100010

// 树状数组结构
typedef struct {
    int tree[MAX_N];
    int n;
} FenwickTree;

// 初始化树状数组
void initFenwick(FenwickTree* ft, int size) {
    ft->n = size;
    memset(ft->tree, 0, sizeof(ft->tree));
}

// 更新操作
void update(FenwickTree* ft, int idx, int delta) {
    while (idx <= ft->n) {
        ft->tree[idx] += delta;
        idx += idx & -idx;
    }
}

// 查询前缀和
int query(FenwickTree* ft, int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += ft->tree[idx];
        idx -= idx & -idx;
    }
    return sum;
}

// 用于排序的结构体
typedef struct {
    int value;
    int index;
} Element;

// 比较函数：按值排序
int cmp_value(const void* a, const void* b) {
    Element* x = (Element*)a;
    Element* y = (Element*)b;
    if (x->value == y->value) {
        return x->index - y->index;
    }
    return x->value - y->value;
}

// 离散化函数
void compress(int* arr, int* compressed, int n) {
    Element* elements = (Element*)malloc(n * sizeof(Element));

    // 存储原始值和索引
    for (int i = 0; i < n; i++) {
        elements[i].value = arr[i];
        elements[i].index = i;
    }

    // 按值排序
    qsort(elements, n, sizeof(Element), cmp_value);

    // 分配新的压缩值（处理重复值）
    int rank = 1;
    compressed[elements[0].index] = rank;

    for (int i = 1; i < n; i++) {
        if (elements[i].value != elements[i - 1].value) {
            rank++;
        }
        compressed[elements[i].index] = rank;
    }

    free(elements);
}

// 计算逆序对数量
long long countInversions(int* arr, int n) {
    int* compressed = (int*)malloc(n * sizeof(int));
    compress(arr, compressed, n);

    FenwickTree ft;
    initFenwick(&ft, n);

    long long inversions = 0;

    // 从后往前遍历
    for (int i = n - 1; i >= 0; i--) {
        // 查询比当前元素小的数量
        inversions += query(&ft, compressed[i] - 1);
        // 更新树状数组
        update(&ft, compressed[i], 1);
    }

    free(compressed);
    return inversions;
}

int main() {
    int n, k;

    while (scanf("%d %d", &n, &k) != EOF) {
        int* arr = (int*)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        long long inversions = countInversions(arr, n);
        long long result = inversions - k;
        if (result < 0) result = 0;

        printf("%lld\n", result);

        free(arr);
    }

    return 0;
}
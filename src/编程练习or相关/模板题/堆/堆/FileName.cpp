#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void stl_heap_demo() {
    cout << "=== STL 堆操作 ===" << endl;

    // nums: 待构建堆的整数数组
    vector<int> nums = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 1. 建立最大堆
    // make_heap: 将普通数组重新排列成堆结构
    make_heap(nums.begin(), nums.end());
    cout << "最大堆: ";
    // num: 循环变量，用于遍历和输出堆中元素
    for (int num : nums) cout << num << " ";
    cout << endl;

    // 2. 添加元素
    // value: 要插入堆的新元素值
    int value = 8;
    nums.push_back(value);
    // push_heap: 将新元素加入堆并调整堆结构
    push_heap(nums.begin(), nums.end());
    cout << "添加8后: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    // 3. 弹出堆顶
    // pop_heap: 将堆顶元素移到容器末尾，剩余部分重新调整成堆
    pop_heap(nums.begin(), nums.end());
    nums.pop_back();  // 删除最后一个元素（原堆顶）
    cout << "弹出堆顶后: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    // 4. 堆排序
    // sort_nums: 用于堆排序的数组副本
    vector<int> sort_nums = { 3, 1, 4, 1, 5, 9, 2, 6 };
    make_heap(sort_nums.begin(), sort_nums.end());
    // sort_heap: 对堆进行排序，变成有序数组
    sort_heap(sort_nums.begin(), sort_nums.end());
    cout << "堆排序结果: ";
    for (int num : sort_nums) cout << num << " ";
    cout << endl;
}






#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MinHeap {
private:
    // heap: 存储堆元素的动态数组
    vector<int> heap;

    // parent: 计算父节点索引
    // i: 当前节点索引
    int parent(int i) { return (i - 1) / 2; }

    // left: 计算左子节点索引  
    // i: 当前节点索引
    int left(int i) { return 2 * i + 1; }

    // right: 计算右子节点索引
    // i: 当前节点索引
    int right(int i) { return 2 * i + 2; }

    // heapifyUp: 上浮调整，维护堆性质
    // i: 需要上浮调整的节点索引
    void heapifyUp(int i) {
        // 循环条件：不在根节点且父节点值大于当前节点
        while (i > 0 && heap[parent(i)] > heap[i]) {
            // 交换当前节点与父节点
            swap(heap[i], heap[parent(i)]);
            // 更新当前节点索引为父节点位置
            i = parent(i);
        }
    }

    // heapifyDown: 下沉调整，维护堆性质
    // i: 需要下沉调整的节点索引
    void heapifyDown(int i) {
        // smallest: 记录最小值的节点索引，初始为当前节点
        int smallest = i;
        // l: 左子节点索引
        int l = left(i);
        // r: 右子节点索引  
        int r = right(i);
        // n: 堆的大小
        int n = heap.size();

        // 如果左子节点存在且比当前最小值小
        if (l < n && heap[l] < heap[smallest])
            smallest = l;
        // 如果右子节点存在且比当前最小值小
        if (r < n && heap[r] < heap[smallest])
            smallest = r;

        // 如果最小值不是当前节点，需要交换并继续调整
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // push: 插入元素到堆中
    // value: 要插入的元素值
    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // pop: 弹出堆顶元素
    // 返回值: 堆顶元素值，堆空时返回-1
    int pop() {
        if (heap.empty()) return -1;

        // root: 保存堆顶元素值
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return root;
    }

    // top: 获取堆顶元素值
    // 返回值: 堆顶元素值，堆空时返回-1
    int top() {
        if (heap.empty()) return -1;
        return heap[0];
    }

    // size: 获取堆的大小
    // 返回值: 堆中元素个数
    int size() { return heap.size(); }

    // empty: 判断堆是否为空
    // 返回值: 堆为空返回true，否则返回false
    bool empty() { return heap.empty(); }

    // print: 打印堆中所有元素
    void print() {
        cout << "堆内容: ";
        // num: 循环变量，用于遍历堆元素
        for (int num : heap) cout << num << " ";
        cout << endl;
    }
};

void min_heap_demo() {
    cout << "\n=== 手动实现最小堆 ===" << endl;
    // heap: 最小堆实例
    MinHeap heap;

    heap.push(3);
    heap.push(1);
    heap.push(4);
    heap.push(1);
    heap.push(5);

    heap.print();
    cout << "堆顶: " << heap.top() << endl;

    cout << "弹出顺序: ";
    while (!heap.empty()) {
        cout << heap.pop() << " ";
    }
    cout << endl;
}

class MaxHeap {
private:
    // heap: 存储堆元素的动态数组
    vector<int> heap;

    // parent: 计算父节点索引
    // i: 当前节点索引
    int parent(int i) { return (i - 1) / 2; }

    // left: 计算左子节点索引
    // i: 当前节点索引  
    int left(int i) { return 2 * i + 1; }

    // right: 计算右子节点索引
    // i: 当前节点索引
    int right(int i) { return 2 * i + 2; }

    // heapifyUp: 上浮调整，维护最大堆性质
    // i: 需要上浮调整的节点索引
    void heapifyUp(int i) {
        // 循环条件：不在根节点且父节点值小于当前节点
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // heapifyDown: 下沉调整，维护最大堆性质
    // i: 需要下沉调整的节点索引
    void heapifyDown(int i) {
        // largest: 记录最大值的节点索引，初始为当前节点
        int largest = i;
        // l: 左子节点索引
        int l = left(i);
        // r: 右子节点索引
        int r = right(i);
        // n: 堆的大小
        int n = heap.size();

        // 如果左子节点存在且比当前最大值大
        if (l < n && heap[l] > heap[largest])
            largest = l;
        // 如果右子节点存在且比当前最大值大
        if (r < n && heap[r] > heap[largest])
            largest = r;

        // 如果最大值不是当前节点，需要交换并继续调整
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // push: 插入元素到最大堆
    // value: 要插入的元素值
    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // pop: 弹出堆顶元素
    // 返回值: 堆顶元素值，堆空时返回-1
    int pop() {
        if (heap.empty()) return -1;

        // root: 保存堆顶元素值
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return root;
    }

    // top: 获取堆顶元素值
    // 返回值: 堆顶元素值，堆空时返回-1
    int top() {
        if (heap.empty()) return -1;
        return heap[0];
    }

    // size: 获取堆的大小
    // 返回值: 堆中元素个数
    int size() { return heap.size(); }

    // empty: 判断堆是否为空
    // 返回值: 堆为空返回true，否则返回false
    bool empty() { return heap.empty(); }

    // print: 打印堆中所有元素
    void print() {
        cout << "最大堆: ";
        // num: 循环变量，用于遍历堆元素
        for (int num : heap) cout << num << " ";
        cout << endl;
    }
};

void max_heap_demo() {
    cout << "\n=== 手动实现最大堆 ===" << endl;
    // heap: 最大堆实例
    MaxHeap heap;

    heap.push(3);
    heap.push(1);
    heap.push(4);
    heap.push(1);
    heap.push(5);

    heap.print();
    cout << "堆顶: " << heap.top() << endl;

    cout << "弹出顺序: ";
    while (!heap.empty()) {
        cout << heap.pop() << " ";
    }
    cout << endl;
}

#include <queue>
#include <functional>

void priority_queue_demo() {
    cout << "\n=== 优先队列示例 ===" << endl;

    // max_pq: 最大优先队列（默认）
    priority_queue<int> max_pq;
    max_pq.push(3);
    max_pq.push(1);
    max_pq.push(4);
    max_pq.push(1);
    max_pq.push(5);

    cout << "最大优先队列: ";
    while (!max_pq.empty()) {
        cout << max_pq.top() << " ";
        max_pq.pop();
    }
    cout << endl;

    // min_pq: 最小优先队列，使用greater比较器
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(4);
    min_pq.push(1);
    min_pq.push(5);

    cout << "最小优先队列: ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";
        min_pq.pop();
    }
    cout << endl;

    // cmp: 自定义比较函数的lambda表达式
    // left, right: 要比较的两个pair对象
    auto cmp = [](pair<int, int> left, pair<int, int> right) {
        return left.second > right.second;  // 按第二个元素最小堆
        };

    // custom_pq: 自定义优先队列，按pair的第二个元素排序
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> custom_pq(cmp);

    custom_pq.push({ 1, 5 });
    custom_pq.push({ 2, 3 });
    custom_pq.push({ 3, 8 });
    custom_pq.push({ 4, 1 });

    cout << "自定义优先队列: ";
    while (!custom_pq.empty()) {
        // p: 当前队首元素
        auto p = custom_pq.top();
        cout << "(" << p.first << "," << p.second << ") ";
        custom_pq.pop();
    }
    cout << endl;
}




void top_k_demo() {
    cout << "\n=== Top K 问题 ===" << endl;

    // nums: 输入数据数组
    vector<int> nums = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    // k: 要找的前K个元素
    int k = 3;

    // min_heap: 最小堆，用于找最大的K个元素
    priority_queue<int, vector<int>, greater<int>> min_heap;

    // num: 循环变量，遍历输入数组的每个元素
    for (int num : nums) {
        min_heap.push(num);
        if (min_heap.size() > k) {
            min_heap.pop();
        }
    }

    cout << "最大的" << k << "个元素: ";
    while (!min_heap.empty()) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    cout << endl;

    // max_heap: 最大堆，用于找最小的K个元素
    priority_queue<int> max_heap;

    for (int num : nums) {
        max_heap.push(num);
        if (max_heap.size() > k) {
            max_heap.pop();
        }
    }

    cout << "最小的" << k << "个元素: ";
    while (!max_heap.empty()) {
        cout << max_heap.top() << " ";
        max_heap.pop();
    }
    cout << endl;
}



























(1) : 求父子节点 :
    父(i) = > (i - 1) / 2;
左子(i) = > i * 2 + 1
右子(i) = > i * 2 + 2
大根上滤(i) {
    while (堆[i] > 堆[父(i)])
    {
        交换(i, 父(i));
        j = 父(i);
    }
}
// 注: 这里大根下滤使用递归方式
// 插入堆首
大根下滤(i) {
    j = i;
    if (左子(i) < 总 && 堆[左子(i)] > 堆[j])
    {
        j = 左子(i);
    }
    if (右子(i) < 总 && 堆[右子(i)] > 堆[j])
    {
        j = 右子(i);
    }
    if (i != j)
    {
        交换(i, j);
        大根下滤(j);
    }
}
(2 - 1) ﻿
04:49
自顶向下建堆法﻿
大根上滤建堆法::O(NlogN)
for (i) {
    上滤(i);
}
(2 - 2) ﻿
06:02
自下而上建堆法
﻿::O(N)
从倒数第二层开始大根下滤 :
    for (i = 父(总 - 1); i倒序)
    {
        下滤(i);
    }
(3)﻿
堆的具体应用
(3 - 1)应用1:
最小优先队列(个人已 : 常用于一些类贪心路径搜索算法的 * **优化, 如A * 算法, dj算法) :
    弹出最小元素() {
    output = 堆[0];
    堆[0] = 堆[总 - 1];
    下滤(0);
    return output;
}
插入(input) {
    堆[总] = input;
    上滤(总);
    总++;
}
(3 - 2)应用2: 堆排
堆排序
小根堆排升序(output数组) {
    j = 总 - 1;
    for (i)
    {
        output[i] = 堆[0];
        堆[0] = 堆[j];
        j--;
        下滤(0);
    }
}
优化堆排序: 大根堆排序
大根堆排升序()::O(NlogN) {
    for (i = 总 - 1)
    {
        交换(0, i);
        总--;
        下滤(0);
    }
}



缩写备注:

for (i) = > for (i = 0; i < 总; i++)


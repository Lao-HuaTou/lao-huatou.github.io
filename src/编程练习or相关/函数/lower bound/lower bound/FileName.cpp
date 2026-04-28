#include <stdio.h>
#include <stdlib.h>

// 比较函数
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// lower_bound 实现
// 返回第一个大于等于 target 的元素位置
int lower_bound(int arr[], int n, int target) {
    int left = 0;
    int right = n;  // 注意：右边界是 n，不是 n-1

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return left;  // 返回的位置在 [0, n] 范围内
}

// 通用版本的 lower_bound，支持任意数据类型
void* lower_bound_generic(void* base, size_t num, size_t size,
    const void* target,
    int (*compare)(const void*, const void*)) {
    char* arr = (char*)base;
    size_t left = 0;
    size_t right = num;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        char* mid_ptr = arr + mid * size;

        if (compare(mid_ptr, target) < 0) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return arr + left * size;
}
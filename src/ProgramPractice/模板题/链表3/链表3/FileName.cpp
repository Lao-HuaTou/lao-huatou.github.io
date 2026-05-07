#include<stdio.h>
#include<stdlib.h>

struct cell {
    int x;
    struct cell* next;
};

// 全局数组，记录每个值对应的节点指针
struct cell* pos[1000001] = { NULL };

void fun1(int x, int y) {
    // 如果y已经存在，不插入（题目保证所有数字均不相同）
    if (pos[y] != NULL) return;

    // 创建新节点
    struct cell* new_node = (struct cell*)malloc(sizeof(struct cell));
    new_node->x = y;

    // 插入到x后面
    new_node->next = pos[x]->next;
    pos[x]->next = new_node;

    // 记录y的位置
    pos[y] = new_node;
}

void fun2(int x) {
    if (pos[x] == NULL) return;

    if (pos[x]->next == NULL) {
        printf("0\n");
    }
    else {
        printf("%d\n", pos[x]->next->x);
    }
}

void fun3(int x) {
    if (pos[x] == NULL || pos[x]->next == NULL) return;

    struct cell* to_delete = pos[x]->next;
    int y = to_delete->x;  // 要删除的节点的值

    // 跳过要删除的节点
    pos[x]->next = to_delete->next;

    // 从pos数组中删除
    pos[y] = NULL;

    // 释放内存
    free(to_delete);
}

int main()
{
    int q;
    scanf("%d", &q);

    // 初始化：创建值为1的节点
    struct cell* head = (struct cell*)malloc(sizeof(struct cell));
    head->x = 1;
    head->next = NULL;
    pos[1] = head;

    while (q--)
    {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            fun1(x, y);
        }
        else if (op == 2) {
            int x;
            scanf("%d", &x);
            fun2(x);
        }
        else if (op == 3) {
            int x;
            scanf("%d", &x);
            fun3(x);
        }
    }

    // 释放所有节点内存
    for (int i = 1; i <= 1000000; i++) {
        if (pos[i] != NULL) {
            free(pos[i]);
            pos[i] = NULL;
        }
    }

    return 0;
}
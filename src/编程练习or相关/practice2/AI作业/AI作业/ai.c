#pragma warning(disable:4996)
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 20     //
#define ID_MAX 20
#define COURSE_NUM 5    // 任务要求至少5门课
#define SORT_BY_ID 1
#define SORT_BY_TOTAL 2
#define SORT_BY_SCORE 3

// 2. 结构体定义
typedef struct Student {
    char id[ID_MAX];
    char name[NAME_MAX];
    float scores[COURSE_NUM];
    float total;
    struct Student* next;
} Student;

// 3. 函数原型声明
Student* initList();
void addStudent(Student* dummy);
void sortList(Student* dummy, int mode, int courseIndex);
void saveToFile(Student* dummy);
void loadFromFile(Student* dummy);
void displayAll(Student* dummy);
void deleteStudent(Student* dummy);
void modifyStudent(Student* dummy);
void searchStudent(Student* dummy);

// 4. 主函数 (菜单逻辑)
int main() {
    // 解决控制台乱码（如果之前试了有用的话）
    SetConsoleOutputCP(65001); 

    Student* dummy = initList();
    int choice;

    while (1) {
        printf("\n====== 学生成绩管理系统 ======\n");
        printf("1. 录入/增加学生 (Add)\n");
        printf("2. 删除学生 (Delete)\n");
        printf("3. 修改成绩 (Modify)\n");
        printf("4. 查询学生 (Search)\n");
        printf("5. 排序并显示所有人 (Sort & Display)\n");
        printf("6. 从文件导入 (Load)\n");
        printf("7. 保存到文件并退出 (Save & Exit)\n");
        printf("==============================\n");
        printf("请选择功能: ");
        scanf("%d", &choice);
        int sMode, cIdx;
        switch (choice) {
        case 1: addStudent(dummy); break;
        case 2: deleteStudent(dummy); break;
        case 3: modifyStudent(dummy); break;
        case 4: searchStudent(dummy); break;
        case 5:
            sMode, cIdx = 0;
            printf("排序方式: 1.学号 2.总分 3.单科: ");
            scanf("%d", &sMode);
            if (sMode == 3) {
                printf("请输入科目编号(0-4): ");
                scanf("%d", &cIdx);
            }
            sortList(dummy, sMode, cIdx);
            displayAll(dummy);
            break;
        case 6: loadFromFile(dummy); break;
        case 7: saveToFile(dummy); return 0; // 保存并结束程序
        default: printf("输入无效，请重新选择。\n");
        }
    }
    return 0;
}

// 5. 核心功能实现

// 初始化哑节点
Student* initList() {
    Student* dummy = (Student*)malloc(sizeof(Student));
    if (dummy) dummy->next = NULL;
    return dummy;
}

// 添加学生（含计算总分）
void addStudent(Student* dummy) {
    Student* newNode = (Student*)malloc(sizeof(Student));
    if (!newNode) return;

    printf("输入学号 姓名: ");
    scanf("%s %s", newNode->id, newNode->name);

    newNode->total = 0;
    for (int i = 0; i < COURSE_NUM; i++) {
        printf("科目 %d 成绩: ", i + 1);
        scanf("%f", &newNode->scores[i]);
        newNode->total += newNode->scores[i];
    }

    // 头插法简单快捷
    newNode->next = dummy->next;
    dummy->next = newNode;
}

// 多功能排序（冒泡法交换数据）
void sortList(Student* dummy, int mode, int courseIndex) {
    if (!dummy->next || !dummy->next->next) return;
    int swapped;
    Student* p;
    do {
        swapped = 0;
        p = dummy->next;
        while (p->next) {
            int shouldSwap = 0;
            if (mode == SORT_BY_ID && strcmp(p->id, p->next->id) > 0) shouldSwap = 1;
            if (mode == SORT_BY_TOTAL && p->total < p->next->total) shouldSwap = 1;
            if (mode == SORT_BY_SCORE && p->scores[courseIndex] < p->next->scores[courseIndex]) shouldSwap = 1;

            if (shouldSwap) {
                // 交换数据块（除了next指针）
                Student temp = *p;
                Student* tempNext = p->next;
                Student* tempNextNext = p->next->next;

                // 这里的交换逻辑建议只交换数据域，最稳妥
                // 简便起见，这里演示交换关键值
                char tId[ID_MAX], tName[NAME_MAX];
                float tScores[COURSE_NUM], tTotal;

                strcpy(tId, p->id); strcpy(p->id, p->next->id); strcpy(p->next->id, tId);
                strcpy(tName, p->name); strcpy(p->name, p->next->name); strcpy(p->next->name, tName);
                tTotal = p->total; p->total = p->next->total; p->next->total = tTotal;
                for (int i = 0; i < COURSE_NUM; i++) {
                    float ts = p->scores[i]; p->scores[i] = p->next->scores[i]; p->next->scores[i] = ts;
                }
                swapped = 1;
            }
            p = p->next;
        }
    } while (swapped);
}

// 保存到文件
void saveToFile(Student* dummy) {
    char filename[100];
    printf("请输入保存文件名: ");
    scanf("%s", filename);
    FILE* fp = fopen(filename, "w");
    if (!fp) return;

    Student* curr = dummy->next;
    while (curr) {
        fprintf(fp, "%s %s ", curr->id, curr->name);
        for (int i = 0; i < COURSE_NUM; i++) fprintf(fp, "%.2f ", curr->scores[i]);
        fprintf(fp, "%.2f\n", curr->total);
        curr = curr->next;
    }
    fclose(fp);
    printf("已安全保存。\n");
}

// 从文件导入
void loadFromFile(Student* dummy) {
    char filename[100];
    printf("请输入导入文件名: ");
    scanf("%s", filename);
    FILE* fp = fopen(filename, "r");
    if (!fp) { printf("文件打不开！\n"); return; }

    while (!feof(fp)) {
        Student* s = (Student*)malloc(sizeof(Student));
        if (fscanf(fp, "%s %s", s->id, s->name) == 2) {
            s->total = 0;
            for (int i = 0; i < COURSE_NUM; i++) {
                fscanf(fp, "%f", &s->scores[i]);
            }
            fscanf(fp, "%f", &s->total);
            s->next = dummy->next;
            dummy->next = s;
        }
        else {
            free(s);
        }
    }
    fclose(fp);
}

// 打印列表
void displayAll(Student* dummy) {
    Student* p = dummy->next;
    printf("\n学号\t姓名\t总分\t各科成绩\n");
    while (p) {
        printf("%s\t%s\t%.2f\t", p->id, p->name, p->total);
        for (int i = 0; i < COURSE_NUM; i++) printf("%.1f ", p->scores[i]);
        printf("\n");
        p = p->next;
    }
}
// 功能：根据学号删除学生
void deleteStudent(Student* dummy) {
    char targetId[ID_MAX];
    printf("请输入要删除的学生学号: ");
    scanf("%s", targetId);

    Student* prev = dummy;
    Student* curr = dummy->next;

    while (curr != NULL) {
        if (strcmp(curr->id, targetId) == 0) {
            prev->next = curr->next; // 绕过要删除的节点
            free(curr);              // 释放内存
            printf("✅ 成功删除学号为 %s 的学生！\n", targetId);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("❌ 未找到该学号的学生，删除失败。\n");
}
// 功能：根据学号修改成绩
void modifyStudent(Student* dummy) {
    char targetId[ID_MAX];
    printf("请输入要修改成绩的学生学号: ");
    scanf("%s", targetId);

    Student* curr = dummy->next;
    while (curr != NULL) {
        if (strcmp(curr->id, targetId) == 0) {
            printf("找到学生 [%s]，请重新输入 %d 门课的成绩:\n", curr->name, COURSE_NUM);
            curr->total = 0; // 总分清零，准备重新计算

            for (int i = 0; i < COURSE_NUM; i++) {
                printf("科目 %d 新成绩: ", i + 1);
                scanf("%f", &curr->scores[i]);
                curr->total += curr->scores[i];
            }
            printf("✅ 修改成功！最新总分为: %.2f\n", curr->total);
            return;
        }
        curr = curr->next;
    }
    printf("❌ 未找到该学号的学生。\n");
}
// 功能：根据学号查找并显示学生信息
void searchStudent(Student* dummy) {
    char targetId[ID_MAX];
    printf("请输入要查询的学生学号: ");
    scanf("%s", targetId);

    Student* curr = dummy->next;
    while (curr != NULL) {
        if (strcmp(curr->id, targetId) == 0) {
            printf("\n✅ 查询结果如下：\n");
            printf("学号: %s\t姓名: %s\t总分: %.2f\n成绩: ", curr->id, curr->name, curr->total);
            for (int i = 0; i < COURSE_NUM; i++) {
                printf("%.1f ", curr->scores[i]);
            }
            printf("\n");
            return;
        }
        curr = curr->next;
    }
    printf("❌ 未查找到该学生。\n");
}
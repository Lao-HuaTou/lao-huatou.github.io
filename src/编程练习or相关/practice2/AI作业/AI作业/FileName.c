//要实现的功能：
//1.从文件导入信息
//2.手动增减学生
//3.修改学生信息
//4.按需求得到成绩表（学号，总成绩，单科成绩）
//5.保存信息至文件

  //算法逻辑说明：
  //1. 采用带哨兵节点的单向链表，简化了首节点的插入与删除操作。
  //2. 排序算法：采用链表插入排序，减少了指针交换频率，在链表结构下具有更高的执行效率。
  //3. 健壮性维护：通过清空输入缓冲区防止非法字符导致死循环。
 
#pragma warning(disable:4996)
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 20     //姓名最大长度
#define ID_MAX 20		//学号最大长度
#define COURSE_NUM 5    // 任务要求至少5门课
#define SORT_BY_ID 1	//功能
#define SORT_BY_TOTAL 2	
#define SORT_BY_SCORE 3
//学生信息结构体
typedef struct Student {
	char name[NAME_MAX];
	char id[ID_MAX];
	float scores[COURSE_NUM];//单科成绩
	float total;			//总成绩
	struct Student* next;	//学生链表
}Student;

//功能实现函数
Student* initList();				//学生链表
void addStudent(Student* dummy);	//增加学生
void sortList(Student* dummy, int mode, int courseIndex);//排序功能
void saveToFile(Student* dummy);	//保存至文件
void loadFromFile(Student* dummy);	//导入学生信息
void displayAll(Student* dummy);	//输出成绩单
void deleteStudent(Student* dummy);	//删除学生
void modifyStudent(Student* dummy);	//修改信息
void searchStudent(Student* dummy);	//查找学生

//主函数
int main() {
	SetConsoleOutputCP(65001);
	Student* dummy = initList(); //哨兵节点，方便修改
	int choice;
	while (1) {
		printf("\n============学生成绩管理系统============\n");
		printf("1.增加/录入学生\n");
		printf("2.删除学生\n");
		printf("3.修改学生成绩\n");
		printf("4.查询学生信息\n");
		printf("5.排序并展示成绩表\n");
		printf("6.从文件导入学生信息 \n");
		printf("7.保存到文件并退出系统 \n");
		printf("======================================== \n");
		printf("请选择功能: ");
		if (scanf("%d", &choice) != 1) {
			printf("输入非法，请输入数字！n");
			while (getchar() != '\n'); // 清空缓冲区，防止死循环
			continue;
		}
		int Mode;		//排序时选择的排序方式
		int Id;			//选择单科成绩时对应的科目编号
		switch (choice) {
		case 1: addStudent(dummy); break;
		case 2: deleteStudent(dummy); break;
		case 3: modifyStudent(dummy); break;
		case 4: searchStudent(dummy); break;
		case 5:
			Mode, Id = 0;
			printf("排序方式: 1.学号 2.总分 3.单科: ");
			scanf("%d", &Mode);
			if (Mode == 3) {
				printf("请输入科目编号(0-4): ");
				scanf("%d", &Id);
				if (Id < 0 || Id >= COURSE_NUM) {
					printf("错误：科目编号应在 0-%d 之间！\n", COURSE_NUM - 1);
					break;
				}
			}
			sortList(dummy, Mode, Id);
			if (!dummy->next)break;
			displayAll(dummy);
			break;
		case 6: loadFromFile(dummy); break;
		case 7: saveToFile(dummy); return 0; // 保存并结束程序
		default: printf("输入无效，请重新选择\n");
		}
	}
	return 0;
}

//函数功能的具体实现

//1.初始化哨兵节点
Student* initList() {
	Student* dummy = (Student*)malloc(sizeof(Student));
	if (dummy) dummy->next = NULL;
	return dummy;
}

//添加学生
void addStudent(Student* dummy) {
	Student* newStu = (Student*)malloc(sizeof(Student));
	printf("请输入学号与姓名\n");
	scanf("%s %s", newStu->id, newStu->name);

	// 健壮性：学号查重
	Student* temp = dummy->next;
	while (temp) {
		if (strcmp(temp->id, newStu->id) == 0) {
			printf("错误：学号已存在！\n");
			free(newStu); return;
		}
		temp = temp->next;
	}

	newStu->total = 0;
	for (int i = 0; i < COURSE_NUM; i++) {
		printf("科目 %d 成绩: ", i + 1);
		scanf("%f", &newStu->scores[i]);
		newStu->total += newStu->scores[i];//自动计算总成绩
	}

	// 有序维护：按学号升序寻找插入点
	Student* prev = dummy;
	while (prev->next != NULL && strcmp(newStu->id, prev->next->id) > 0) {//插入节点
		prev = prev->next;
	}
	newStu->next = prev->next;
	prev->next = newStu;
	printf("添加成功并已自动按学号归位。\n");
}

//排序功能：插入排序
void sortList(Student* dummy, int mode, int couseID) {
	// 1. 如果链表为空或只有一个有效节点，无需排序
	if (dummy->next == NULL || dummy->next->next == NULL) {
		if (dummy->next == NULL) {
			printf("目前系统中未存入学生，请导入学生信息后重试 \n");
		}
		return;
	}

	// 2. 将原链表拆开：lastSorted 是已排序部分的最后一个节点，curr 是待排序节点
	Student* head = dummy->next; // 记录第一个节点
	Student* curr = head->next;  // 从第二个节点开始处理
	head->next = NULL;           // 暂时断开，先把第一个节点当成已排序的

	while (curr != NULL) {
		Student* nextTemp = curr->next; // 暂存下一个待排序节点，防止断链

		// 3. 在已排序部分（从 dummy 开始）寻找插入位置
		Student* prev = dummy;
		while (prev->next != NULL) {
			int shouldStop = 0;
			// 比较逻辑：根据 mode 决定插入位置
			//依据三种功能，决定停止位置
			if (mode == SORT_BY_ID && strcmp(curr->id, prev->next->id) < 0) shouldStop = 1;
			if (mode == SORT_BY_TOTAL && curr->total > prev->next->total) shouldStop = 1; 
			if (mode == SORT_BY_SCORE && curr->scores[couseID] > prev->next->scores[couseID]) shouldStop = 1; 

			if (shouldStop) break; // 找坑位
			prev = prev->next;
		}

		// 4. 插入新位置
		curr->next = prev->next;
		prev->next = curr;

		curr = nextTemp;
	}
	printf("排序完成。\n");
}

//保存至文件
void saveToFile(Student* dummy) {
	char filename[200];
	printf("请输入要保存到的文件名：");
	scanf("%s", filename);
	FILE* fp = fopen(filename, "w");
	if (!fp) {
		perror("文件打开失败"); //若打开失败，提示错误原因
		return;
	}
	Student* cur = dummy->next;
	while (cur) {
		fprintf(fp, "%s %s ", cur->id, cur->name);
		for (int i = 0; i < COURSE_NUM; i++) {
			fprintf(fp, "%.2f ", cur->scores[i]);
		}
		fprintf(fp, "%.2f\n", cur->total);
		cur = cur->next;
	}
	fclose(fp);
	printf("文件保存成功");
}

//从文件导入
void loadFromFile(Student* dummy) {
	char filename[200];
	printf("请输入导入文件名: ");
	if (scanf("%s", filename) != 1) return;

	FILE* fp = fopen(filename, "r");
	if (!fp) {
		perror("无法打开文件"); // 显示具体的系统错误原因
		printf("提示：请检查文件名是否正确，或文件是否被其他程序占用。\n");
		return;
	}

	int successCount = 0;//成功导入学生数量
	int duplicateCount = 0;//学号重复的数量

	while (1) {
		Student* newStu = (Student*)malloc(sizeof(Student));
		if (!newStu) break;

		// 尝试读取学号和姓名
		if (fscanf(fp, "%s %s", newStu->id, newStu->name) != 2) {
			free(newStu);
			break; // 读取结束或格式不匹配
		}

		newStu->total = 0;
		for (int i = 0; i < COURSE_NUM; i++) {
			if (fscanf(fp, "%f", &(newStu->scores[i])) == 1) {//读取健壮性测试
				newStu->total += newStu->scores[i];
			}
		}
		// 读取文件中的总分记录
		float fileTotal;
		fscanf(fp, "%f", &fileTotal);

		// 4. 学号唯一性校验
		int isDuplicate = 0;
		Student* check = dummy->next;
		while (check != NULL) {
			if (strcmp(check->id, newStu->id) == 0) {
				isDuplicate = 1;//存在学号重复，特别处理
				break;
			}
			check = check->next;
		}

		if (isDuplicate) {
			duplicateCount++;
			free(newStu); // 学号重复，释放内存
		}
		else {
			Student* prev = dummy;
			while (prev->next != NULL && strcmp(newStu->id, prev->next->id) > 0) {//插入节点
				prev = prev->next;
			}
			newStu->next = prev->next;
			prev->next = newStu;
			successCount++;
		}
	}

	fclose(fp); // 确保文件关闭

	printf("成功导入 %d 名学生\n", successCount);
	if (duplicateCount > 0) {
		printf("跳过重复学号 %d 个\n", duplicateCount);
	}
	printf("----------------\n");
}


//输出成绩单
void displayAll(Student* dummy) {
	Student* cur = dummy->next;
	printf("\n姓名\t学号\t总成绩 \t各科成绩\n");
	while (cur) {
		printf("%s\t%s\t", cur->name, cur->id);
		printf("%.2f\t", cur->total);
		for (int i = 0; i < COURSE_NUM; i++)printf("%.2f ", cur->scores[i]);
		printf("\n");
		cur = cur->next;
	}
}

//删除学生
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
			printf("成功删除学号为 %s 的学生！\n", targetId);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("未找到该学号的学生，请重试。\n");
}

//修改学生信息
void modifyStudent(Student* dummy) {
	char targetId[ID_MAX];
	printf("请输入要修改成绩的学生学号: ");
	scanf("%s", targetId);

	Student* curr = dummy->next;
	while (curr != NULL) {
		if (strcmp(curr->id, targetId) == 0) {
			printf("找到学生 [%s]，1.修改所有成绩  2.修改单科成绩\n", curr->name);
			int choice2;
			if (scanf("%d", &choice2) != 1||choice2>2||choice2<1) { 
				printf("输入错误，请重新尝试\n");
				while (getchar() != '\n'); 
				return; 
			}
			if (choice2 == 2) {//修改单科成绩
				int idx;
				printf("请输入科目编号(1-5): ");
				scanf("%d", &idx);
				while (idx<1 || idx>COURSE_NUM) {
					printf("科目编号错误，请输入1-5之间的数字 ");
					scanf("%d", &idx);
				}
				if (idx >= 1 && idx <= COURSE_NUM) {
					printf("原成绩 %.2f, 请输入新成绩: ", curr->scores[idx - 1]);
					scanf("%f", &curr->scores[idx - 1]);
					// 重新计算总分
					curr->total = 0;
					for (int i = 0; i < COURSE_NUM; i++) curr->total += curr->scores[i];
				}
				
			}

			else {//全部修改
				curr->total = 0; // 总分清零，准备重新计算

				for (int i = 0; i < COURSE_NUM; i++) {
					printf("科目 %d 新成绩: ", i + 1);
					scanf("%f", &curr->scores[i]);
					curr->total += curr->scores[i];
				}
				printf("修改成功！最新总分为: %.2f\n", curr->total);
				return;
			}
		}
		curr = curr->next;
	}
	printf("未找到该学号的学生，请重试。\n");
}

//查询学生信息
void searchStudent(Student* dummy) {
	printf("选择查询方式: 1.姓名  2.学号 \n");
	int way; scanf("%d", &way);
	while (way < 1 || way>2) {
		printf("方式错误，请输入1或2\n");
		scanf("%d", &way);
	}
	if (way == 2) {//按学号查询
		char targetId[ID_MAX];
		printf("请输入要查询的学生学号: ");
		scanf("%s", targetId);

		Student* curr = dummy->next;
		while (curr != NULL) {
			if (strcmp(curr->id, targetId) == 0) {
				printf("\n查询结果如下：\n");
				printf("学号: %s\t姓名: %s\t总分: %.2f\n成绩: ", curr->id, curr->name, curr->total);
				for (int i = 0; i < COURSE_NUM; i++) {
					printf("%.2f ", curr->scores[i]);
				}
				printf("\n");
				return;
			}
			curr = curr->next;
		}
		printf("未查找到该学生，请重试。\n");
	}
	else {//按姓名查询
		char targetName[ID_MAX];
		printf("请输入要查询的学生姓名: ");
		scanf("%s", targetName);

		Student* curr = dummy->next;
		while (curr != NULL) {
			if (strcmp(curr->name, targetName) == 0) {
				printf("\n查询结果如下：\n");
				printf("学号: %s\t姓名: %s\t总分: %.2f\n成绩: ", curr->id, curr->name, curr->total);
				for (int i = 0; i < COURSE_NUM; i++) {
					printf("%.2f ", curr->scores[i]);
				}
				printf("\n");
				return;
			}
			curr = curr->next;
		}
		printf("未查找到该学生，请重试。\n");
	}
}




//#include <stdio.h>
//#include <malloc.h>
//struct cell {//单链表结点结构体定义
//	int x;
//	struct cell* next;
//};
//struct cell* build(void) {//新建单链表，并将建好的单链表首结点地址返回
//	struct cell* head, * tmp, * p;
//	head = tmp = p = NULL;
//	int n; scanf("%d", &n);
//	if (n == 0) return NULL;
//	while (n != 0)
//	{
//		p = (struct cell*)malloc(sizeof(struct cell));
//		p->x = n;
//		p->next = NULL;
//		if (head == NULL) { head = p; tmp = p; }
//		else {
//
//			tmp->next = p;
//			tmp = p;
//		}
//		scanf("%d", &n);
//	}
//	return head;//返回单链表头
//}
//
//void print(struct cell* head) {//打印整个单链表,head是单链表首结点指针
//	while (head != NULL)
//	{
//		printf("%d", head->x);
//		head = head->next;
//		if (head != NULL) printf(" ");
//	}
//}
//void release(struct cell* head) {//释放单链表空间,head是单链表首结点指针
//	struct cell* tem = head;
//	while (head != NULL)
//	{
//		tem = head;
//		head = head->next;
//		free(tem);
//	}
//}
//int main(void) {
//	struct cell* head, * half;
//	head = build();
//
//	if (half != NULL)
//		print(half);
//	else
//		printf("NULL");
//	release(head);
//}
//#include<stdio.h>
//#include<malloc.h>
//struct farlei_item{
// int numerator,denominator;// 分子、分母
// struct farlei_item* next;// 连接部分
//};
//typedef struct farlei_item* farleipointer;
//int gcd(int x, int y) {
//	if (y == 0) return x;
//	return gcd(y, x % y);
//}
///*构造法雷序列,并返回序列头指针*/
//farleipointer farlei(int n) {
//	int i, j;
//	farleipointer fn, r, r0, p;//head zuo you wei
//	fn =   r = r0 = p  = NULL;
//	if (n  < 1)return NULL;//如果n<=0,则没有法雷序列
//	fn  = (farleipointer)malloc(sizeof(struct farlei_item));  //构造0/1
//	fn->numerator  = 0;
//	fn->denominator  = 1;
//	p  = (farleipointer)malloc(sizeof(struct farlei_item));
//	p->numerator = 1;
//	p->denominator = 1;
//	fn->next = p;
//	p->next = NULL;
//	for (i = 2; i <= n; i++)
//	{
//		for (j = 1; j < i; j++)
//		{
//			if (gcd(i, j) == 1) {
//				r0 = fn; r = r0->next;
//				while (r!=NULL&&j * r->denominator > i * r->numerator) {
//					r0 = r0->next; r = r->next;
//				}
//				if (r!=NULL&&j * r->denominator != i * r->numerator) {
//					p = (farleipointer)malloc(sizeof(struct farlei_item));
//					p->numerator = j; p->denominator = i;
//					p->next = r;
//					r0->next = p;
//				}
//			}
//		}
//	}
//	return fn;
//}
//void print(farleipointer fn) {
//	farleipointer tem = fn;
//	while (tem != NULL)
//	{
//		printf("%d/%d", tem->numerator, tem->denominator);
//		tem = tem->next;
//		if (tem != NULL) printf(" ");
//	}
//}
//void release(farleipointer head) {
//	farleipointer tem=head;
//	while (head != NULL)
//	{
//		head = head->next;
//		free(tem);
//		tem = head;
//	}
//}
//int main(void) {
//	int n;
//	farleipointer fn;
//	scanf("%d", &n);
//	fn = farlei(n);
//	if (fn != NULL) 
//		print(fn);	
//	else printf("NULL");
//	release(fn);
//	return 0;
//}
#include<stdio.h>
#include<malloc.h>
struct cell {//单链表结点结构体定义
 int x;
 struct cell* next;
};
struct cell* build(void) {//新建单链表，并将建好的单链表首结点地址返回
	struct cell* head, * tmp, * p;
	head  = tmp = p = NULL;
	int n;
	scanf("%d", &n);
	if (n == 0) return NULL;
	while (n != 0)
	{
		if (head == NULL) {
			head= (struct cell*)malloc(sizeof(struct cell));
			head->x = n; head->next = NULL;
			p = head;
		}
		else {
			tmp = (struct cell*)malloc(sizeof(struct cell));
			tmp->x = n;
			tmp->next = NULL;
			p->next = tmp;
			p = p->next;
			
		}
		scanf("%d", &n);
	}
	return head;//返回单链表头
}
struct cell * sort(struct cell* head) {//递增排序链表，head是单链表首结点指针
	struct cell* p, * p0, * r, * r0, * q;
	p = p0 = r = r0 = q = NULL;
	p  = head;
	int flag = 1;
	if (head == NULL || head->next == NULL) return head;
	while (flag)
	{
		flag = 0;
		p = head; p0 = NULL;
		while (p != NULL && p->next != NULL)
		{
			q = p->next;
			if (p->x > q->x) {
				// 需要交换p和q
				flag = 1;

				// 交换两个节点
				if (p0 == NULL) {
					// p是头节点
					p->next = q->next;
					q->next = p;
					head = q;
					p0 = q;  // 更新前驱
				}
				else {
					// p不是头节点
					p->next = q->next;
					q->next = p;
					p0->next = q;
					p0 = q;  // 更新前驱
				}
			}
			else {
				// 不需要交换，直接后移
				p0 = p;
				p = p->next;
			}
		}
	}
	return head;
}
//struct cell* back(struct cell* head, int k) {//求链表倒数第k个结点，head是单链表首结点指针
//	struct cell* slow=head, * fast=head;
//	for (int i = 0; i < k - 1; i++)
//	{
//		if (fast->next == NULL) return NULL;
//		fast = fast->next;
//	}
//	while (fast->next != NULL)
//	{
//		fast = fast->next;
//		slow = slow->next;
//
//	}
//	return slow;
//}
void print(struct cell* fn) {
	struct cell* tem = fn;
	while (tem != NULL)
	{
		printf("%d/%d",tem->x);
		tem = tem->next;
		if (tem != NULL) printf(" ");
	}
}
void release(struct cell* head) {//释放单链表空间,head是单链表首结点指针
	struct cell* tem = head;
	while (head != NULL)
	{
		head = head->next;
		free(tem);
		tem = head;
	}
}
int main(void) {
	struct cell* head;
	head = build();
	if (head != NULL) {
		head = sort(head);
		print(head);
	}
else
printf("NULL");
release(head);
return 0;
}
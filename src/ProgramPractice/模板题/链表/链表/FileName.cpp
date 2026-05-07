#include <stdio.h>
#include <malloc.h>
struct cell {//单链表结点结构体定义
	int x;
	struct cell* next;
};
struct cell* build(void) {//新建单链表，并将建好的单链表首结点地址返回
	struct cell* head, * tmp, * p;
	head = tmp = p = NULL;
	int n; scanf("%d", &n);
	if (n == 0) return NULL;
	while (n != 0)
	{
		p = (struct cell*)malloc(sizeof(struct cell));
		p->x = n;
		p->next = NULL;
		if (head == NULL) { head = p; tmp = p; }
		else {

			tmp->next = p;
			tmp = p;
		}
		scanf("%d", &n);
	}
	return head;//返回单链表头
}
struct cell* mid(struct cell* head) {//寻找链表中间位置结点地址并返回，head是单链表首结点指针
	struct cell* slow=head, * fast=head;
	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		if (fast != NULL) {
			slow = slow->next;
		}
	}
	return slow;
}
//struct cell* del2one(struct cell* head) {//删除重复结点只保留一个，head是单链表首结点指针
//	if (head == NULL || head->next == NULL) return head;
//	struct cell* p, * pre, * q;
//	p = head;
//	while (p != NULL)
//	{
//		pre = p;
//		q = p->next;
//		while (q != NULL)
//		{
//			if (q->x == p->x)
//			{
//				pre->next = q->next;
//				free(q);
//				q = pre->next;
//			}
//			else {
//				q = q->next; pre = pre->next;
//			}
//		}
//		p = p->next;
//	}
//	return head;//返回删除重复结点的单链表头
//}
void print(struct cell* head) {//打印整个单链表,head是单链表首结点指针
	while (head != NULL)
	{
		printf("%d", head->x);
		head = head->next;
		if (head != NULL) printf(" ");
	}
}
void release(struct cell* head) {//释放单链表空间,head是单链表首结点指针
	struct cell* tem = head;
	while (head != NULL)
	{
		tem = head;
		head = head->next;
		free(tem);
	}
}
int main(void) {
	struct cell* head,*half;
	head = build();
	half = mid(head);
	if (half != NULL)
		print(half);
	else
		printf("NULL");
	release(head);
}
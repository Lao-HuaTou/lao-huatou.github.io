#include<stdio.h>
#include<malloc.h>
struct cell { //单链表结点结构体定义
	int x;
	struct cell* next;
};
struct cell* build(void) { //新建单链表，并将建好的单链表首结点地址返回
	struct cell* head, * tmp, * p;
	head = tmp = p = NULL;
	int n;
	//*请在以下位置补充完整，实现函数build
	scanf("%d", &n);
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
void print(struct cell* head) {//打印整个单链表,head是指向单链表首结点的指针

	while (head != NULL) {
		printf("%d", head->x);
		head = head->next;
		if (head != NULL) printf(" ");
	}

}
void release(struct cell* head) {//释放单链表空间,head是指向单链表首结点的指针
	struct cell* tem = head;
	while (head != NULL)
	{
		tem = head;
		head = head->next;
		free(tem);
	}
}
int main(void) {
	struct cell* head;
	head = build();
	if (head != NULL)
		print(head);
	else
		printf("NULL");
	release(head);
}
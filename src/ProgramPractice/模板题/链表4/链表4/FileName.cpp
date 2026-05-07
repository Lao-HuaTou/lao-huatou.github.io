#include<stdio.h>
#include<stdlib.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
// LeetCode 206 - Reverse Linked List
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;

    while (curr != NULL) {
        struct ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }

    return prev;
}
// LeetCode 21 - Merge Two Sorted Lists
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        }
        else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = (l1 != NULL) ? l1 : l2;
    return dummy.next;
}
//
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* slow=head, * fast = head;
    while (fast->next!=NULL&&fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
// LeetCode 237 - Delete Node in a Linked List
void deleteNode(struct ListNode* node) {
    struct ListNode* nexttem = node->next;
    node->val = node->next->val;
    node->next = node->next->next;
    free(nexttem);
}
// LeetCode 141 - Linked List Cycle
bool hasCycle(struct ListNode* head) {
    struct ListNode* slow=head, * fast=head->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL)return false;
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode* fast = &dummy;
    struct ListNode* slow = &dummy;

    // fast先走n步（不是n+1！）
    for (int i = 0; i < n; i++) {
        if (fast->next == NULL) return head; // n可能大于链表长度
        fast = fast->next;
    }

    // slow和fast同时走，直到fast到达最后一个节点
    while (fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    // 此时slow是要删除节点的前驱
    struct ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    free(toDelete);

    return dummy.next;
}
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL || head->next == NULL) return head;

    // 计算链表长度并找到尾节点
    int length = 1;
    struct ListNode* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    // 形成环
    tail->next = head;

    // 计算实际旋转步数
    k = k % length;

    // 找到新的尾节点（从原tail开始走 length-k 步）
    struct ListNode* newTail = tail;
    for (int i = 0; i < length - k; i++) {
        newTail = newTail->next;
    }

    // 断开环
    struct ListNode* newHead = newTail->next;
    newTail->next = NULL;

    return newHead;
}
//insert
struct ListNode* insert(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* last, * cur, dummy;
    dummy.next = head;
    last = head; cur = last->next;
    while (cur != NULL) {
        if (last->val <= cur->val) {
            last = last->next;
        }
        else {
            struct ListNode* tem=&dummy;
            while (tem->next->val < cur->val)tem = tem->next;
            last->next = cur->next;
            cur->next = tem->next;
            tem->next = cur;

        }
        cur = last->next;
    }
    return dummy.next;
}
//bubble
struct ListNode* bubble(struct ListNode* head) {
    if (head == NULL || head->next == NULL)return head;
    struct ListNode* p0, * p, * p1;
    p0 = p = p1 = NULL;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        p0 = NULL;
        p = head; p1 = head->next;
        while (p!=NULL&&p1 != NULL) {
            if (p->val > p1->val) {
                flag = 1;
                if (p0 == NULL) {
                    p->next = p1->next;
                    p1->next = p;
                    head = p1;
                }
                else {
                    p->next = p1->next;
                    p1->next = p;
                    p0->next = p1;
                }
                p = p1->next;
                p1 = p->next;
            }
            else {
                p0 = p;
                p = p->next;
                p1 = p1->next;
                
            }
        }
    }
    return head;
}

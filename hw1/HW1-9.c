#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//链表声明
struct ListNode {
    int val;
    struct ListNode* next;
};
//建表
struct ListNode* CreateRootList(int listsize) {
    int val;
    if (listsize == 0) return NULL; 
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    scanf("%d", &val);
    head -> next = head;
    head -> val = val;
    listsize --;
    struct ListNode* rear = head;
    for (int i = 0; i < listsize; i ++) {
        struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        scanf("%d", & val);
        newnode -> val = val;
        newnode -> next = rear -> next;
        rear -> next = newnode;
        rear = rear -> next;
    }
    return head;
}
//题目的算法解答：删除循环链表特定元素
struct ListNode* DeleteCertainNode(struct ListNode* s) {
    struct ListNode* p = s;
    while (p -> next && p -> next != s) {
        p = p -> next;
    }
    struct ListNode* cur = s;
    p -> next = s -> next;
    free(s);
    return p;
}
//输出链表
void RootListOutput(struct ListNode* head) {
    struct ListNode* p = head;
    if (p == NULL) {
        printf("empty list\n");
        return ;
    }
    do {
        printf("%d ", p -> val);
        p = p -> next;
    } while (p != head);
    printf("\n");
    return ;
}
int main() {
    int listsize;
    scanf("%d", &listsize);
    struct ListNode* head = CreateRootList(listsize);
    //以删除第二个初始化的结点为例
    struct ListNode* del = head -> next;
    printf("before delete function: ");
    RootListOutput(head);
    DeleteCertainNode(del);
    printf("after delete function: ");
    RootListOutput(head);  
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* CreateList() {
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head -> next = NULL;
    return head;
}
struct ListNode* CreateNode(struct ListNode* head, int listsize) {
    struct ListNode* rear = head;
    int val;
    for (int i = 0; i < listsize; i ++) {
        struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        scanf("%d", & val);
        newnode -> val = val;
        newnode -> next = NULL;
        rear -> next = newnode;
        rear = rear -> next;
    }
    return head;
}
struct ListNode* ReverseList(struct ListNode* head) {
    struct ListNode* cur, * pre, * nxt;
    pre = NULL;
    cur = head;
    if (!cur || ! cur -> next) return head;
    while (cur) {
        nxt = cur -> next;
        cur -> next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}
void ListOutput(struct ListNode* head) {
    while (head) {
        printf("%d ", head -> val);
        head = head -> next;
    }
    printf("\n");
    return ;
}
int main() {
    struct ListNode* dummyhead = CreateList();
    int listsize;
    scanf("%d", &listsize);
    dummyhead = CreateNode(dummyhead, listsize);
    printf("before reverse function: ");
    ListOutput(dummyhead -> next);
    dummyhead -> next = ReverseList(dummyhead -> next);
    printf("after reverse function: ");
    ListOutput(dummyhead -> next);
    return 0;
}
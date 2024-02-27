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
int ListCompare(struct ListNode* list1, struct ListNode* list2) {
    int flag = 1;
    while (list1 && list2) {
        if (list1 -> val == list2 -> val) {
            flag = 0;
        } else if (list1 -> val < list2 -> val && flag == 0) {
            flag = -1;
        } else if (list1 -> val  >= list2 -> val) {
            flag = 1;
        }
        list1 = list1 -> next;
        list2 = list2 -> next;
    }
    if (list1 || list2) {
        if (flag == 0) flag = 1;
    }
    return flag;
}
int main() {
    struct ListNode* dummyhead1 = CreateList();
    struct ListNode* dummyhead2 = CreateList();
    int listsize1, listsize2;
    scanf("%d %d", &listsize1, & listsize2);
    dummyhead1 = CreateNode(dummyhead1, listsize1);
    dummyhead2 = CreateNode(dummyhead2, listsize2);
    printf("compare result: %d", ListCompare(dummyhead1 -> next, dummyhead2 -> next));
    return 0;
}
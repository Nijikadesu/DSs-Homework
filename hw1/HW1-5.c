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
void ListOutput(struct ListNode* head) {
    while (head) {
        printf("%d ", head -> val);
        head = head -> next;
    }
    printf("\n");
    return ;
}
struct ListNode* DeleteRegularNode(struct ListNode* head, int min, int max) {
    if (head -> next == NULL) return head;
    if (max <= min) return head;
    struct ListNode* p1 = head;
    struct ListNode* p2 = head;
    while (p2 -> next && p2 -> next -> val <= min) {
        p2 = p2 -> next;
    }
    p1 = p2;
    while (p2 && p2 -> val < max) {
        p2 = p2 -> next;
    }
    struct ListNode* p = p1 -> next;
    p1 -> next = p2;
    while (p && p -> next != p2) {
        struct ListNode* s = p;
        p = p -> next;
        free(s);
    }
    return head;
}
int main() {
    int min, max;
    scanf("%d %d", &min, &max);
    struct ListNode* dummyhead = CreateList();
    int listsize;
    scanf("%d", &listsize);
    dummyhead = CreateNode(dummyhead, listsize);
    printf("before delete function: ");
    ListOutput(dummyhead -> next);
    dummyhead = DeleteRegularNode(dummyhead, min, max);
    printf("after delete function: ");
    ListOutput(dummyhead -> next);
    return 0;
}
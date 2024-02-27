#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node {
    int data;
    struct node* next;
} linklist;
linklist* CreateList() {
    linklist* head = (linklist*)malloc(sizeof(linklist));
    head -> next = NULL;
    return head;
}
linklist* CreateNode(linklist* head, int listsize) {
    linklist* rear = head;
    int data;
    for (int i = 0; i < listsize; i ++) {
        linklist* newnode = (linklist*)malloc(sizeof(linklist));
        scanf("%d", & data);
        newnode -> data = data;
        newnode -> next = NULL;
        rear -> next = newnode;
        rear = rear -> next;
    }
    return head;
}
int deletenode(linklist* head, int i) {
    linklist* p, * q;
    int j;
    q = head;
    j = 0;
    while ((q != NULL) && (j < i - 1)) {
        q = q -> next;
        j ++;
    }
    if (q == NULL) 
        return (0);
    p = q -> next;
    q -> next = p -> next;
    free(p);
    return (1);
}
void ListOutput(linklist* head) {
    while (head) {
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n");
    return ;
}
int main() { 
    linklist* dummyhead = CreateList();
    int listsize, num;
    scanf("%d", &listsize);
    dummyhead = CreateNode(dummyhead, listsize);
    printf("delete which one: ");
    scanf("%d", &num);
    printf("before delete function: ");
    ListOutput(dummyhead -> next);
    printf("%d", deletenode(dummyhead, num));
    printf("after delete function: ");
    ListOutput(dummyhead -> next);
    return 0;
}
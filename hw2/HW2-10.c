#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct Node {
    int val;
    struct Node* next;
};
typedef struct Node QueueNode;
typedef struct {
    QueueNode* rear;
    int size;
} MyQueue;
MyQueue* MyQueue_Create() {
    MyQueue* Q = (MyQueue*)malloc(sizeof(MyQueue));
    Q -> rear == NULL;
    Q -> size = 0;
    return Q;
}
//向循环队列中插入一个元素值为x的结点
void MyQueue_Insert(MyQueue* Q, int val) {
    QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
    newnode -> val = val;
    if (Q -> size == 0) {
        Q -> rear = newnode;
        Q -> rear -> next = Q -> rear;
    } else {
        newnode -> next = Q -> rear -> next;
        Q -> rear -> next = newnode;
        Q -> rear = newnode;
    }
    Q -> size ++;
    return ;
}
//删除结点（不保留值，不回收空间）
void MyQueue_Delete(MyQueue* Q) {
    if (Q -> size == 0) {
        printf("MyQfueue is empty\n");
        return ;
    }
    if (Q -> size == 1) {
        Q -> rear = NULL;
        return ;
    }
    QueueNode* front = Q -> rear -> next;
    Q -> rear -> next = front -> next;
    Q -> size --;
    return ;
}
//打印循环队列
void MyQueue_Print(MyQueue* Q) {
    if (Q -> rear == NULL) {
        printf("Myqueue is empty\n");
        return ;
    }
    QueueNode* p = Q -> rear -> next;
    while (p != Q -> rear) {
        printf("%d -> ", p -> val);
        p = p -> next;
    }
    printf("%d\n", p -> val);
    return ;
}
int main() {
    MyQueue* Q = MyQueue_Create();
    int m;
    // printf("%d", Q -> rear == NULL);
    printf("type the num of the queue: ");
    scanf("%d", &m);
    printf("Initialize: ");
    for (int i = 0; i < m; i ++) {
        int val;
        scanf("%d", &val);
        MyQueue_Insert(Q, val);
    }
    printf("print circularqueue from front to rear: ");
    MyQueue_Print(Q);
    printf("delete funciton!\n");
    MyQueue_Delete(Q);
    MyQueue_Print(Q);
    return 0;
}
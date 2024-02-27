#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 10 //循环队列最大容量
typedef struct {
    int rear, quelen;
    int vals[MaxSize];
} MyCircularQueue; //队列声明
MyCircularQueue* MyCircularQueue_Create() { //创建队列
    MyCircularQueue* Q = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    Q -> rear = 0;
    Q -> quelen = 0;
    return Q;
}
bool MyCircularQueue_Empty(MyCircularQueue* Q) { //循环队列上溢与下溢条件
    return Q -> quelen == 0;
}
bool MyCircularQueue_Full(MyCircularQueue* Q) {
    return Q -> quelen == MaxSize - 1;
}
void MyCircularQueue_Push(MyCircularQueue* Q, int val) { //入队列算法
    if (MyCircularQueue_Full(Q)) {
        printf("the circularqueue is full\n");
        return ;
    }
    Q -> vals[Q -> rear] = val;
    Q -> rear = (Q -> rear + 1) % MaxSize;
    Q -> quelen ++;
    return ;
}
int MyCircularQueue_Pop(MyCircularQueue* Q) { //出队列算法
    if (MyCircularQueue_Empty(Q)) {
        printf("the circularqueue is empty\n");
        return -1;
    }
    int front = (Q -> rear - Q -> quelen + MaxSize) % MaxSize;
    int frontval = Q -> vals[front];
    front = (front + 1) % MaxSize;
    Q -> quelen --;
    return frontval;
}
void MyCircularQueue_Print(MyCircularQueue* Q) { //从头到尾打印队列
    if (Q -> quelen == 0) {
        printf("the circular queue is empty\n");
        return ;
    }
    int i = (Q -> rear - Q -> quelen + MaxSize) % MaxSize;
    while (i != (Q -> rear + MaxSize - 1) % MaxSize) {
        printf("%d -> ", Q -> vals[i]);
        i = (i + 1) % MaxSize;
    }
    printf("%d\n", Q -> vals[i]);
    return ;
}
int main() {
    MyCircularQueue* Q = MyCircularQueue_Create();
    int m;
    printf("type the num of the queue: ");
    scanf("%d", &m);
    printf("Initialize: ");
    for (int i = 0; i < m; i ++) {
        int val;
        scanf("%d", &val);
        MyCircularQueue_Push(Q, val);
    }
    printf("print circularqueue from front to rear: ");
    MyCircularQueue_Print(Q);
    printf("delete funciton!\n");
    MyCircularQueue_Pop(Q);
    MyCircularQueue_Print(Q);
    return 0;
}
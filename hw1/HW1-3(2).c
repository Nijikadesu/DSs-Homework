#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
struct NumList {
    int listsize;
    int list[MaxSize];
};
struct NumList* InitList() {
    struct NumList* ptrl = (struct NumList*)malloc(sizeof(struct NumList));
    ptrl -> listsize = 0;
    ptrl -> list[0] = 0;
    return ptrl;
}
struct NumList* ValInsert(struct NumList* ptrl, int size) {
    int val;
    for (int i = 0; i < size; i ++) {
        scanf("%d", &val);
        ptrl -> list[0] ++;
        ptrl -> list[ptrl -> list[0]] = val;
        ptrl -> listsize ++;
    }
    return ptrl;
}
struct NumList* ReverseList(struct NumList* ptrl) {
    int head, rear;
    head = 1;
    rear = ptrl -> list[0];
    while (rear - head >= 1) {
        int t = ptrl -> list[head];
        ptrl -> list[head] = ptrl -> list[rear];
        ptrl -> list[rear] = t;
        head ++;
        rear --;
    }
    return ptrl;
}
void ListOutput(struct NumList* ptrl) {
    for (int i = 1; i <= ptrl -> listsize; i ++) {
        printf("%d ", ptrl -> list[i]);
    }
    printf("\n");
    return ;
}
int main() {
    struct NumList* ptrl = InitList();
    int size, val;
    scanf("%d", &size);
    ptrl = ValInsert(ptrl, size);
    printf("before reverse function: ");
    ListOutput(ptrl);
    ptrl = ReverseList(ptrl);
    printf("after reversse function: ");
    ListOutput(ptrl);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct StackNode {
    int val;
    struct StackNode* next;
}; 
typedef struct StackNode Stack; //链结声明
typedef struct {
    Stack* top;
    int size;
} MyStack; //堆栈声明
MyStack* MyStack_Create() { //创建堆栈
    MyStack* S = (MyStack*)malloc(sizeof(MyStack));
    S -> top = NULL;
    S -> size = 0;
    return S;
}
void MyStack_Push(MyStack* S, int val) { //元素压栈
    Stack* newnode = (Stack*)malloc(sizeof(Stack));
    newnode -> val = val;
    newnode -> next = S -> top;
    S -> top = newnode;
    S -> size ++;
    return ;
}
bool MyStack_Empty(MyStack* S) { //堆栈判空
    return S -> top == NULL;
}
int MyStack_Pop(MyStack* S) { //弹出栈顶元素
    if (MyStack_Empty(S)) return -1;
    int topval = S -> top -> val;
    Stack* p = S -> top;
    S -> top = p -> next;
    free(p);
    S -> size --;
    return topval;
}
void MyStack_Print(MyStack* S) { //自顶向下打印堆栈
    Stack* ptrS = S -> top;
    while (ptrS) {
        printf("%d ", ptrS -> val);
        ptrS = ptrS -> next;
    }
    printf("\n");
    return ;
}
int main() {
    MyStack* S = MyStack_Create();
    int nums;
    printf("type the num of the stack: ");
    scanf("%d", &nums);
    printf("Initialize: ");
    for (int i = 0; i < nums; i ++) {
        int val;
        scanf("%d", &val);
        MyStack_Push(S, val);
    }
    printf("print stack from top to bottom: ");
    MyStack_Print(S);
    //栈S初始化完成
    MyStack* TranSit = MyStack_Create();
    int m;
    printf("val to be delete: ");
    scanf("%d", &m);
    while (! MyStack_Empty(S)) {
        int val = MyStack_Pop(S);
        if (val != m) {
            MyStack_Push(TranSit, val);
        }
    }
    //将栈S中除m以外元素压于中转栈TranSit中，顺序逆置
    while (! MyStack_Empty(TranSit)) {
        int val = MyStack_Pop(TranSit);
        MyStack_Push(S, val);
    }
    free(TranSit);
    //TranSit中逆置元素顺序压入S，释放TranSit空间
    printf("print stack from top to bottom: ");
    MyStack_Print(S);
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
struct List {
    char ch;
    struct List* next;
};
typedef struct List Node;
typedef struct {
    Node* head;
    int size;
} String;
//字符链表声明
String* StringInit() { //初始化空串
    String* Str = (String*)malloc(sizeof(String));
    Str -> size = 0;
    Str -> head = NULL;
    return Str;
}
void StringInput(String* Str) { //对空串进行赋值操作
    int len;
    Node* p;
    printf("enter the length of string: ");
    scanf("%d", &len);
    for (int i = 0; i < len; i ++) {
        Node* newnode = (Node*)malloc(sizeof(Node));
        getchar();
        scanf("%c", &newnode -> ch);
        newnode -> next = NULL;
        if (Str -> size == 0) {
            Str -> head = newnode;
            p = Str -> head;
        } else {
            p -> next = newnode;
            p = p -> next;
        }
        Str -> size ++;
    }
    return ;
}
int KMP(String* Str1, String* Str2) { //字符串比较算法，返回匹配位置下标
    int pos = 0;
    Node* s = Str1 -> head;
    Node* p1 = Str1 -> head, * p2 = Str2 -> head;
    while (p1 && p2) {
        if (p1 -> ch == p2 -> ch) {
            p1 = p1 -> next;
            p2 = p2 -> next;
        } else {
            s = s -> next;
            pos ++;
            p1 = s;
            p2 = Str2 -> head;
        }
    }
    if (!p1 && p2) {
        printf("not found\n");
        return -1;
    } else {
        return pos;
    }
}
Node* FindPrev(String* Str, int pos) { //返回第一个匹配位置对应链结的前驱
    Node* prev = Str -> head;
    if (pos == 0) return NULL;
    pos --;
    while (prev) {
        if (pos == 0) return prev;
        prev = prev -> next;
        pos --;
    }
    return NULL;
}
Node* FindRear(String* Str, int pos, int len) { //返回匹配子串的第一个后继
    Node* rear = Str -> head;
    pos += len;
    while (rear) {
        if (pos == 0) return rear;
        rear = rear -> next;
        pos --;
    }
    return NULL;
}
Node* SubListReverse(Node* head, int len, Node* rear) { //逆置子串算法
    Node* pre, * cur, * nxt;
    pre = NULL;
    cur = head;
    while (len --) {
        nxt = cur -> next;
        cur -> next = pre;
        pre = cur;
        cur = nxt;
    }
    //将逆置字符链表连接原后继，保证逆置子串的前后完整性
    head -> next = rear;
    return pre;
}
void StringPrint(String* Str) { //打印字符链表
    Node* p = Str -> head;
    while (p) {
        printf("%c", p -> ch);
        p = p -> next;
    }
    printf("\n");
    return ;
}
int main() {
    String* Str1 = StringInit();
    String* Str2 = StringInit();
    StringInput(Str1);
    StringInput(Str2);
    int pos = KMP(Str1, Str2);
    if (pos == -1) return 0;
    Node* prev = FindPrev(Str1, pos);
    Node* rear = FindRear(Str1, pos, Str2 -> size);
    printf("Before Sub List Reverse Function: ");
    StringPrint(Str1);
    //按是否有前驱进行讨论
    if (prev)
        prev -> next = SubListReverse(prev -> next, Str2 -> size, rear);
    else 
        Str1 -> head = SubListReverse(Str1 -> head, Str2 -> size, rear);
    printf("After Sub List Reverse Function: ");
    StringPrint(Str1);
    return 0;
}
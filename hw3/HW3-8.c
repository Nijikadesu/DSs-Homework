#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void FirstNotFound(String* Str1, String* Str2) { //打印str1中第一个不在str2出现的字符
    Node* p1 = Str1 -> head;
    bool found = false;
    int tag;
    while (p1) {
        Node* p2 = Str2 -> head;
        while (p2) {
            if (p1 -> ch == p2 -> ch) {
                found = true;
            }
            p2 = p2 -> next;
        }
        if (!found) {
            printf("The ch you want is %c!\n", p1 -> ch);
            return ;
        }
        found = false;
        p1 = p1 -> next;
    }
    printf("All match!\n");
    return ;
}
int main() {
    String* Str1 = StringInit();
    String* Str2 = StringInit();
    StringInput(Str1);
    StringInput(Str2);
    FirstNotFound(Str1, Str2);
    return 0;
}
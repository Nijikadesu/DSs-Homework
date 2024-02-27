#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30
void StrDelete(char* S, int i, int m) {
    int len = strlen(S);
    if (i >= len) return ;
    if (i + m >= len) {
        S[i] = '\0';
        return ;
    }
    char ans[SIZE];
    //strncpy不会在复制完后给字符串自动添加结束符，需要手动添加
    strncpy(ans, &S[0], i); //将S的[0, i)区间内字符子串复制给ans
    ans[i] = '\0';
    strncpy(&ans[i], &S[i + m], len - i - m); //将S的[i + m, len)区间内字符子串复制到ans尾端
    ans[len] = '\0';
    S[0] = '\0';
    strcpy(S, ans); //将S用结果字符串ans覆盖
    S[len - m] = '\0';
    return ;
}
int main() {
    char S[SIZE];
    printf("Please Enter the String: ");
    scanf("%s", S);
    int i, m;
    printf("Starting Position: ");
    scanf("%d", &i);
    printf("Wanted Length: ");
    scanf("%d", &m);
    StrDelete(S, i, m);
    printf("After StrDelete Function: %s", S);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
void DeleteAndCopy(char* str, int s, int m, int t) {
    char ans[SIZE]; //辅助串，用于保存str的操作进度
    strncpy(ans, &str[m + t], s - m - t); //截取S中删除部分后的子串
    ans[s - m - t] = '\0'; 
    str[m] = '\0'; //删除S第m个字符开始的后续所有字符
    strcat(str, ans); //将S删除部分后的子串重新接入，确保完整性
    strcpy(ans, str); //将ans用str覆盖
    ans[s - t] = '\0';
    for (int i = s - t; i <= s; i ++) {
        str[i] = ' ';
    }
    str[s] = '\0'; //将str长度用空格延展到以下标s为止
    strcat(str, ans); //拼接str与ans得出所求字符串
    printf("After Delete and Copy:\n%s", str);
    return ;
}
int main() {
    int s, m, t;
printf("length? starting position? sublength?\n");
    scanf("%d %d %d", &s, &m, &t);
    m --; //题目问的是第m个字符，故须减1转换成数组下标
    char str[SIZE];
    printf("Please Enter the String:\n");
    scanf("%s", str);
    DeleteAndCopy(str, s, m ,t);
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
struct node {
    int line;
    int row;
    int val;
}; //三元组表结点声明
typedef struct node Node;
typedef struct {
    int size;
    Node mp[MAXSIZE];
    bool vis[MAXSIZE][MAXSIZE]; //矩阵i行j列元素存在性
} Matrix; //三元组表声明
Matrix* CreateMatrix(int size) { //建表
    Matrix* Mp = (Matrix*)malloc(sizeof(Matrix));
    for (int i = 0; i < MAXSIZE; i ++) {
        memset(&Mp -> vis[i][0], false, MAXSIZE * sizeof(bool));
    }
    Mp -> size = size;
    for (int i = 0; i < size; i ++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Mp -> mp[i].line = a;
        Mp -> mp[i].row = b;
        Mp -> mp[i].val = c;
        Mp -> vis[a][b] = true;
    }
    return Mp;
}
Matrix* MatrixSum(Matrix* M1, Matrix* M2) { //矩阵加法
    Matrix* Ans = (Matrix*)malloc(sizeof(Matrix));
    Ans -> size = M1 -> size;
    for (int i = 0; i < MAXSIZE; i ++) {
        memset(&Ans -> vis[i][0], false, MAXSIZE * sizeof(bool));
    }
    for (int i = 0; i < M1 -> size; i ++) {
        Ans -> mp[i].line = M1 -> mp[i].line;
        Ans -> mp[i].row = M1 -> mp[i].row;
        Ans -> mp[i].val = M1 -> mp[i].val;
        Ans -> vis[Ans -> mp[i].line][Ans -> mp[i].row] = true;
    }
    for (int i = 0; i < M2 -> size; i ++) {
        int line = M2 -> mp[i].line;
        int row = M2 -> mp[i].row;
        int val = M2 -> mp[i].val;
        //判断M1与M2是否在相同位置存在非零元素
        if (Ans -> vis[line][row]) {
            for (int i = 0; i < Ans -> size; i ++) {
                if (Ans -> mp[i].line == line && Ans -> mp[i].row == row) {
                    Ans -> mp[i].val += val;
                }
            }
        } else {
            Ans -> mp[Ans -> size].line = line;
            Ans -> mp[Ans -> size].row = row;
            Ans -> mp[Ans -> size].val = val;
            Ans -> size ++;
        }
    }
    return Ans;
}
void MatrixPrint(Matrix* Mp) { //打印矩阵
    for (int i = 0; i < Mp -> size; i ++) {
        printf("Line: %d, Row: %d ", Mp -> mp[i].line, Mp -> mp[i].row);
        printf("Val : %d\n", Mp -> mp[i].val);
    }
    return ;
}
int main() {
    int size1, size2;
    printf("Matrix Size Initialize: ");
    scanf("%d %d", &size1, &size2);
    Matrix* M1, * M2;
    M1 = CreateMatrix(size1);
    M2 = CreateMatrix(size2);
    Matrix* SUM = MatrixSum(M1, M2);
    MatrixPrint(SUM);
    return 0;
}
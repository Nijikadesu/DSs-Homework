#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100
int Tri[MAXSIZE][MAXSIZE]; //存储三对角矩阵
int n; //三对角矩阵尺寸
void TriToArray(int* A) { //转一维数组算法
    int cursize = 0;
    int start = -1, len = 3, idx = 0;
    while (idx <= n) {
        int left = start > 0 ? start : 0;
        int right = start + len < n ? start + len : n;
        for (int i = left; i < right; i ++) {
            A[cursize ++] = Tri[idx][i];
        }
        idx ++;
        start ++;
    }
    return ;
}
int main() {
    printf("TriMatrix Initialize: \n");
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            scanf("%d", &Tri[i][j]);
        }
    }
    int A[3 * n - 2];
    TriToArray(A);
    printf("After TriToArray Function: \n");
    for (int i = 0; i < 3 * n - 2; i ++) {
        printf("%d", A[i]);
        if (i != 3 * n - 3) printf(" ");
        else printf("\n");
    }
    return 0;
}
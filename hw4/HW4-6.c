#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXSIZE 100
int m, n;
int A[MAXSIZE][MAXSIZE];
bool isLineMin(int x, int y) { //判断A[x][y]是否为行最小元素
    int min = INT_MAX;
    for (int i = 0; i < n; i ++) {
        if (min > A[x][i]) min = A[x][i];
    }
    return min == A[x][y];
}
bool isRowMax(int x, int y) { //判断A[x][y]是否为列最大元素
    int max = INT_MIN;
    for (int i = 0; i < m; i ++) {
        if (max < A[i][y]) max = A[i][y];
    }
    return max == A[x][y];
}
int main() {
    printf("Size Initial: ");
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            if (isLineMin(i, j) && isRowMax(i, j)) {  //马鞍点同时满足行最小与列最大
                printf("MApoint: A[%d][%d]=%d\n", i, j, A[i][j]); //输出马鞍点信息
            }
        }
    }
    return 0;  
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAXSIZE 100
int matrix[MAXSIZE][MAXSIZE];
struct mapNode {
    int val;
    struct mapNode* next;
};
typedef struct mapNode MapNode;
typedef struct {
    MapNode Mp[MAXSIZE];
    int size;
} Map;
Map* MapInit(int n) {
    Map* M = (Map*)malloc(sizeof(Map));
    M -> size = n;
    for (int i = 0; i < n; i ++) {
        M -> Mp[i].val = i;
        M -> Mp[i].next = NULL;
    }
    return M;
}
Map* MatrixToMap(Map* M) {
    for (int i = 0; i < M -> size; i ++) {
        for (int j = 0; j < M -> size; j ++) {
            if (matrix[i][j]) {
                MapNode* NewNode = (MapNode*)malloc(sizeof(MapNode));
                NewNode -> val = j;
                NewNode -> next = M -> Mp[i].next;
                M -> Mp[i].next = NewNode;
            }
        }
    }
    return M;
}
void ChainMapPrint(Map* M) {
    for (int i = 0; i < M -> size; i ++) {
        MapNode* ptrl = &M -> Mp[i];
        while (ptrl != NULL) {
            printf("%d", ptrl -> val);
            if (ptrl -> next) printf(" -> ");
            ptrl = ptrl -> next;
        }
        printf("\n");
    }
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    Map* M = MapInit(n);
    M = MatrixToMap(M);
    ChainMapPrint(M);
    return 0;
}
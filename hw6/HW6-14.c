#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
typedef struct {
    MapNode* front;
    MapNode* rear;
} Queue; //BFS访问队列
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
void Dfs(Map* M, int start, bool* vis) {
    if (vis[start] == true) return ;
    // printf("%c", (char)('A' + start));
    printf("%d", start);
    vis[start] = true;
    MapNode* ptrl = &M -> Mp[start];
    while (ptrl != NULL) {
        Dfs(M, ptrl -> val, vis);
        ptrl = ptrl -> next;
    }
}
void DfsPrint(Map* M, int start, bool* vis) { //DFS
    printf("Dfs: ");
    Dfs(M, start, vis); 
    memset(vis, 0, sizeof(vis)); //重置vis数组
    printf("\n");
}
void Enqueue(Queue* Q, Map* M, int start) {
    MapNode* ptrl = M -> Mp[start].next;
    Q -> rear -> next = ptrl;
    while (ptrl && ptrl -> next) {
        ptrl = ptrl -> next;
    } 
    Q -> rear = ptrl;
}
void Bfs(Map* M, int start, bool* vis) {
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q -> front = &M -> Mp[start];
    Q -> rear = Q -> front;
    MapNode* cur;
    while (Q -> front != NULL) {
        cur = Q -> front;
        if (!vis[cur -> val]) {
            vis[cur -> val] = true;
            // printf("%c", (char)('A' + cur -> val));
            printf("%d", cur -> val);
            Enqueue(Q, M, cur -> val);
            cur = cur -> next;
        }
        Q -> front = Q -> front -> next;
    }
}
void BfsPrint(Map* M, int start, bool* vis) {
    printf("Bfs: ");
    Bfs(M, start, vis); 
    memset(vis, 0, sizeof(vis)); //重置vis数组
    printf("\n");
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
    bool vis[MAXSIZE] = {false};
    DfsPrint(M, 0, vis);
    BfsPrint(M, 0, vis);
    return 0;
}
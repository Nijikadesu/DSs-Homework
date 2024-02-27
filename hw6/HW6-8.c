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
        int connected, val;
        printf("输入与%d直接相连的顶点数与下标: ", (char)(i));
        scanf("%d", &connected);
        MapNode* cur = &M -> Mp[i]; //尾插法指针
        for (int h = 0; h < connected; h ++) {
            scanf("%d", &val);
            MapNode* newnode = (MapNode*)malloc(sizeof(MapNode));
            newnode -> val = val;
            newnode -> next = NULL;
            cur -> next = newnode;
            cur = cur -> next;
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
            printf("%d", cur -> val);
            // printf("%c", (char)('A' + cur -> val));
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
    Map* M = MapInit(n);
    bool vis[MAXSIZE] = {false};
    DfsPrint(M, 0, vis);
    BfsPrint(M, 0, vis);
    return 0;
}
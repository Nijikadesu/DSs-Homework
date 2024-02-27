#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct treeNode {
    int val;
    struct treeNode* left;
    struct treeNode* right;
};
typedef struct treeNode TreeNode;
//建立二叉排序树作为算法演示，假设二叉树中结点不重复
TreeNode* NodeInsert(TreeNode* root, int val) {
    if (root == NULL) {
        root = (TreeNode*)malloc(sizeof(TreeNode));
        root -> val = val;
        root -> left = NULL; root -> right = NULL;
        return root;
    } else if (root -> val > val) {
        root -> left = NodeInsert(root -> left, val);
    } else if (root -> val < val) {
        root -> right = NodeInsert(root -> right, val);
    }
    return root;
}
TreeNode* FindParent(TreeNode* root, int x) {
    if (!root -> left && !root -> right) {
        return NULL;
    } else if (!root -> left && root -> right) {
        if (root -> right -> val == x) return root;
        else return FindParent(root -> right, x);
    } else if (!root -> right && root -> left) {
        if (root -> left -> val == x) return root;
        else return FindParent(root -> left, x);
    } else {
        if (root -> left -> val == x || root -> right -> val == x) {
            return root;
        } else {
            TreeNode* lsearch = FindParent(root -> left, x);
            TreeNode* rsearch = FindParent(root -> right, x);
            if (lsearch != NULL) return lsearch;
            else return rsearch;
        }
    }
}
int main() {
    int n, x; //节点数
    scanf("%d %d", &n, &x);
    TreeNode* Root = NULL;
    for (int i = 0; i < n; i ++) {
        int val;
        scanf("%d", &val);
        Root = NodeInsert(Root, val);
    }
    TreeNode* res = FindParent(Root, x);
    if (res == NULL) {
        if (Root -> val == x) printf("No Parent\n");
        else printf("Node Not exist\n");
    }
    else printf("%d\n", res -> val);
    return 0;
}
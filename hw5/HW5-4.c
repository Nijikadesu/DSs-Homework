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
/*
为了使左右子树的交换更加直观，我选择建立一个二叉排序树，本题中交换
左右子树位置的操作可以直观体现在二叉排序树的中序遍历上，表现为中序
遍历序列由递增变为递减。
*/
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
TreeNode* TreeSwap(TreeNode* root) {
    if (root == NULL) return NULL;
    TreeNode* StagingP = root -> left;
    root -> left = root -> right;
    root -> right = StagingP;
    root -> left = TreeSwap(root -> left);
    root -> right = TreeSwap(root -> right);
    return root;
}
void InorderTravisal(TreeNode* root) {
    if (root == NULL) return ;
    InorderTravisal(root -> left);
    printf("%d ", root -> val);
    InorderTravisal(root -> right);
}
void InorderPrint(TreeNode* root) {
    printf("Inorder Travisal Result: ");
    InorderTravisal(root);
    printf("\n");
}
int main() {
    int n; //节点数
    scanf("%d", &n);
    TreeNode* Root = NULL;
    for (int i = 0; i < n; i ++) {
        int val;
        scanf("%d", &val);
        Root = NodeInsert(Root, val);
    }
    InorderPrint(Root);
    TreeSwap(Root);
    InorderPrint(Root);
    return 0;
}
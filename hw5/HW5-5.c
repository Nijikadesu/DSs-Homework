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
//建立二叉排序树进行算法演示
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
void InorderDNO(TreeNode* root) { //输出删除子树的前序遍历&释放空间
    if (root == NULL) return ;
    printf("%d ", root -> val);
    InorderDNO(root -> left);
    InorderDNO(root -> right);
    free(root);
}
void DNO(TreeNode* root) {
    printf("SubTree Deleted Output: ");
    InorderDNO(root);
    printf("\n");
}
TreeNode* DeleteAndOutput(TreeNode* root, int x) { //主要算法
    if (root == NULL) {
        return NULL;
    } else if (root -> val == x) {
        DNO(root);
        return NULL;
    } else {
        root -> left = DeleteAndOutput(root -> left, x);
        root -> right = DeleteAndOutput(root -> right, x);
    }
    return root;
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
    Root = DeleteAndOutput(Root, x);
    return 0;
}
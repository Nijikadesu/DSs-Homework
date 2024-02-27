#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// 哈夫曼树节点结构
struct HuffmanTreeNode {
    char data; // 字符
    unsigned freq; // 字符出现的频率
    struct HuffmanTreeNode *left, *right; // 左右子节点
};

// 哈夫曼树结构
struct HuffmanTree {
    unsigned size; // 当前节点数量
    unsigned capacity; // 堆的总容量
    struct HuffmanTreeNode** array; // 指向节点数组的指针
};

// 创建新的哈夫曼树节点
struct HuffmanTreeNode* newNode(char data, unsigned freq) {
    struct HuffmanTreeNode* temp = (struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// 创建一个最小堆（辅助查找最小与次最小频率结点）
struct HuffmanTree* createMinHeap(unsigned capacity) {
    struct HuffmanTree* minHeap = (struct HuffmanTree*)malloc(sizeof(struct HuffmanTree));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct HuffmanTreeNode**)malloc(minHeap->capacity * sizeof(struct HuffmanTreeNode*));
    return minHeap;
}

// 交换两个哈夫曼树节点
void swapHuffmanTreeNode(struct HuffmanTreeNode** a, struct HuffmanTreeNode** b) {
    struct HuffmanTreeNode* t = *a;
    *a = *b;
    *b = t;
}

// 构造最小堆
void minHeapify(struct HuffmanTree* minHeap, int idx) {
    int smallest = idx; //初始化当前下标为idx的节点频率为最小值
    int left = 2 * idx + 1; //左儿子下标
    int right = 2 * idx + 2; //右儿子下标
    
    // 左儿子存在，且左儿子频率小于父节点频率，更新smallest
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }

    // 右儿子存在，且右儿子频率小于父节点频率，更新smallest
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }

    //若smallest被更新，则说明左右儿子至少一个频率小于父节点，交换父节点与较小频率节点位置
    if (smallest != idx) {
        swapHuffmanTreeNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 检查堆的大小是否为一，即是否所有的节点都被合并到哈夫曼树中
int isSizeOne(struct HuffmanTree* minHeap) {
    return (minHeap->size == 1);
}

// 从最小堆中取出并删除根节点（频率最小的节点）
struct HuffmanTreeNode* extractMin(struct HuffmanTree* minHeap) {
    struct HuffmanTreeNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// 插入一个新节点到最小堆中
void insertMinHeap(struct HuffmanTree* minHeap, struct HuffmanTreeNode* minHeapNode) {
    minHeap->size++;
    int i = minHeap->size - 1;

    //自底向上寻找新节点的插入位置
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }

    minHeap->array[i] = minHeapNode;
}

// 构建最小堆
void buildMinHeap(struct HuffmanTree* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }
}

// 判断节点是否是叶节点
int isLeaf(struct HuffmanTreeNode* root) {
    return !(root->left) && !(root->right);
}

// 根据给定的字符及其频率构建哈夫曼树
struct HuffmanTree* buildHuffmanTree(char data[], int freq[], int size) {
    struct HuffmanTreeNode *left, *right, *top;

    // 对堆作乱序初始化
    struct HuffmanTree* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i) {
        minHeap->array[i] = newNode(data[i], freq[i]);
    }
    minHeap->size = size;
    buildMinHeap(minHeap);

    // 建立哈夫曼树，每次合并最小与次最小频率节点，再将新生成的节点插入最小堆
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    //建树完成后，最小堆仅存储哈夫曼树的根节点
    return minHeap;
}

// 用于存储编码结果
char codes[MAX_TREE_HT][256]; // 增加字符范围以存储所有可能的ASCII字符

// 递归编码并存储
void storeCodes(struct HuffmanTreeNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        for (int i = 0; i < top; ++i) {
            codes[root->data][i] = arr[i] + '0'; // 数字转字符
        }
        codes[root->data][top] = '\0'; // 字符串结束符
    }
}

// 打印哈夫曼编码
void printCodes(struct HuffmanTreeNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// 构建哈夫曼编码并保存到文件
void HuffmanCodes(char data[], int freq[], int size) {
    struct HuffmanTree* minHeap = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    storeCodes(minHeap->array[0], arr, top); // 存储编码
    printCodes(minHeap->array[0], arr, top); // 打印编码
}

// 读取字符和频率，构建哈夫曼树并打印编码
void readAndBuildHuffmanTree() {
    int n;
    printf("Enter the number of characters (n): ");
    scanf("%d", &n);

    char* data = (char*)malloc(n * sizeof(char));
    int* freq = (int*)malloc(n * sizeof(int));

    printf("Enter %d characters and their frequencies:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Char #%d: ", i+1);
        scanf(" %c", &data[i]);
        if (data[i] == '#')
            data[i] = ' ';
        printf("Freq of %c: ", data[i]);
        scanf("%d", &freq[i]);
    }

    HuffmanCodes(data, freq, n);

    free(data);
    free(freq);
}

// 编码一个字符串
void encodeString(char data[], int size) {
    printf("Encoded string: ");
    for (int i = 0; i < size; i++) {
        if (codes[data[i]][0] != '\0') { // 确保字符有对应的编码
            printf("%s", codes[data[i]]);
        } else {
            printf("Error: Character '%c' not found in Huffman Tree.\n", data[i]);
        }
    }
    printf("\n");
}

int main() {
    readAndBuildHuffmanTree(); //读入字符频率，进行哈夫曼编码
    char testStr[] = "THIS PROGRAM IS MY FAVORITE";
    encodeString(testStr, strlen(testStr)); // 编码字符串
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 10000

// 计算 next 数组
void computeNextArray(char* pat, int M, int* next) {
    int len = 0;
    next[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            next[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = next[len - 1];
            }
            else {
                next[i] = 0;
                i++;
            }
        }
    }
}

// KMP 搜索算法 - 输出模式串出现的行号、该行中出现的次数以及位置
void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int* next = (int*)malloc(sizeof(int) * M);
    computeNextArray(pat, M, next);

    int i = 0; // txt 的索引
    int j = 0; // pat 的索引
    int line = 1; // 行号
    int count = 0; // 当前行中模式串出现的次数
    int lastNewLine = -1; // 上一个换行符的位置

    while (i < N) {
        if (txt[i] == '\n') {
            line++;
            lastNewLine = i;
            if (count > 0) {
                printf("Line %d: count %d\n", line - 1, count); // 输出上一行的模式串出现次数
                count = 0; // 重置计数器
            }
        }
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            printf("行号 %d, 位置 %d\n", line, i - j - lastNewLine);
            j = next[j - 1];
            count++;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = next[j - 1];
            } else {
                i++;
            }
        }
    }
    if (count > 0) {
        printf(" %d: count %d\n", line, count); // 输出最后一行的模式串出现次数
    }
    free(next);
}

// 统计功能：统计文本中的单词、空格和标点符号数量
void statistics(char* txt) {
    int wordCount = 0, spaceCount = 0, punctuationCount = 0;
    char* ptr = txt;
    int inWord = 0;

    while (*ptr) {
        if (isspace((unsigned char)*ptr)) {
            spaceCount++;
            if (inWord) {
                inWord = 0;
                wordCount++;
            }
        }
        else if (ispunct((unsigned char)*ptr)) {
            punctuationCount++;
        }
        else {
            inWord = 1;
        }
        ptr++;
    }
    if (inWord) {
        wordCount++; // Count the last word
    }

    printf("单词数: %d\n空格树: %d\n标点符号数: %d\n", wordCount, spaceCount, punctuationCount);
}

// 替换功能：替换文本中的特定单词
void replaceWord(char* txt, const char* search, const char* replace, FILE* output) {
    char* pos, temp[MAX_BUFFER];
    int index = 0;
    int owlen;

    owlen = strlen(search);
    while ((pos = strstr(txt, search)) != NULL) {
        strcpy(temp, txt);
        index = pos - txt;
        txt[index] = '\0';
        strcat(txt, replace);
        strcat(txt, temp + index + owlen);
    }
    fprintf(output, "Replaced text:\n%s\n", txt);
}

// 读取文件内容到字符串
char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char *buffer = (char*)malloc(MAX_BUFFER);
    size_t contentSize = 1; // 包括NULL-terminator
    char *content = (char*)malloc(MAX_BUFFER);
    if(content == NULL){
        perror("Failed to allocate content");
        fclose(file);
        return NULL;
    }
    content[0] = '\0'; // 确保内容为空字符串

    while(fgets(buffer, MAX_BUFFER, file)) {
        char *old = content;
        contentSize += strlen(buffer);
        content = (char*)realloc(content, contentSize);
        if(content == NULL){
            perror("Failed to reallocate content");
            free(old);
            fclose(file);
            return NULL;
        }
        strcat(content, buffer);
    }

    if(ferror(file)) {
        free(content);
        perror("Error reading file");
        fclose(file);
        return NULL;
    }

    fclose(file);
    free(buffer);
    return content;
}

// 写入字符串到文件
void writeFile(const char* filename, const char* data) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fputs(data, file);
    fclose(file);
}

int main() {
    char* inputFilename = "../data/in.txt";
    char* outputFilename = "../data/out.txt";
    char* text = readFile(inputFilename);
    if (text == NULL) {
        return 1;
    }

    FILE* output = fopen(outputFilename, "w");
    if (output == NULL) {
        perror("Error opening output file");
        free(text);
        return 1;
    }

    // 循环选择操作
    int choice;
    char pat[100];
    char replace[100];
    do {
        printf("选择操作：\n1. 统计\n2. 查找\n3. 替换\n0. 退出\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                statistics(text);
                break;
            case 2:
                printf("输入查找模式串：");
                scanf("%s", pat);
                KMPSearch(pat, text);
                break;
            case 3:
                printf("输入查找单词：");
                scanf("%s", pat);
                printf("输入替换单词：");
                scanf("%s", replace);
                replaceWord(text, pat, replace, output);
                writeFile(inputFilename, text); // 将替换后的文本写回文件
                break;
            case 0:
                printf("退出...\n");
                break;
            default:
                printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);

    free(text);
    fclose(output);
    return 0;
}

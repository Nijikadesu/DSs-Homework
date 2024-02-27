#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100

int main() {
    int nums[MAXSIZE];
    int size;
    printf("Size Initial: ");
    scanf("%d", &size);
    int left = 0, right = size - 1; //双指针
    for (int i = 0; i < size; i ++) scanf("%d", &nums[i]);
    while (left < right) {
        if (nums[left] % 2 == 0 && nums[right] % 2 == 0) {
            //左偶右偶，左指针不动，右指针左移
            right --;
        } else if (nums[left] % 2 != 0 && nums[right] % 2 != 0) {
            //左奇右奇，右指针不动，左指针右移
            left ++;
        } else if (nums[left] % 2 != 0 && nums[right] % 2 == 0) {
            //左奇右偶，不需要任何操作，左右同时向中间迭代
            left ++; right --;
        } else {
            //左偶右奇，左指针与右指针指向元素互换后，同时向中间迭代
            int t = nums[left];
            nums[left ++] = nums[right];
            nums[right --] = t;
        }
    }
    //算法时间复杂度为O(n), 空间复杂度为O(1)
    for (int i = 0; i < size; i++) {
        printf("%d", nums[i]);
        if (i != size - 1) printf(" ");
        else printf("\n");
    }
    return 0;
}
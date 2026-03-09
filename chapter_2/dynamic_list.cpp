#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define InitSize 10

typedef struct{
    int *data;
    int MaxSize;
    int length;
} SqList;

void InitList(SqList &L){
    L.data = (int *)malloc(sizeof(int) * InitSize);

    L.length = 0;
    L.MaxSize = InitSize;
}

// 动态增加数组长度
void IncreaseSize(SqList &L, int len){
    int *p = L.data;
    L.data = (int *)malloc(sizeof(int) * (L.MaxSize + len));

    for(int i = 0; i < L.length; i++){
        L.data[i] = p[i];    // 将数据复制到新区域
    }

    L.MaxSize += len;    // 更新数组长度

    free(p);     // 释放原来的内存空间
}

// 在第 i 个位置插入元素 e
bool ListInsert(SqList &L, int i, int e){
    if(i < 1 || i > L.length + 1) return false;
    if(L.length >= L.MaxSize) IncreaseSize(L, 5);    // 如果当前存储空间已满，则增加数组长度

    for(int j = L.length; j >= i; j --){
        L.data[j] = L.data[j-1];
    }

    L.data[i - 1] = e;
    L.length ++;

    return true;
}

// 删除第 i 个位置的元素，并用 e 返回其值
bool ListDelete(SqList &L, int i, int *e){
    if (L.length <= 0 || i < 1 || i > L.length){
        printf("Invalid position or list is empty\n");

        return false;
    }

    *e = L.data[i - 1];

    for(int j = i; j < L.length; j ++){
        L.data[j - 1] = L.data[j];
    }

    L.length --;

    return true;
}

// 查找第一个值为 e 的元素，并返回其位置
int LocateElem(SqList &L, int e){
    for(int i = 0; i < L.length; i ++){
        if(L.data[i] == e) return i + 1;
    }

    return 0;
}

// 打印顺序表中的元素和顺序表长度
void PrintList(SqList &L){
    for (int i = 0; i < L.length; i ++){
        printf("L.data[%d] = %d\n", i, L.data[i]);
    }

    printf("Length = %d\n", L.length);
}

int main(){
    SqList L1,L2;
    
    InitList(L1);
    L1.length = 5;     // 假设顺序表中已经有5个元素
    for(int i = 0; i < L1.length; i ++){
        L1.data[i] = i + 1;    // 初始化顺序表中的元素
    }

    ListInsert(L1, 3, 9);
    PrintList(L1);
    int *e = (int *)malloc(sizeof(int));
    ListDelete(L1, 4, e);
    PrintList(L1);
    printf("Deleted element: %d\n", *e);

    InitList(L2);
    L2.length = L2.MaxSize;     // 假设顺序表中已经有MaxSize个元素
    for(int i = 0; i < L2.length; i ++){
        L2.data[i] = i + 10;
    }
    ListInsert(L2, 5, 99);    // 在第5个位置插入元素99
    PrintList(L2);

    int pos = LocateElem(L2, 12);    // 查找元素12在顺序表中的位置
    if(pos != 0)
        printf("Element 12 is located at position %d\n", pos);
    else
        printf("Element 12 not found in the list\n");

    return 0;
}
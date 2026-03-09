#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 10

typedef struct{
    int data[MaxSize];
    int length;
} SqList;

void InitList(SqList *L) {
    for(int i = 0; i < MaxSize; i++) {
        L->data[i] = 0;
    }
    L->length = 0;
}

// 在顺序表中第 i 个位置插入元素 e
bool ListInsert(SqList *L, int i, int e){
    if(L->length >= MaxSize || i < 1 || i > L->length + 1) {
        printf("Invalid position or list is full\n");

        return false;
    }
        
    for(int j = L->length; j >= i; j--){
        L->data[j] = L->data[j - 1];
    }

    L->data[i - 1] = e;
    L->length ++;

    return true;
}

// 删除顺序表的第 i 个元素，并用 e 返回其值
bool ListDelete(SqList *L, int i, int *e){
    if(L->length <= 0 || i < 1 || i > L->length) {
        printf("Invalid position or list is empty\n");

        return false;
    }

    *e  = L->data[i - 1];

    for(int j = i; j < L->length; j ++){
        L->data[j - 1] = L->data[j];
    }

    L->length --;

    return true;
}

// 查找第一个值为 e 的元素，并返回其位置
int LocateElem(SqList *L, int e){
    for(int i = 0; i < L->length; i ++){
        if(L->data[i] == e) return i + 1;
    }

    return 0;
}

// 打印顺序表中的元素和顺序表长度
void PrintList(SqList *L) {
    for(int i = 0; i < L->length; i++){
        printf("data[%d] = %d\n", i, L->data[i]);
    }

    printf("Length = %d\n", L->length);
}

int main(){
    SqList L;
    InitList(&L);

    L.length = 5;     // 假设顺序表中已经有5个元素
    for(int i = 0; i < 5; i ++){
        L.data[i] = i * 2;
    }

    ListInsert(&L, 3, 9);    // 在第3个位置插入元素9
    PrintList(&L);

    int *e = (int *)malloc(sizeof(int));
    ListDelete(&L, 4, e);    // 删除第4个元素
    printf("Deleted element: %d\n", *e);
    PrintList(&L);

    int pos = LocateElem(&L, 6);    // 查找元素6的位置
    if(pos != 0)
        printf("Element 6 is located at position: %d\n", pos);
    else
        printf("Element 6 not found in the list\n");

    return 0;
}


// L->data[i] is used when L is a pointer to a struct
// L.data[i] is used when L is a direct struct variable
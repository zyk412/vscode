#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 定义链表中的一个节点，包含数据和指针两部分
typedef struct LNode{
    int data;
    struct LNode *next; 
} LNode, *LinkList;     
// *LinkList 为指针类型。使用LNode*, 表明这是一个指针；使用LinkList，表明这是一个链表。

// 初始化一个带头结点的单链表
bool InitList(LinkList &L){
    L = (LNode *)malloc(sizeof(LNode));   // 创建头结点
    if(L == NULL) return false;   // 头指针内存分配失败

    L->next = NULL;   // 头结点的next指针指向NULL
    return true;   // 初始化成功
}

// 查找第 i 个结点
LNode *GetElem(LinkList &L, int i){
    if(i <= 0) return NULL;   // i 不合法

    LNode *p = L;
    for(int j = 0; j < i; j ++){
        p = p->next;

        if(p == NULL) return NULL;    // i 超出表长
    }

    return p;
}

// 在第 i 个位置插入值为 e 的结点
bool ListInsert(LinkList &L, int i, int e){
    LNode *p = GetElem(L, i - 1);    // 获取第 i-1 个结点

    if(p == NULL) return false;

    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s == NULL) return false;
    
    s->data = e;
    s->next = p->next;
    p->next = s;

    return true;
}

// 在结点 p 前插入结点 s   (相当于后插并交换数据域)
bool InsertList2(LNode *p,LNode *s){
    if(s == NULL) return false;

    s->next = p->next;
    p->next = s;

    int temp = p->data;
    p->data = s->data;
    s->data = temp;

    return true;
}

// 删除第 i 个结点，并用 e 返回第 i 个结点的值
bool ListDelete(LinkList &L, int i, int &e){
    LNode *p = GetElem(L, i - 1);

    if(p == NULL || p->next == NULL) return false;

    LNode *q = p->next;
    e = q->data;
    p->next = q->next;

    free(q);

    return true;
}

// 按值查找结点
LNode *LocateElem(LinkList &L, int e){
    LNode *p = L;

    while(p->next != NULL){
        p = p->next;

        if(p->data == e) return p;
    }

    return NULL;
}

// 求表长
int ListLength(LinkList &L){
    int length = 0;
    LNode *p = L->next;

    while(p != NULL){
        length ++;
        p = p->next;
    }

    return length;
}

// 头插法建立链表
bool 

// 尾插法建立链表

// 打印链表
void PrintList(LinkList &L){
    LNode *p = L;
    int i = 0;

    while(p->next != NULL){
        p = p->next;
        i ++;

        printf("第%d个元素为%d\n", i, p->data);
    }
}

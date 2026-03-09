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

// 对结点 p 进行后插

// 对结点 p 进行前插

// 删除第 i 个结点

// 删除给定结点 *p

// 按序号查找结点

// 按值查找结点

// 求表长



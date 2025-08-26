#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // 用于INT_MIN标记错误（object为int）

#define object int
// 检查链表是否为NULL（无返回值函数用）
#define CHECK_LIST(list) if (list == NULL) return;
// 检查内存分配（有返回值函数用，返回NULL）
#define CHECK_MEMORY(node) if (node == NULL) {\
    fprintf(stderr, "Memory allocation error!\n");\
    return NULL;\
}

// 循环链表节点
typedef struct CircularNode {
    object data;
    struct CircularNode* next;  // 非空时，尾节点的next指向头节点
} Node;

// 循环链表结构
typedef struct CList {
    Node* head;   // 头节点
    Node* tail;   // 尾节点（优化尾插/尾删效率）
    size_t size;  // 节点数量
} List;

/**
 * 初始化循环链表
 * 空链表：head = tail = NULL，size = 0
 */
static void initialize_CList(List* list) {
    CHECK_LIST(list);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * 创建新节点
 * @param data：节点数据
 * @param next：节点的next指针（循环链表中需手动维护闭环）
 * @return 新节点地址（内存分配失败返回NULL）
 */
static Node* new_node(object data, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    CHECK_MEMORY(newNode);
    newNode->data = data;
    newNode->next = next;
    return newNode;
}

/**
 * 头插法：在链表头部插入节点
 * 核心：新节点成为新头，尾节点的next指向新头（保持闭环）
 */
static void push_front(object data, List* list) {
    CHECK_LIST(list);
    Node* newNode = new_node(data, list->head);  // 新节点next指向原头

    if (list->size == 0) {  // 空链表：新节点自闭环（next指向自身）
        newNode->next = newNode;
        list->tail = newNode;  // 尾节点也指向新节点
    }
    else {  // 非空链表：尾节点next指向新头（保持闭环）
        list->tail->next = newNode;
    }

    list->head = newNode;  // 更新头节点
    list->size++;
}

/**
 * 尾插法：在链表尾部插入节点
 * 核心：新节点成为新尾，新尾的next指向头（保持闭环）
 */
static void push_back(object data, List* list) {
    CHECK_LIST(list);
    Node* newNode = new_node(data, list->head);  // 新节点next直接指向头（提前闭环）

    if (list->size == 0) {  // 空链表：新节点自闭环，头/尾都指向它
        newNode->next = newNode;
        list->head = newNode;
    }
    else {  // 非空链表：原尾节点next指向新节点
        list->tail->next = newNode;
    }

    list->tail = newNode;  // 更新尾节点
    list->size++;
}

/**
 * 遍历循环链表
 * 核心：终止条件为“curr->next == head”（遍历到尾节点），避免无限循环
 */
static void traverse(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // 空链表
        printf("[]\n");
        return;
    }

    Node* curr = list->head;
    printf("[");
    do {  // 先打印当前节点，再判断是否终止（处理单个节点的情况）
        printf("%d", curr->data);
        curr = curr->next;
        if (curr != list->head) {  // 不是尾节点，加分隔符
            printf(", ");
        }
    } while (curr != list->head);  // 终止条件：回到头节点

    printf("]\n");
}

/**
 * 释放循环链表内存
 * 核心：先断开闭环（尾节点next设为NULL），再按单向链表释放，避免无限循环
 */
static void free_list(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // 空链表直接清空状态
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    // 1. 断开闭环：尾节点next设为NULL（避免遍历无限循环）
    list->tail->next = NULL;

    // 2. 按单向链表释放所有节点
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next_ptr = curr->next;
        free(curr);
        curr = next_ptr;
    }

    // 3. 清空链表状态
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * 反转循环链表
 * 核心：反转后新尾（原头）的next指向新头（保持闭环）
 */
static void reverse_list(List* list) {
    CHECK_LIST(list);
    if (list->size <= 1) {  // 空链表或单个节点，无需反转
        return;
    }

    Node* prev = NULL;
    Node* curr = list->head;
    Node* next = NULL;
    Node* old_head = list->head;  // 原头节点（反转后成为新尾）
    Node* old_tail = list->tail;  // 原尾节点（反转后成为新头）

    // 反转指针（同单向链表，但需遍历整个闭环）
    do {
        next = curr->next;  // 保存下一个节点
        curr->next = prev;  // 反转当前节点的next
        prev = curr;        // prev移动到当前节点
        curr = next;        // curr移动到下一个节点
    } while (curr != list->head);  // 遍历完所有节点（回到原头）

    // 修复闭环：新尾（原头）的next指向新头（原尾）
    old_head->next = old_tail;

    // 更新头和尾节点
    list->head = old_tail;
    list->tail = old_head;
}

/**
 * 头删法：删除头部节点
 * 核心：删除后新头的next被尾节点指向（保持闭环）
 */
static void pop_front(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // 空链表，直接返回
        return;
    }

    Node* old_head = list->head;
    if (list->size == 1) {  // 只剩一个节点：删除后为空链表
        list->head = NULL;
        list->tail = NULL;
    }
    else {  // 多个节点：尾节点next指向新头（原头的next）
        list->tail->next = old_head->next;
        list->head = old_head->next;  // 更新头节点
    }

    free(old_head);
    list->size--;
}

/**
 * 尾删法：删除尾部节点
 * 核心：删除后新尾的next指向头（保持闭环）
 */
static void pop_back(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // 空链表，直接返回
        return;
    }

    Node* old_tail = list->tail;
    if (list->size == 1) {  // 只剩一个节点：删除后为空链表
        list->head = NULL;
        list->tail = NULL;
    }
    else {  // 多个节点：找到倒数第二个节点（新尾）
        Node* new_tail = list->head;
        while (new_tail->next != old_tail) {  // 终止条件：new_tail的next是原尾
            new_tail = new_tail->next;
        }
        new_tail->next = list->head;  // 新尾next指向头（保持闭环）
        list->tail = new_tail;        // 更新尾节点
    }

    free(old_tail);
    list->size--;
}

/**
 * 删除指定索引的节点
 * 核心：删除后若涉及头/尾，需修复闭环
 */
static void erase(size_t index, List* list) {
    CHECK_LIST(list);
    if (index >= list->size) {  // 索引越界
        fprintf(stderr, "Error: index %zu out of range (size: %zu)\n", index, list->size);
        return;
    }

    // 直接复用头删/尾删逻辑（已处理闭环）
    if (index == 0) {
        pop_front(list);
        return;
    }
    if (index == list->size - 1) {
        pop_back(list);
        return;
    }

    // 删除中间节点：找到待删节点的前一个节点
    Node* prev = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }
    Node* to_delete = prev->next;
    prev->next = to_delete->next;  // 跳过待删节点

    free(to_delete);
    list->size--;
}

/**
 * 获取指定索引的元素
 * 核心：用索引控制遍历次数（避免无限循环），返回INT_MIN标记错误
 */
static object at(size_t index, List* list) {
    CHECK_LIST(list);
    if (index >= list->size) {  // 索引越界
        fprintf(stderr, "Error: index %zu out of range (size: %zu)\n", index, list->size);
        return INT_MIN;  // object是int，用INT_MIN标记错误
    }

    Node* curr = list->head;
    for (size_t i = 0; i < index; ++i) {  // 按索引遍历，无需依赖NULL
        curr = curr->next;
    }
    return curr->data;
}

/**
 * 在指定索引插入节点
 * 核心：插入后若涉及头/尾，需修复闭环
 */
static void insert(size_t index, object data, List* list) {
    CHECK_LIST(list);
    if (index > list->size) {  // 索引越界（允许index=size，即尾插）
        fprintf(stderr, "Error: index %zu out of range (size: %zu)\n", index, list->size);
        return;
    }

    // 直接复用头插/尾插逻辑（已处理闭环）
    if (index == 0) {
        push_front(data, list);
        return;
    }
    if (index == list->size) {
        push_back(data, list);
        return;
    }

    // 插入中间节点：找到插入位置的前一个节点
    Node* prev = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }
    // 新节点next指向prev的next，prev的next指向新节点
    prev->next = new_node(data, prev->next);

    list->size++;
}
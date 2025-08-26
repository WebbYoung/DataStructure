#pragma once
#include<stdio.h>
#include <stdlib.h>
#define object int
#define CHECK_LIST(list) if (list == NULL) return;

#define CHECK_MEMORY(node) if (node == NULL) {\
printf("Memory allocation error!");\
return NULL;\
    }
typedef struct CListNode {
    object data;
    struct CListNode* next;
    struct CListNode* prev;
}Node;
typedef struct CList {
    Node* head;
    Node* tail;
    size_t size;
}List;
//初始化链表
static void initialize_CList(List* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
//创建新节点
static Node* new_node(object data, Node* prev,Node*next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    CHECK_MEMORY(newNode);
    newNode->data = data;
    newNode->next = next;
    newNode->prev = prev;
    return newNode;
}
//头插法
static void push_front(object data, List* list) {
    CHECK_LIST(list);
    if (list->head == NULL) {
        list->tail = new_node(data, NULL,NULL);
        list->head = list->tail;
        list->size++;
        return;
    }
    Node* old_head = list->head;
    list->head = new_node(data, NULL,list->head);
    old_head->prev = list->head;
    list->size++;
}
//尾插法
static void push_back(object data, List* list) {
    CHECK_LIST(list);
    Node* newNode = new_node(data, list->tail,NULL);
    Node** head = &(list->head);
    Node** tail = &(list->tail);
    if (*head == NULL) {
        *head = newNode;
        *tail = *head;
        list->size++;
        return;
    }
    (*tail)->next = newNode;
    *tail = newNode;
    list->size++;
}
//正向遍历链表
static void traverse(List* list) {
    CHECK_LIST(list);
    Node* curr = list->head;
    printf("[");
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL)printf(",");
        curr = curr->next;
    }
    printf("]\n");
}
//反向遍历链表

static void reverse_traverse(List* list) {
    CHECK_LIST(list);
    Node* curr = list->tail;
    printf("[");
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->prev != NULL)printf(",");
        curr = curr->prev;
    }
    printf("]\n");
}
//释放链表
static void free_list(List* list) {
    CHECK_LIST(list);
    Node* curr = list->head;
    Node* next_ptr;
    while (curr != NULL) {
        next_ptr = curr->next;
        free(curr);
        curr = next_ptr;
    }
    curr = NULL;
    next_ptr = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

//从头部删除元素
static void pop_front(List* list) {
    CHECK_LIST(list);
    if (list->head == NULL)return;
    Node* next = list->head->next;
    free(list->head);
    list->head = next;
    list->head->prev = NULL;
    list->size--;
}
//从尾部删除元素
static void pop_back(List* list) {
    CHECK_LIST(list);
    if (list->head == NULL)return;
    Node* last = list->head;
    if (last->next == NULL) {
        free(last);
        list->size = 0;
        return;
    }
    while (last->next->next != NULL) {
        last = last->next;
    }
    free(list->tail);
    last->next = NULL;
    list->tail = last;
    list->size--;
}
//从指定位置删除元素
static void erase(size_t index, List* list) {
    if (index >= list->size) {
        printf("index out of range");
        return;
    }
    if (index == 0) {
        pop_front(list);
        return;
    }
    if (index == list->size - 1) {
        pop_back(list);
        return;
    }
    Node* current = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next;
    }
    Node* to_delete = current->next;
    current->next = to_delete->next;
    to_delete->next->prev = current;
    free(to_delete);
    list->size--;
}
//获取指定位置的元素
static object at(size_t index, List* list) {
    if (index >= list->size) {
        printf("index out of range");
        return NULL;
    }
    Node* current;
    size_t pos;
    if (index < list->size / 2) {
        current = list->head;
        pos = index;
        for (size_t i = 0; i < pos; ++i) {
            current = current->next;
        }
    }
    else {
        current = list->tail;
        pos = list->size - index-1;
        for (size_t i = 0; i < pos; ++i) {
            current = current->prev;
        }
    }
    return current->data;
}
//在指定位置插入元素
static void insert(size_t index, object data, List* list) {
    if (index > list->size) {
        printf("index out of range");
        return;
    }
    if (index == 0) {
        push_front(data, list);
        return;
    }
    if (index == list->size) {
        push_back(data, list);
        return;
    }
    Node* current = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next;
    }
    current->next = new_node(data, current->next,NULL);
    list->size++;
}
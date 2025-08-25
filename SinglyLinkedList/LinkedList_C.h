#pragma once
#include<stdio.h>
#include <stdlib.h>
#define object int
#define CHECK_MEMORY(node) if (node == NULL) {\
printf("Memory allocation error!");\
return NULL;\
    }
typedef struct CListNode {
    object data;
    struct CListNode* next;
}Node;
typedef struct CList {
    Node* head;
    Node* tail;
}List;
static void initialize_CList(List* list) {
    list->head = NULL;
    list->tail = NULL;
}
static Node* new_node(object data, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    CHECK_MEMORY(newNode);
    newNode->data = data;
    newNode->next = next;
    return newNode;
}
static void push_front(object data, List* list) {
    if (list == NULL)return;
    list->head = new_node(data, list->head);
    Node* curr = list->head;
    while (curr->next!=NULL) {
        curr = curr->next;
    }
    list->tail = curr;
}
static void push_back(object data, List* list) {
    if (list == NULL)return;
    Node* newNode = new_node(data, NULL);
    Node** head = &(list->head);
    Node** tail = &(list->tail);
    if (*head == NULL) {
        *head = newNode;
        *tail = *head;
        return;
    }
    (*tail)->next = newNode;
    *tail = newNode;
}
static void traverse(List* list) {
    if (list == NULL || list->head == NULL)return;
    Node* curr = list->head;
    printf("[");
    while (curr!= NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL)printf(",");
        curr = curr->next;
    }
    printf("]\n");
}
static void free_list(List* list) {
    if (list == NULL||list->head==NULL)return;
    Node* curr=list->head;
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
}
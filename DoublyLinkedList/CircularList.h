#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // ����INT_MIN��Ǵ���objectΪint��

#define object int
// ��������Ƿ�ΪNULL���޷���ֵ�����ã�
#define CHECK_LIST(list) if (list == NULL) return;
// ����ڴ���䣨�з���ֵ�����ã�����NULL��
#define CHECK_MEMORY(node) if (node == NULL) {\
    fprintf(stderr, "Memory allocation error!\n");\
    return NULL;\
}

// ѭ������ڵ�
typedef struct CircularNode {
    object data;
    struct CircularNode* next;  // �ǿ�ʱ��β�ڵ��nextָ��ͷ�ڵ�
} Node;

// ѭ������ṹ
typedef struct CList {
    Node* head;   // ͷ�ڵ�
    Node* tail;   // β�ڵ㣨�Ż�β��/βɾЧ�ʣ�
    size_t size;  // �ڵ�����
} List;

/**
 * ��ʼ��ѭ������
 * ������head = tail = NULL��size = 0
 */
static void initialize_CList(List* list) {
    CHECK_LIST(list);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * �����½ڵ�
 * @param data���ڵ�����
 * @param next���ڵ��nextָ�루ѭ�����������ֶ�ά���ջ���
 * @return �½ڵ��ַ���ڴ����ʧ�ܷ���NULL��
 */
static Node* new_node(object data, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    CHECK_MEMORY(newNode);
    newNode->data = data;
    newNode->next = next;
    return newNode;
}

/**
 * ͷ�巨��������ͷ������ڵ�
 * ���ģ��½ڵ��Ϊ��ͷ��β�ڵ��nextָ����ͷ�����ֱջ���
 */
static void push_front(object data, List* list) {
    CHECK_LIST(list);
    Node* newNode = new_node(data, list->head);  // �½ڵ�nextָ��ԭͷ

    if (list->size == 0) {  // �������½ڵ��Աջ���nextָ������
        newNode->next = newNode;
        list->tail = newNode;  // β�ڵ�Ҳָ���½ڵ�
    }
    else {  // �ǿ�����β�ڵ�nextָ����ͷ�����ֱջ���
        list->tail->next = newNode;
    }

    list->head = newNode;  // ����ͷ�ڵ�
    list->size++;
}

/**
 * β�巨��������β������ڵ�
 * ���ģ��½ڵ��Ϊ��β����β��nextָ��ͷ�����ֱջ���
 */
static void push_back(object data, List* list) {
    CHECK_LIST(list);
    Node* newNode = new_node(data, list->head);  // �½ڵ�nextֱ��ָ��ͷ����ǰ�ջ���

    if (list->size == 0) {  // �������½ڵ��Աջ���ͷ/β��ָ����
        newNode->next = newNode;
        list->head = newNode;
    }
    else {  // �ǿ�����ԭβ�ڵ�nextָ���½ڵ�
        list->tail->next = newNode;
    }

    list->tail = newNode;  // ����β�ڵ�
    list->size++;
}

/**
 * ����ѭ������
 * ���ģ���ֹ����Ϊ��curr->next == head����������β�ڵ㣩����������ѭ��
 */
static void traverse(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // ������
        printf("[]\n");
        return;
    }

    Node* curr = list->head;
    printf("[");
    do {  // �ȴ�ӡ��ǰ�ڵ㣬���ж��Ƿ���ֹ���������ڵ�������
        printf("%d", curr->data);
        curr = curr->next;
        if (curr != list->head) {  // ����β�ڵ㣬�ӷָ���
            printf(", ");
        }
    } while (curr != list->head);  // ��ֹ�������ص�ͷ�ڵ�

    printf("]\n");
}

/**
 * �ͷ�ѭ�������ڴ�
 * ���ģ��ȶϿ��ջ���β�ڵ�next��ΪNULL�����ٰ����������ͷţ���������ѭ��
 */
static void free_list(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // ������ֱ�����״̬
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    // 1. �Ͽ��ջ���β�ڵ�next��ΪNULL�������������ѭ����
    list->tail->next = NULL;

    // 2. �����������ͷ����нڵ�
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next_ptr = curr->next;
        free(curr);
        curr = next_ptr;
    }

    // 3. �������״̬
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * ��תѭ������
 * ���ģ���ת����β��ԭͷ����nextָ����ͷ�����ֱջ���
 */
static void reverse_list(List* list) {
    CHECK_LIST(list);
    if (list->size <= 1) {  // ������򵥸��ڵ㣬���跴ת
        return;
    }

    Node* prev = NULL;
    Node* curr = list->head;
    Node* next = NULL;
    Node* old_head = list->head;  // ԭͷ�ڵ㣨��ת���Ϊ��β��
    Node* old_tail = list->tail;  // ԭβ�ڵ㣨��ת���Ϊ��ͷ��

    // ��תָ�루ͬ��������������������ջ���
    do {
        next = curr->next;  // ������һ���ڵ�
        curr->next = prev;  // ��ת��ǰ�ڵ��next
        prev = curr;        // prev�ƶ�����ǰ�ڵ�
        curr = next;        // curr�ƶ�����һ���ڵ�
    } while (curr != list->head);  // ���������нڵ㣨�ص�ԭͷ��

    // �޸��ջ�����β��ԭͷ����nextָ����ͷ��ԭβ��
    old_head->next = old_tail;

    // ����ͷ��β�ڵ�
    list->head = old_tail;
    list->tail = old_head;
}

/**
 * ͷɾ����ɾ��ͷ���ڵ�
 * ���ģ�ɾ������ͷ��next��β�ڵ�ָ�򣨱��ֱջ���
 */
static void pop_front(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // ������ֱ�ӷ���
        return;
    }

    Node* old_head = list->head;
    if (list->size == 1) {  // ֻʣһ���ڵ㣺ɾ����Ϊ������
        list->head = NULL;
        list->tail = NULL;
    }
    else {  // ����ڵ㣺β�ڵ�nextָ����ͷ��ԭͷ��next��
        list->tail->next = old_head->next;
        list->head = old_head->next;  // ����ͷ�ڵ�
    }

    free(old_head);
    list->size--;
}

/**
 * βɾ����ɾ��β���ڵ�
 * ���ģ�ɾ������β��nextָ��ͷ�����ֱջ���
 */
static void pop_back(List* list) {
    CHECK_LIST(list);
    if (list->size == 0) {  // ������ֱ�ӷ���
        return;
    }

    Node* old_tail = list->tail;
    if (list->size == 1) {  // ֻʣһ���ڵ㣺ɾ����Ϊ������
        list->head = NULL;
        list->tail = NULL;
    }
    else {  // ����ڵ㣺�ҵ������ڶ����ڵ㣨��β��
        Node* new_tail = list->head;
        while (new_tail->next != old_tail) {  // ��ֹ������new_tail��next��ԭβ
            new_tail = new_tail->next;
        }
        new_tail->next = list->head;  // ��βnextָ��ͷ�����ֱջ���
        list->tail = new_tail;        // ����β�ڵ�
    }

    free(old_tail);
    list->size--;
}

/**
 * ɾ��ָ�������Ľڵ�
 * ���ģ�ɾ�������漰ͷ/β�����޸��ջ�
 */
static void erase(size_t index, List* list) {
    CHECK_LIST(list);
    if (index >= list->size) {  // ����Խ��
        fprintf(stderr, "Error: index %zu out of range (size: %zu)\n", index, list->size);
        return;
    }

    // ֱ�Ӹ���ͷɾ/βɾ�߼����Ѵ���ջ���
    if (index == 0) {
        pop_front(list);
        return;
    }
    if (index == list->size - 1) {
        pop_back(list);
        return;
    }

    // ɾ���м�ڵ㣺�ҵ���ɾ�ڵ��ǰһ���ڵ�
    Node* prev = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }
    Node* to_delete = prev->next;
    prev->next = to_delete->next;  // ������ɾ�ڵ�

    free(to_delete);
    list->size--;
}

/**
 * ��ȡָ��������Ԫ��
 * ���ģ����������Ʊ�����������������ѭ����������INT_MIN��Ǵ���
 */
static object at(size_t index, List* list) {
    CHECK_LIST(list);
    if (index >= list->size) {  // ����Խ��
        fprintf(stderr, "Error: index %zu out of range (size: %zu)\n", index, list->size);
        return INT_MIN;  // object��int����INT_MIN��Ǵ���
    }

    Node* curr = list->head;
    for (size_t i = 0; i < index; ++i) {  // ��������������������NULL
        curr = curr->next;
    }
    return curr->data;
}

/**
 * ��ָ����������ڵ�
 * ���ģ���������漰ͷ/β�����޸��ջ�
 */
static void insert(size_t index, object data, List* list) {
    CHECK_LIST(list);
    if (index > list->size) {  // ����Խ�磨����index=size����β�壩
        fprintf(stderr, "Error: index %zu out of range (size: %zu)\n", index, list->size);
        return;
    }

    // ֱ�Ӹ���ͷ��/β���߼����Ѵ���ջ���
    if (index == 0) {
        push_front(data, list);
        return;
    }
    if (index == list->size) {
        push_back(data, list);
        return;
    }

    // �����м�ڵ㣺�ҵ�����λ�õ�ǰһ���ڵ�
    Node* prev = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }
    // �½ڵ�nextָ��prev��next��prev��nextָ���½ڵ�
    prev->next = new_node(data, prev->next);

    list->size++;
}
#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "DoublyNode.h"

template<typename T>
class DoublyLinkedList
{
    using List = DoublyLinkedList<T>;
    using Node = DoubleNode<T>;
public:
    // 拷贝构造函数
    DoublyLinkedList(const List& list);

    // 默认构造函数
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // 头插法
    void push_front(const T& data);

    // 尾插法
    void push_back(const T& data);

    // 从头部删除元素
    void pop_front();

    // 从尾部删除元素
    void pop_back();

    // 从指定位置删除元素
    void erase(size_t index);

    // 从指定位置插入元素
    void insert(size_t index, const T& data);

    // 从指定位置插入链表
    void insert_range(size_t index, List& list);

    // 交换两个链表
    void swap(List& list);

    // 清空链表
    void clear();

    // 遍历链表
    void traverse() const;

    // 反转链表
    void reverse();

    // 获取链表大小
    size_t getsize() const;

    // 拼接链表
    void append_range(List& list);

    // 拼接链表（重载+=）
    void operator+=(List& list);

    // 获取指定位置的元素
    const T& at(size_t index) const;

    // 重载[]运算符
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // 重载赋值运算符
    List& operator=(const List& other);

    // 析构函数
    ~DoublyLinkedList();

private:
    Node* head;  // 头节点指针
    Node* tail;  // 尾节点指针，双向链表新增
    size_t size; // 链表大小
};

// 拷贝构造函数
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const List& list) : head(nullptr), tail(nullptr), size(0)
{
    Node* current = list.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

// 头插法
template<typename T>
void DoublyLinkedList<T>::push_front(const T& data)
{
    try {
        Node* newNode = new Node(data, nullptr, head);
        if (head) {
            head->prev = newNode;
        }
        else {
            // 如果链表为空，新节点既是头也是尾
            tail = newNode;
        }
        head = newNode;
        size++;
    }
    catch (const std::bad_alloc&) {
        throw std::runtime_error("Memory allocation failed");
    }
}

// 尾插法
template<typename T>
void DoublyLinkedList<T>::push_back(const T& data)
{
    try {
        Node* newNode = new Node(data, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        }
        else {
            // 如果链表为空，新节点既是头也是尾
            head = newNode;
        }
        tail = newNode;
        size++;
    }
    catch (const std::bad_alloc&) {
        throw std::runtime_error("Memory allocation failed");
    }
}

// 从头部删除元素
template<typename T>
void DoublyLinkedList<T>::pop_front()
{
    if (!head) {
        throw std::runtime_error("List is empty");
    }

    Node* temp = head;
    head = head->next;

    if (head) {
        head->prev = nullptr;
    }
    else {
        // 如果链表变为空，尾指针也置空
        tail = nullptr;
    }

    delete temp;
    size--;
}

// 从尾部删除元素
template<typename T>
void DoublyLinkedList<T>::pop_back()
{
    if (!tail) {
        throw std::runtime_error("List is empty");
    }

    Node* temp = tail;
    tail = tail->prev;

    if (tail) {
        tail->next = nullptr;
    }
    else {
        // 如果链表变为空，头指针也置空
        head = nullptr;
    }

    delete temp;
    size--;
}

// 从指定位置删除元素
template<typename T>
void DoublyLinkedList<T>::erase(size_t index)
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    // 优化：根据索引位置决定从头部还是尾部开始遍历
    Node* current;
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    }
    else {
        current = tail;
        for (size_t i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }

    // 处理前驱节点
    if (current->prev) {
        current->prev->next = current->next;
    }
    else {
        // 删除的是头节点
        head = current->next;
    }

    // 处理后继节点
    if (current->next) {
        current->next->prev = current->prev;
    }
    else {
        // 删除的是尾节点
        tail = current->prev;
    }

    delete current;
    size--;
}

// 从指定位置插入元素
template<typename T>
void DoublyLinkedList<T>::insert(size_t index, const T& data)
{
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        push_front(data);
        return;
    }

    if (index == size) {
        push_back(data);
        return;
    }

    try {
        // 找到插入位置的节点
        Node* current;
        if (index < size / 2) {
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        }
        else {
            current = tail;
            for (size_t i = size - 1; i > index; --i) {
                current = current->prev;
            }
        }
    }
    catch (const std::bad_alloc&) {
        throw std::runtime_error("Memory allocation failed");
    }
    // 创建新节点
    Node* newNode = new Node(data, current->prev, current);

    // 更新前驱节点的next指针
    current->prev->next = newNode;

    // 更新当前节点的prev指针
    current->prev = newNode;

    size++;
}


// 从指定位置插入链表
template<typename T>
void DoublyLinkedList<T>::insert_range(size_t index, List& list)
{
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (list.size == 0) return; // 如果插入的链表为空，直接返回

    // 创建要插入的链表的副本，避免所有权问题
    List tempList(list);

    if (size == 0) {
        // 如果当前链表为空
        head = tempList.head;
        tail = tempList.tail;
        size = tempList.size;

        // 防止临时链表析构时删除节点
        tempList.head = nullptr;
        tempList.tail = nullptr;
        tempList.size = 0;
        return;
    }

    if (index == 0) {
        // 插入到头部
        tempList.tail->next = head;
        head->prev = tempList.tail;
        head = tempList.head;
    }
    else if (index == size) {
        // 插入到尾部
        tail->next = tempList.head;
        tempList.head->prev = tail;
        tail = tempList.tail;
    }
    else {
        // 插入到中间
        Node* current;
        if (index < size / 2) {
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        }
        else {
            current = tail;
            for (size_t i = size - 1; i > index; --i) {
                current = current->prev;
            }
        }

        tempList.head->prev = current->prev;
        tempList.tail->next = current;

        if (current->prev) {
            current->prev->next = tempList.head;
        }
        current->prev = tempList.tail;
    }

    size += tempList.size;

    // 防止临时链表析构时删除节点
    tempList.head = nullptr;
    tempList.tail = nullptr;
    tempList.size = 0;
}

// 交换两个链表
template<typename T>
void DoublyLinkedList<T>::swap(List& list)
{
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
}

// 清空链表
template<typename T>
void DoublyLinkedList<T>::clear()
{
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// 遍历链表
template<typename T>
void DoublyLinkedList<T>::traverse() const
{
    Node* current = head;
    std::cout << "[";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next) std::cout << ",";
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

// 反转链表（双向链表反转更简单高效）
template<typename T>
void DoublyLinkedList<T>::reverse()
{
    // 交换头指针和尾指针
    std::swap(head, tail);

    Node* current = head;
    while (current) {
        // 交换每个节点的prev和next指针
        std::swap(current->prev, current->next);
        current = current->next; // 注意：这里因为prev和next已交换，实际是移动到原来的prev
    }
}

// 获取链表大小
template<typename T>
size_t DoublyLinkedList<T>::getsize() const
{
    return size;
}

// 拼接链表
template<typename T>
void DoublyLinkedList<T>::append_range(List& list)
{
    if (list.size == 0) return;

    List tempList(list);

    if (size == 0) {
        head = tempList.head;
        tail = tempList.tail;
    }
    else {
        tail->next = tempList.head;
        tempList.head->prev = tail;
        tail = tempList.tail;
    }

    size += tempList.size;

    // 防止临时链表析构时删除节点
    tempList.head = nullptr;
    tempList.tail = nullptr;
    tempList.size = 0;
}

// 拼接链表（重载+=）
template<typename T>
void DoublyLinkedList<T>::operator+=(List& list)
{
    append_range(list);
}

// 获取指定位置的元素
template<typename T>
const T& DoublyLinkedList<T>::at(size_t index) const
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current;
    // 优化：根据索引位置决定从头部还是尾部开始遍历
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    }
    else {
        current = tail;
        for (size_t i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }

    return current->data;
}

// 重载[]运算符（非const版本）
template<typename T>
T& DoublyLinkedList<T>::operator[](size_t index)
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current;
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    }
    else {
        current = tail;
        for (size_t i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }

    return current->data;
}

// 重载[]运算符（const版本）
template<typename T>
const T& DoublyLinkedList<T>::operator[](size_t index) const
{
    return const_cast<List*>(this)->operator[](index);
}

// 重载赋值运算符
template<typename T>
typename DoublyLinkedList<T>::List& DoublyLinkedList<T>::operator=(const List& other)
{
    if (this == &other)
        return *this;

    clear();

    Node* cur = other.head;
    while (cur != nullptr) {
        push_back(cur->data);
        cur = cur->next;
    }

    return *this;
}

// 析构函数
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

// 重载<<运算符
template<typename T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list)
{
    list.traverse();
    return os;
}

// 重载+运算符
template<typename T>
DoublyLinkedList<T> operator+(const DoublyLinkedList<T>& list1, const DoublyLinkedList<T>& list2)
{
    DoublyLinkedList<T> result(list1);
    result += const_cast<DoublyLinkedList<T>&>(list2);
    return result;
}

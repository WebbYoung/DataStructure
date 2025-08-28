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
    // �������캯��
    DoublyLinkedList(const List& list);

    // Ĭ�Ϲ��캯��
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // ͷ�巨
    void push_front(const T& data);

    // β�巨
    void push_back(const T& data);

    // ��ͷ��ɾ��Ԫ��
    void pop_front();

    // ��β��ɾ��Ԫ��
    void pop_back();

    // ��ָ��λ��ɾ��Ԫ��
    void erase(size_t index);

    // ��ָ��λ�ò���Ԫ��
    void insert(size_t index, const T& data);

    // ��ָ��λ�ò�������
    void insert_range(size_t index, List& list);

    // ������������
    void swap(List& list);

    // �������
    void clear();

    // ��������
    void traverse() const;

    // ��ת����
    void reverse();

    // ��ȡ�����С
    size_t getsize() const;

    // ƴ������
    void append_range(List& list);

    // ƴ����������+=��
    void operator+=(List& list);

    // ��ȡָ��λ�õ�Ԫ��
    const T& at(size_t index) const;

    // ����[]�����
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // ���ظ�ֵ�����
    List& operator=(const List& other);

    // ��������
    ~DoublyLinkedList();

private:
    Node* head;  // ͷ�ڵ�ָ��
    Node* tail;  // β�ڵ�ָ�룬˫����������
    size_t size; // �����С
};

// �������캯��
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const List& list) : head(nullptr), tail(nullptr), size(0)
{
    Node* current = list.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

// ͷ�巨
template<typename T>
void DoublyLinkedList<T>::push_front(const T& data)
{
    try {
        Node* newNode = new Node(data, nullptr, head);
        if (head) {
            head->prev = newNode;
        }
        else {
            // �������Ϊ�գ��½ڵ����ͷҲ��β
            tail = newNode;
        }
        head = newNode;
        size++;
    }
    catch (const std::bad_alloc&) {
        throw std::runtime_error("Memory allocation failed");
    }
}

// β�巨
template<typename T>
void DoublyLinkedList<T>::push_back(const T& data)
{
    try {
        Node* newNode = new Node(data, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        }
        else {
            // �������Ϊ�գ��½ڵ����ͷҲ��β
            head = newNode;
        }
        tail = newNode;
        size++;
    }
    catch (const std::bad_alloc&) {
        throw std::runtime_error("Memory allocation failed");
    }
}

// ��ͷ��ɾ��Ԫ��
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
        // ��������Ϊ�գ�βָ��Ҳ�ÿ�
        tail = nullptr;
    }

    delete temp;
    size--;
}

// ��β��ɾ��Ԫ��
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
        // ��������Ϊ�գ�ͷָ��Ҳ�ÿ�
        head = nullptr;
    }

    delete temp;
    size--;
}

// ��ָ��λ��ɾ��Ԫ��
template<typename T>
void DoublyLinkedList<T>::erase(size_t index)
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    // �Ż�����������λ�þ�����ͷ������β����ʼ����
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

    // ����ǰ���ڵ�
    if (current->prev) {
        current->prev->next = current->next;
    }
    else {
        // ɾ������ͷ�ڵ�
        head = current->next;
    }

    // �����̽ڵ�
    if (current->next) {
        current->next->prev = current->prev;
    }
    else {
        // ɾ������β�ڵ�
        tail = current->prev;
    }

    delete current;
    size--;
}

// ��ָ��λ�ò���Ԫ��
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
        // �ҵ�����λ�õĽڵ�
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
    // �����½ڵ�
    Node* newNode = new Node(data, current->prev, current);

    // ����ǰ���ڵ��nextָ��
    current->prev->next = newNode;

    // ���µ�ǰ�ڵ��prevָ��
    current->prev = newNode;

    size++;
}


// ��ָ��λ�ò�������
template<typename T>
void DoublyLinkedList<T>::insert_range(size_t index, List& list)
{
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (list.size == 0) return; // ������������Ϊ�գ�ֱ�ӷ���

    // ����Ҫ���������ĸ�������������Ȩ����
    List tempList(list);

    if (size == 0) {
        // �����ǰ����Ϊ��
        head = tempList.head;
        tail = tempList.tail;
        size = tempList.size;

        // ��ֹ��ʱ��������ʱɾ���ڵ�
        tempList.head = nullptr;
        tempList.tail = nullptr;
        tempList.size = 0;
        return;
    }

    if (index == 0) {
        // ���뵽ͷ��
        tempList.tail->next = head;
        head->prev = tempList.tail;
        head = tempList.head;
    }
    else if (index == size) {
        // ���뵽β��
        tail->next = tempList.head;
        tempList.head->prev = tail;
        tail = tempList.tail;
    }
    else {
        // ���뵽�м�
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

    // ��ֹ��ʱ��������ʱɾ���ڵ�
    tempList.head = nullptr;
    tempList.tail = nullptr;
    tempList.size = 0;
}

// ������������
template<typename T>
void DoublyLinkedList<T>::swap(List& list)
{
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
}

// �������
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

// ��������
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

// ��ת����˫������ת���򵥸�Ч��
template<typename T>
void DoublyLinkedList<T>::reverse()
{
    // ����ͷָ���βָ��
    std::swap(head, tail);

    Node* current = head;
    while (current) {
        // ����ÿ���ڵ��prev��nextָ��
        std::swap(current->prev, current->next);
        current = current->next; // ע�⣺������Ϊprev��next�ѽ�����ʵ�����ƶ���ԭ����prev
    }
}

// ��ȡ�����С
template<typename T>
size_t DoublyLinkedList<T>::getsize() const
{
    return size;
}

// ƴ������
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

    // ��ֹ��ʱ��������ʱɾ���ڵ�
    tempList.head = nullptr;
    tempList.tail = nullptr;
    tempList.size = 0;
}

// ƴ����������+=��
template<typename T>
void DoublyLinkedList<T>::operator+=(List& list)
{
    append_range(list);
}

// ��ȡָ��λ�õ�Ԫ��
template<typename T>
const T& DoublyLinkedList<T>::at(size_t index) const
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current;
    // �Ż�����������λ�þ�����ͷ������β����ʼ����
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

// ����[]���������const�汾��
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

// ����[]�������const�汾��
template<typename T>
const T& DoublyLinkedList<T>::operator[](size_t index) const
{
    return const_cast<List*>(this)->operator[](index);
}

// ���ظ�ֵ�����
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

// ��������
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

// ����<<�����
template<typename T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list)
{
    list.traverse();
    return os;
}

// ����+�����
template<typename T>
DoublyLinkedList<T> operator+(const DoublyLinkedList<T>& list1, const DoublyLinkedList<T>& list2)
{
    DoublyLinkedList<T> result(list1);
    result += const_cast<DoublyLinkedList<T>&>(list2);
    return result;
}

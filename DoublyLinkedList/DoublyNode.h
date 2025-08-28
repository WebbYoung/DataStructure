#pragma once
template<typename T>
class DoublyLinkedList_CPP;
template<typename T>
class DoubleNode
{
    friend class DoublyLinkedList_CPP<T>;
public:
    T data;
    DoubleNode* prev;  // ָ��ǰһ���ڵ�
    DoubleNode* next;  // ָ���һ���ڵ�

    // ���캯��
    DoubleNode(const T& data, DoubleNode* prev = nullptr, DoubleNode* next = nullptr)
        : data(data), prev(prev), next(next) {
    }
};

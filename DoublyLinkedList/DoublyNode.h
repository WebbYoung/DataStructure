#pragma once
template<typename T>
class DoublyLinkedList_CPP;
template<typename T>
class DoubleNode
{
    friend class DoublyLinkedList_CPP<T>;
public:
    T data;
    DoubleNode* prev;  // 指向前一个节点
    DoubleNode* next;  // 指向后一个节点

    // 构造函数
    DoubleNode(const T& data, DoubleNode* prev = nullptr, DoubleNode* next = nullptr)
        : data(data), prev(prev), next(next) {
    }
};

#pragma once

//泛型单向链表(非智能指针)C++实现

#include <iostream>
#include <stdexcept>
#include "SingleNode.h"
template<typename T>
class LinkedList
{
	using List = LinkedList<T>;
	using Node = SingleNode<T>;
public:
	
	LinkedList(const List& list);//拷贝构造函数
	LinkedList() :head(nullptr), size(0) {}//默认构造函数
	void push_front(const T& data);//头插法
	void push_back(const T& data);//尾插法
	void pop_front();//从头部删除元素
	void pop_back();//从尾部删除元素
	void erase(size_t index);//从指定位置删除元素
	void insert(size_t index, const T& data); //从指定位置插入元素
	void insert_range(size_t index, List& list);//从指定位置插入链表
	void swap(List& list);//交换两个链表
	void clear();//清空链表
	void traverse();//遍历链表
	void reverse();//反转链表
	size_t getsize()const;
	void append_range(List& list);//拼接链表
	void operator+=(List& list);//拼接链表（重载+=）
	const T& at(size_t index)const;//获取指定位置的元素
	T& operator[](size_t index) const;//重载[]运算符
	LinkedList& operator=(List& other);//重载赋值运算符
	~LinkedList();
private:
	Node* head;
	size_t size;
};

template<typename T>
inline void LinkedList<T>::push_front(const T& data)
{
	try {
		head = new Node(data, head);
		size++;
	}
	catch (const std::bad_alloc&) {
		throw std::runtime_error("Memory allocation failed");
	}
}

template<typename T>
void LinkedList<T>::push_back(const T& data)
{
	try {
		if (!head) {
			head = new Node(data, nullptr);
			size++;
			return;
		}
		Node* current = head;
		while (current->next) {
			current = current->next;
		}
		current->next = new Node(data, nullptr);
		size++;
	}
	catch (const std::bad_alloc&) {
		throw std::runtime_error("Memory allocation failed");
	}
}

template<typename T>
inline void LinkedList<T>::pop_front()
{
	if (!head) {
		throw std::runtime_error("List is empty");
	}
	Node* temp = head;
	head = head->next;
	delete temp;
	size--;
	if (size == 0) {
		head = nullptr; // 如果链表变为空，重置头指针
	}
}

template<typename T>
inline void LinkedList<T>::pop_back()
{
	if (!head) {
		throw std::runtime_error("List is empty");
	}
	Node* current = head;
	if (current->next == nullptr) {
		delete current; // 删除头节点
		head = nullptr; // 头指针置空
		size--;
		return;
	}
	while (current->next && current->next->next) {
		current = current->next;
	}
	delete current->next; // 删除尾节点
	current->next = nullptr; // 尾节点置空
	size--;
}

template<typename T>
inline void LinkedList<T>::erase(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}
	if (index == 0) {
		pop_front();
		return;
	}
	if (index == size - 1) {
		pop_back();
		return;
	}
	Node* current = head;
	for (size_t i = 0; i < index - 1; ++i) {
		current = current->next;
	}
	Node* to_delete = current->next;
	current->next = to_delete->next;
	delete to_delete;
	size--;
}

template<typename T>
inline void LinkedList<T>::insert(size_t index, const T& data)
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
		Node* current = head;
		for (size_t i = 0; i < index - 1; ++i) {
			current = current->next;
		}
		current->next = new Node(data, current->next);
		size++;
	}
	catch (const std::bad_alloc&) {
		throw std::runtime_error("Memory allocation failed");
	}
}

template<typename T>
inline void LinkedList<T>::insert_range(size_t index, List& list)
{
	if (index > size) {
		throw std::out_of_range("Index out of range");
	}
	if (list.size == 0) return; // 如果插入的链表为空，直接返回
	if (index == 0) {
		Node* new_head = list.head;
		Node* tail = new_head;
		while (tail->next) {
			tail = tail->next;
		}
		tail->next = head; // 将原链表接到新链表的尾部
		head = new_head; // 更新头指针
		size += list.size;
		return;
	}
	if (index == size) {
		append_range(list);
		return;
	}
	Node* current = head;
	for (size_t i = 0; i < index - 1; ++i) {
		current = current->next;
	}
	Node* new_head = list.head;
	Node* tail = new_head;
	while (tail->next) {
		tail = tail->next;
	}
	tail->next = current->next; // 将新链表的尾部连接到当前节点的下一个节点
	current->next = new_head; // 将当前节点的下一个节点指向新链表的头
	size += list.size;
}

template<typename T>
inline void LinkedList<T>::swap(List& list)
{
	std::swap(this->head, list.head);
	std::swap(this->size, list.size);
}

template<typename T>
inline void LinkedList<T>::clear()
{
	if (head == nullptr)return;
	Node* current = head;
	while (current) {
		head = current->next;
		delete current;
		current = head;
	}
}

template<typename T>
void LinkedList<T>::traverse()
{
	Node* current = head;
	std::cout << "[";
	while (current!=nullptr) {
		std::cout << current->data;
		if (current->next)std::cout << ",";
		current = current->next;
	}
	std::cout << "]" << std::endl;
}

template<typename T>
inline void LinkedList<T>::reverse()
{
	if (!head || !head->next) return;
	Node* prev = nullptr;
	Node* current = head;
	Node* next = nullptr;
	while (current) {
		next = current->next;
		current -> next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}

template<typename T>
inline size_t LinkedList<T>::getsize() const
{
	return size;
}



template<typename T>
inline void LinkedList<T>::append_range(List& list)
{
	if (!list.size)return;
	if (!size) {
		*this = list;
		return;
	}
	List* newlist=new List(list);
	Node* last = head;
	while (last->next) {
		last = last->next;
	}
	last->next = newlist->head;
	size += newlist->size;
}

template<typename T>
inline void LinkedList<T>::operator+=(List& list)
{
	append_range(list);
}

template<typename T>
inline const T& LinkedList<T>::at(size_t index) const
{
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}
	Node* current = head;
	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template<typename T>
inline T& LinkedList<T>::operator[](size_t index) const
{
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}
	Node* current = head;
	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(List& other)
{
	if (&other == this)
		return *this; 
	clear();
	Node* cur = other.head; // 遍历other的节点
	while (cur != nullptr) {
		this->push_back(cur->data); // 将other的每个元素添加到当前对象
		cur = cur->next;
	}
	return *this;
}

//重载<<运算符
template<typename T>
inline std::ostream& operator<<(std::ostream& os,LinkedList<T>& list)
{
	list.traverse();
	return os;
}

//重载+运算符
template<typename T>
LinkedList<T>& operator+(LinkedList<T>& list1, LinkedList<T>& list2)
{
	LinkedList<T>* result=new LinkedList<T>();
	result->append_range(list1);
	result->append_range(list2);
	return *result;
}

template<typename T>
LinkedList<T>::LinkedList(const List& list) {
	Node* current = list.head;
	while (current) {
		push_back(current->data);
		current = current->next;
	}
}


template<typename T>
inline LinkedList<T>::~LinkedList()
{
	clear();
	head = nullptr;
	size = 0;
}




#pragma once

//���͵�������(������ָ��)C++ʵ��

#include <iostream>
#include <stdexcept>
#include "SingleNode.h"
template<typename T>
class LinkedList
{
	using List = LinkedList<T>;
	using Node = SingleNode<T>;
public:
	
	LinkedList(const List& list);//�������캯��
	LinkedList() :head(nullptr), size(0) {}//Ĭ�Ϲ��캯��
	void push_front(const T& data);//ͷ�巨
	void push_back(const T& data);//β�巨
	void pop_front();//��ͷ��ɾ��Ԫ��
	void pop_back();//��β��ɾ��Ԫ��
	void erase(size_t index);//��ָ��λ��ɾ��Ԫ��
	void insert(size_t index, const T& data); //��ָ��λ�ò���Ԫ��
	void insert_range(size_t index, List& list);//��ָ��λ�ò�������
	void swap(List& list);//������������
	void clear();//�������
	void traverse();//��������
	void reverse();//��ת����
	size_t getsize()const;
	void append_range(List& list);//ƴ������
	void operator+=(List& list);//ƴ����������+=��
	const T& at(size_t index)const;//��ȡָ��λ�õ�Ԫ��
	T& operator[](size_t index) const;//����[]�����
	LinkedList& operator=(List& other);//���ظ�ֵ�����
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
		head = nullptr; // ��������Ϊ�գ�����ͷָ��
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
		delete current; // ɾ��ͷ�ڵ�
		head = nullptr; // ͷָ���ÿ�
		size--;
		return;
	}
	while (current->next && current->next->next) {
		current = current->next;
	}
	delete current->next; // ɾ��β�ڵ�
	current->next = nullptr; // β�ڵ��ÿ�
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
	if (list.size == 0) return; // ������������Ϊ�գ�ֱ�ӷ���
	if (index == 0) {
		Node* new_head = list.head;
		Node* tail = new_head;
		while (tail->next) {
			tail = tail->next;
		}
		tail->next = head; // ��ԭ����ӵ��������β��
		head = new_head; // ����ͷָ��
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
	tail->next = current->next; // ���������β�����ӵ���ǰ�ڵ����һ���ڵ�
	current->next = new_head; // ����ǰ�ڵ����һ���ڵ�ָ���������ͷ
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
	Node* cur = other.head; // ����other�Ľڵ�
	while (cur != nullptr) {
		this->push_back(cur->data); // ��other��ÿ��Ԫ����ӵ���ǰ����
		cur = cur->next;
	}
	return *this;
}

//����<<�����
template<typename T>
inline std::ostream& operator<<(std::ostream& os,LinkedList<T>& list)
{
	list.traverse();
	return os;
}

//����+�����
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




#pragma once

//泛型单向链表(智能指针)实现


#include "NodeWithAutoPtr.h"
template<typename T>
class LinkedListWithAutoPtr
{
	using List = LinkedListWithAutoPtr<T>;
	using Node = NodeWithAutoPtr<T>;
public:

	
	LinkedListWithAutoPtr() :head(nullptr), size(0) {}//默认构造函数
	//拷贝构造函数
	LinkedListWithAutoPtr(const List& list) {
		if (list.head == nullptr) {
			head = nullptr;
			size = 0;
			return;
		}
		head = std::make_shared<Node>(list.head->data, nullptr);
		auto current_new = head;
		auto current_old = list.head->next;
		while (current_old != nullptr) {
			current_new->next = std::make_shared<Node>(current_old->data, nullptr);
			current_new = current_new->next;
			current_old = current_old->next;
		}
		size = list.size;
	}
	//重载赋值运算符
	LinkedListWithAutoPtr& operator=(List& other) {
		if (&other == this)
			return *this;
		clear();
		auto cur = other.head; // 遍历other的节点
		while (cur != nullptr) {
			this->push_back(cur->data); // 将other的每个元素添加到当前对象
			cur = cur->next;
		}
		return *this;
	}
	//头插法
	void push_front(const T& data) {
		head = std::make_shared<Node>(data, head);
	}
	//尾插法
	void push_back(const T& data) {
		auto newNode = std::make_shared<Node>(data, nullptr);
		if (head == nullptr) {
			head = newNode;
			size++;
			return;
		}
		auto last = head;
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = newNode;
		size++;
	}
	//从头部删除元素
	void pop_front() {
		if (head == nullptr) {
			throw std::runtime_error("List is empty");
		}
		head = head->next;
		size--;
	}
	//从尾部删除元素
	void pop_back() {
		if (head == nullptr) {
			throw std::runtime_error("List is empty");
		}
		else if (head->next == nullptr) {
			head = nullptr;
			size = 0;
			return;
		}
		auto sec_last = head;
		while (sec_last->next->next!=nullptr) {
			sec_last = sec_last->next;
		}
		sec_last->next = nullptr;
		size--;
	}
	//从指定位置删除元素
	void erase(size_t index) {
		if (index >= size) {
			throw std::out_of_range("Index out of range");
		}
		if (index == 0) {
			pop_front();
			return;
		}
		auto current = head;
		for (size_t i = 0; i < index - 1; ++i) {
			current = current->next;
		}
		current->next = current->next->next;
		size--;
	}
	//在指定位置插入元素
	void insert(size_t index, const T& data) {
		if (index > size) {
			throw std::out_of_range("Index out of range");
		}
		if (index == 0) {
			push_front(data);
			return;
		}
		auto current = head;
		for (size_t i = 0; i < index - 1; ++i) {
			current = current->next;
		}
		current->next = std::make_shared<Node>(data, current->next);
		size++;
	}
	//返回指定位置的元素
	const T& at(size_t index) const {
		if (index >= size) {
			throw std::out_of_range("Index out of range");
		}
		auto current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->data;
	}
	T& operator[](size_t index) const {
		if (index >= size) {
			throw std::out_of_range("Index out of range");
		}
		auto current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->data;
	}
	//返回链表大小
	size_t getsize()const {
		return size;
	}
	//遍历链表
	void traverse() {
		auto current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
	//反转链表
	void reverse() {
		std::shared_ptr<Node> prev = nullptr;
		auto current = head;
		std::shared_ptr<Node> next = nullptr;
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}
	//清空链表
	void clear() {
		head = nullptr;
		size = 0;
	}
	//拼接链表
	void append_range(List& list) {
		if (!list.size)return;
		if (!size) {
			*this = list;
			return;
		}
		auto newlist = std::make_shared<List>(list);
		auto last = head;
		while (last->next) {
			last = last->next;
		}
		last->next = newlist->head;
		size += newlist->size;
	}
	//重载+=运算符
	void operator+=(List& list) {
		append_range(list);
	}
	//重载+运算符
	friend LinkedListWithAutoPtr<T>& operator+(LinkedListWithAutoPtr<T>& list1, LinkedListWithAutoPtr<T>& list2) {
		auto result = new LinkedListWithAutoPtr<T>();
		result->append_range(list1);
		result->append_range(list2);
		return *result;
	}
	//重载<<运算符
	friend std::ostream& operator<<(std::ostream& os, LinkedListWithAutoPtr<T>& list) {
		list.traverse();
		return os;
	}
	//析构函数
	~LinkedListWithAutoPtr()=default;
private:
	std::shared_ptr<Node>head;
	size_t size;
};

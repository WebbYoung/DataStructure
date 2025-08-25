#pragma once

//���͵�������(����ָ��)ʵ��


#include "NodeWithAutoPtr.h"
template<typename T>
class LinkedListWithAutoPtr
{
	using List = LinkedListWithAutoPtr<T>;
	using Node = NodeWithAutoPtr<T>;
public:

	
	LinkedListWithAutoPtr() :head(nullptr), size(0) {}//Ĭ�Ϲ��캯��
	//�������캯��
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
	//���ظ�ֵ�����
	LinkedListWithAutoPtr& operator=(List& other) {
		if (&other == this)
			return *this;
		clear();
		auto cur = other.head; // ����other�Ľڵ�
		while (cur != nullptr) {
			this->push_back(cur->data); // ��other��ÿ��Ԫ����ӵ���ǰ����
			cur = cur->next;
		}
		return *this;
	}
	//ͷ�巨
	void push_front(const T& data) {
		head = std::make_shared<Node>(data, head);
	}
	//β�巨
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
	//��ͷ��ɾ��Ԫ��
	void pop_front() {
		if (head == nullptr) {
			throw std::runtime_error("List is empty");
		}
		head = head->next;
		size--;
	}
	//��β��ɾ��Ԫ��
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
	//��ָ��λ��ɾ��Ԫ��
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
	//��ָ��λ�ò���Ԫ��
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
	//����ָ��λ�õ�Ԫ��
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
	//���������С
	size_t getsize()const {
		return size;
	}
	//��������
	void traverse() {
		auto current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
	//��ת����
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
	//�������
	void clear() {
		head = nullptr;
		size = 0;
	}
	//ƴ������
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
	//����+=�����
	void operator+=(List& list) {
		append_range(list);
	}
	//����+�����
	friend LinkedListWithAutoPtr<T>& operator+(LinkedListWithAutoPtr<T>& list1, LinkedListWithAutoPtr<T>& list2) {
		auto result = new LinkedListWithAutoPtr<T>();
		result->append_range(list1);
		result->append_range(list2);
		return *result;
	}
	//����<<�����
	friend std::ostream& operator<<(std::ostream& os, LinkedListWithAutoPtr<T>& list) {
		list.traverse();
		return os;
	}
	//��������
	~LinkedListWithAutoPtr()=default;
private:
	std::shared_ptr<Node>head;
	size_t size;
};

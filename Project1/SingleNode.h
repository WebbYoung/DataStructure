#pragma once
template<typename T>
class LinkedList;
template<typename T>
class SingleNode
{
	friend class LinkedList<T>;
public:
	SingleNode() :next(nullptr){}
	SingleNode(const T& data, SingleNode* next) :data(data), next(next){}
	~SingleNode() {
		data = T();
		next = nullptr;
	}
	
private:
	T data;
	SingleNode* next;
};


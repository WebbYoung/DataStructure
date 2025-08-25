#pragma once
#include<iostream>
#include<memory>
#include<stdexcept>
template<typename T>
class LinkedListWithAutoPtr;
template<typename T>
class NodeWithAutoPtr
{
	friend class LinkedListWithAutoPtr<T>;
public:
	NodeWithAutoPtr() :next(nullptr) {}
	NodeWithAutoPtr(const T& data, std::shared_ptr<NodeWithAutoPtr>next) :data(data), next(next) {}
	~NodeWithAutoPtr() = default;

private:
	T data;
	std::shared_ptr<NodeWithAutoPtr>next;
};


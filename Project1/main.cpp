#include<iostream>
#include "LinkedList.h"
using namespace std;
auto main() -> int {
	LinkedList<int>list1,list2;
	for (int i = 0;i < 10;i++) {
		list1.push_back(i);
		list2.push_back(10 - i);
	}
	list1.swap(list2);
	list1.erase(0);
	list1 += list2;
	std::cout << list1[3];
	std::cout << list1;
	return 0;
}

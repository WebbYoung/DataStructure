#include<iostream>
#include "LinkedListWithAutoPtr.h"
using namespace std;
auto main() -> int {
	LinkedListWithAutoPtr<int>list1,list2;
	for (int i = 0;i < 10;i++) {
		list1.push_back(i);
		list2.push_back(10 - i);
	}
	cout << list1 + list2;
	return 0;
}

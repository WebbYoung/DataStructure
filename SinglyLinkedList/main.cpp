#include<iostream>
#include "LinkedListWithAutoPtr.h"
#include "LinkedList_C.h"
using namespace std;
auto main() -> int {
    struct CList list;
    initialize_CList(&list);
    for (int i = 0;i < 10;i++) {
        push_back(i, &list);
        push_front(9 - i, &list);
    }
    traverse(&list);
	return 0;
}

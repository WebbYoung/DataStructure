#include<iostream>
#include "LinkedListWithAutoPtr.h"
#include "LinkedList_C.h"
using namespace std;
auto main() -> int {
    struct CList list;
    initialize_CList(&list);
    for (int i = 0;i < 10;i++) {
        push_back(i, &list);
    }
    pop_front(&list);
    pop_back(&list);
    reverse_list(&list);
    traverse(&list);
    free_list(&list);
	return 0;
}

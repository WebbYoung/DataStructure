#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include "DoublyLinkedList.h"
int main() {
    List list;
    initialize_CList(&list);
    for (int i = 0; i < 10; i++) {
        push_back(i, &list);
    }
    printf("%d", at(4,&list));
    reverse_traverse(&list);
    system("pause");
    return 0;
}
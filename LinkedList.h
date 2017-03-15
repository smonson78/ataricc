#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "LinkedListNode.h"

namespace smonson {

template <typename T>
class LinkedList {
public:
	LinkedList() {
		//head = (LinkedListNode<T> *)0;
	}
	virtual ~LinkedList() {}
	void addItem(T *item) {
		//if (head == 0) {
		//	head = new LinkedListNode<T>(item);
		//	return;
		//}
		//LinkedListNode<T> *p = head;
		//while (p->next != 0) {
		//	p = p->next;
		//}
		//p->next = new LinkedListNode<T>(item);
	}
private:
	//LinkedListNode<T> *head;
};

}

#endif

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "LinkedListNode.h"

namespace smonson {

template <typename T>
class LinkedList {
public:

	LinkedList() {
		head = (LinkedListNode<T> *)0;
	}

	virtual ~LinkedList() {
		LinkedListNode<T> *p = head;
		while (p) {
			LinkedListNode<T> *next = p->getNext();
			delete p;
			p = next;
		}
	}

	void addItem(T *item) {
		if (head == 0) {
			head = new LinkedListNode<T>(item);
			return;
		}
		LinkedListNode<T> *p = head;
		while (p->getNext() != 0) {
			p = p->getNext();
		}
		p->add(item);
	}

	LinkedListNode<T> *getHead() {
		return head;
	}

	int findLength() {
		LinkedListNode<T> *p = head;
		int i = 0;
		while (p) {
			i++;
			p = p->getNext();
		}
		return i;
	}

private:
	LinkedListNode<T> *head;
};

}

#endif

#ifndef LINKEDLISTNODE_H_
#define LINKEDLISTNODE_H_

namespace smonson {

template <typename T>
class LinkedListNode {
public:
	LinkedListNode(T *item) {
		this->item = item;
		this->next = 0;
	}
	~LinkedListNode() {}
	T *getItem() {
		return item;
	}
	LinkedListNode<T> *getNext() {
		return next;
	}
	void add(T *item) {
		next = new LinkedListNode(item);
	}
private:
	T *item;
	LinkedListNode *next;
};
}

#endif

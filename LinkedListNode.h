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
	T *item;
	LinkedListNode *next;
};
}

#endif

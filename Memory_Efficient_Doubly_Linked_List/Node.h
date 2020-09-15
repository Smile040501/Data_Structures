#ifndef _NODE_
#define _NODE_

class Node {			// Node class for representing a node for memory efficient doubly linked list
public:
	// Attributes
	int data;
	Node *ptrDiff;		// XOR of prev and next node of the linked list
	
	// Constructors
	Node(int data, Node *prev, Node *next);
	Node();
	Node(int data);
	
	// Destructor
	~Node();
};

// Constructors
Node::Node(int data, Node *prev, Node *next)
: data{data}, ptrDiff{nullptr} {
	ptrDiff = (Node*) ((uintptr_t)(prev) ^ (uintptr_t)(next));
}

Node::Node()
: data{}, ptrDiff{nullptr} {
}

Node::Node(int data)
: data{data}, ptrDiff{nullptr} {
}

// Destructor
Node::~Node() {
}

#endif // _NODE_

#ifndef _NODE_
#define _NODE_

class Node {			// Node class for representing a node of the linked list representing Dequeue
public:
	// Attributes
	Node *prev;
	int data;
	Node *next;
	
	// Constructors
	Node();
	Node(int data);
	
	// Destructor
	~Node();
};

// Constructors
Node::Node()
: prev{nullptr}, data{}, next{nullptr} {
}

Node::Node(int data)
: prev{nullptr}, data{data}, next{nullptr} {
}

// Destructor
Node::~Node() {
	delete next;
	delete prev;
}

#endif // _NODE_

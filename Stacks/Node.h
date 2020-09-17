#ifndef _NODE_
#define _NODE_

class Node {			// Node class for representing a node of linked list representing stack
public:
	// Attributes
	int data;
	Node *bottom;
	
	// Constructors
	Node();
	Node(int data);
	
	// Destructor
	~Node();
};

// Constructors
Node::Node()
: data{}, bottom{nullptr} {
}

Node::Node(int data)
: data{data}, bottom{nullptr} {
}

// Destructor
Node::~Node() {
	delete bottom;
}

#endif // _NODE_

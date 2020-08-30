#ifndef _NODE_
#define _NODE_

#include<vector>

class Node {			// Node class for representing a node of the tree
	
public:
	// Attributes
	int data;
	std::vector<Node*> *children;
	
	// Constructors
	Node(int data, std::vector<Node*> *children);
	Node();
	Node(int data);
	
	// Destructor
	~Node();

};

// Constructors
Node::Node(int data, std::vector<Node*> *children)
: data{data}, children{children} {
}

Node::Node()
: Node(-1, nullptr) {
}

Node::Node(int data)
: Node(data, new std::vector<Node*>()) {
}

// Destructor
Node::~Node() {
	for(auto &node: *children) {
		delete node;
	}
	delete children;
}

#endif // _NODE_

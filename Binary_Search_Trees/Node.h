#ifndef _NODE_
#define _NODE_

class Node {			// Node class for representing a node of the tree

public:
	// Attributes
    Node* left;
    int data;
    Node* right;
    
	// Constructors
    Node(Node* left, int data, Node* right);
    Node();
    Node(int data);
    
	// Destructor
    ~Node();

};

// Constructors
Node::Node(Node* left, int data, Node* right)
: left{left}, data{data}, right{right} {
}

Node::Node()
: Node{nullptr, 0, nullptr} {
}

Node::Node(int data)
: Node{nullptr, data, nullptr} {
}

// Destructor
Node::~Node() {
    delete left;
    delete right;
}

#endif // _NODE_

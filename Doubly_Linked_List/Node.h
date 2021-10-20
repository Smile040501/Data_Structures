#ifndef _NODE_
#define _NODE_

class Node {  // Node class for representing a node of Doubly Linked List

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
}

#endif  // _NODE_

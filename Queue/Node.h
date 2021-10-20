#ifndef _NODE_
#define _NODE_

class Node {  // Node class for representing a node of the linked list representing a queue
   public:
    // Attributes
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
    : data{}, next{nullptr} {
}

Node::Node(int data)
    : data{data}, next{nullptr} {
}

// Destructor
Node::~Node() {
    delete next;
}

#endif  // _NODE_

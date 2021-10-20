#ifndef _NODE_
#define _NODE_

class Node {  // Node class for representing a node of a singly circular linked list
   public:
    // Attributes
    int data;
    Node *next;

    // Constructors
    Node();
    Node(int data);

    // Destrcutor
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
}

#endif  // _NODE_

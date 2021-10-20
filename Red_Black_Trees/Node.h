#ifndef _NODE_
#define _NODE_

class Node {  // Node class for representing a node of the tree

   public:
    int data;
    char color;
    Node* left;
    Node* right;
    Node* parent;

    // Constructors
    Node(int data, char color, Node* left, Node* right, Node* parent);
    Node();
    Node(int data);
    Node(int data, char color);

    // Destructor
    ~Node();

    // Methods
    void flipColor();
};

// Constructors

Node::Node(int data, char color, Node* left, Node* right, Node* parent)
    : data{data}, color{color}, left{left}, right{right}, parent{parent} {
}

Node::Node()
    : Node(0, 'R', nullptr, nullptr, nullptr) {
}

Node::Node(int data)
    : Node(data, 'R', nullptr, nullptr, nullptr) {
}

Node::Node(int data, char color)
    : Node(data, color, nullptr, nullptr, nullptr) {
}

// Destructor

Node::~Node() {
    delete left;
    delete right;
    delete parent;
}

// Methods

void Node::flipColor() {
    color = (color == 'R') ? 'B' : 'R';
}

#endif  // _NODE_

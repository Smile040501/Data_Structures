#ifndef _NODE_
#define _NODE_

#include <climits>
#include <cmath>

class Node {  // Node class for representing a node of the tree
   public:
    // Attributes
    int k1;
    int k2;
    int k3;
    Node* first;
    Node* second;
    Node* third;
    Node* fourth;
    Node* parent;

    // Constructors
    Node(int k1, int k2, int k3, Node* first, Node* second, Node* third, Node* fourth, Node* parent);
    Node();
    Node(int k1);
    Node(int k1, int k2);
    Node(int k1, int k2, int k3);

    // Destructor
    ~Node();

    // Methods
    void setKeyWithValue(int key, int newValue);  // Set the key with current value to the new value
    bool hasAnySpace();                           // To check if there is any space in the current node
    bool isLeafNode();                            // To check if the node is a leaf node
    bool hasKey(int key);                         // To check whether the key is present in a node
    int minKey();                                 // To get the minimum key out of the 3 keys
    int maxKey();                                 // To get the maximum key out of the 3 keys
    int keyCount();                               // To return the key count of a node
    int keyPosition(int key);                     // To return the position of a key in the node
    void sortKeys();                              // To sort the keys in increasing order
    void rearrangeChildren();                     // To rearrange the children of the node in increasing order

    Node* getNextSibling();      // To get the very next sibling of the node
    Node* getPreviousSibling();  // To get the very previous sibling of the node

    Node* rightmostChild(Node* node);  // To return the rightmost child of the node
    Node* rightmostChild();

    Node* leftmostChild(Node* node);  // To return the leftmost child of the node
    Node* leftmostChild();

    Node* previousChildOfKey(int key);  // To return the very previous child of the key
    Node* nextChildOfKey(int key);      // To return the very next child of the key
};

// Constructors
Node::Node(int k1, int k2, int k3, Node* first, Node* second, Node* third, Node* fourth, Node* parent)
    : k1{k1}, k2{k2}, k3{k3}, first{first}, second{second}, third{third}, fourth{fourth}, parent{parent} {
}

Node::Node()
    : Node(0, 0, 0, nullptr, nullptr, nullptr, nullptr, nullptr) {
}

Node::Node(int k1)
    : Node(k1, 0, 0, nullptr, nullptr, nullptr, nullptr, nullptr) {
}

Node::Node(int k1, int k2)
    : Node(k1, k2, 0, nullptr, nullptr, nullptr, nullptr, nullptr) {
}

Node::Node(int k1, int k2, int k3)
    : Node(k1, k2, k3, nullptr, nullptr, nullptr, nullptr, nullptr) {
}

// Destructor
Node::~Node() {
    delete first;
    delete second;
    delete third;
    delete fourth;
}

// Methods

// Set the key with current value to the new value
void Node::setKeyWithValue(int key, int newValue) {
    if (key == k1) {
        k1 = newValue;
    } else if (key == k2) {
        k2 = newValue;
    } else if (key == k3) {
        k3 = newValue;
    }
}

// To check if there is any space in the current node
bool Node::hasAnySpace() {
    if (k1 == 0 || k2 == 0 || k3 == 0) {
        return true;
    } else {
        return false;
    }
}

// To check if the node is a leaf node
bool Node::isLeafNode() {
    if (!first && !second && !third && !fourth) {
        return true;
    } else {
        return false;
    }
}

// To check whether the key is present in a node
bool Node::hasKey(int key) {
    if (key == k1 || key == k2 || key == k3) {
        return true;
    } else {
        return false;
    }
}

// To get the minimum key out of the 3 keys
int Node::minKey() {
    if (k1 == 0 && k2 == 0 && k3 == 0) {
        return 0;
    } else if (k1 == 0 && k2 == 0) {
        return k3;
    } else if (k2 == 0 && k3 == 0) {
        return k1;
    } else if (k3 == 0 && k1 == 0) {
        return k2;
    } else if (k1 == 0) {
        return (k2 < k3) ? k2 : k3;
    } else if (k2 == 0) {
        return (k1 < k3) ? k1 : k3;
    } else if (k3 == 0) {
        return (k1 < k2) ? k1 : k2;
    } else {
        return (k1 < k2 && k1 < k3) ? k1 : (k2 < k1 && k2 < k3) ? k2
                                                                : k3;
    }
}

// To get the maximum key out of the 3 keys
int Node::maxKey() {
    return std::fmax(k1, std::fmax(k2, k3));
}

// To return the number of the keys of a node
int Node::keyCount() {
    int count = 0;
    if (k1 != 0) {
        count++;
    }
    if (k2 != 0) {
        count++;
    }
    if (k3 != 0) {
        count++;
    }
    return count;
}

// To return the position of a key in the node
int Node::keyPosition(int key) {
    return (key == k1) ? 1 : (key == k2) ? 2
                         : (key == k3)   ? 3
                                         : 0;
}

// To sort the keys in increasing order
void Node::sortKeys() {
    int tempK1 = k1, tempK2 = k2, tempK3 = k3;
    k1 = 0;
    k2 = 0;
    k3 = 0;
    if (tempK1 == 0 && tempK2 == 0 && tempK3 == 0) {
        return;
    } else if (tempK1 == 0 && tempK2 == 0) {
        k1 = tempK3;
    } else if (tempK2 == 0 && tempK3 == 0) {
        k1 = tempK1;
    } else if (tempK3 == 0 && tempK1 == 0) {
        k1 = tempK2;
    } else if (tempK1 == 0) {
        k1 = (tempK2 < tempK3) ? tempK2 : tempK3;
        k2 = tempK2 + tempK3 - k1;
    } else if (tempK2 == 0) {
        k1 = (tempK1 < tempK3) ? tempK1 : tempK3;
        k2 = tempK1 + tempK3 - k1;
    } else if (k3 == 0) {
        k1 = (tempK1 < tempK2) ? tempK1 : tempK2;
        k2 = tempK1 + tempK2 - k1;
    } else {
        k1 = std::fmin(tempK1, std::fmin(tempK2, tempK3));
        k3 = std::fmax(tempK1, std::fmax(tempK2, tempK3));
        k2 = tempK1 + tempK2 + tempK3 - k1 - k3;
    }
}

// To rearrange the children of the node in increasing order
void Node::rearrangeChildren() {
    Node* tempFirst = first;
    Node* tempSecond = second;
    Node* tempThird = third;
    Node* tempFourth = fourth;
    first = nullptr;
    second = nullptr;
    third = nullptr;
    fourth = nullptr;
    if (tempFirst) {
        if (tempFirst->maxKey() < k1) {
            first = tempFirst;
        } else if ((k2 != 0 && (tempFirst->minKey() > k1 && tempFirst->maxKey() < k2)) || (k2 == 0 && (tempFirst->minKey() > k1))) {
            second = tempFirst;
        } else if ((k3 != 0 && (tempFirst->minKey() > k2 && tempFirst->maxKey() < k3)) || (k3 == 0 && (tempFirst->minKey() > k2))) {
            third = tempFirst;
        } else {
            fourth = tempFirst;
        }
    }
    if (tempSecond) {
        if (tempSecond->maxKey() < k1) {
            first = tempSecond;
        } else if ((k2 != 0 && (tempSecond->minKey() > k1 && tempSecond->maxKey() < k2)) || (k2 == 0 && (tempSecond->minKey() > k1))) {
            second = tempSecond;
        } else if ((k3 != 0 && (tempSecond->minKey() > k2 && tempSecond->maxKey() < k3)) || (k3 == 0 && (tempSecond->minKey() > k2))) {
            third = tempSecond;
        } else {
            fourth = tempSecond;
        }
    }
    if (tempThird) {
        if (tempThird->maxKey() < k1) {
            first = tempThird;
        } else if ((k2 != 0 && (tempThird->minKey() > k1 && tempThird->maxKey() < k2)) || (k2 == 0 && (tempThird->minKey() > k1))) {
            second = tempThird;
        } else if ((k3 != 0 && (tempThird->minKey() > k2 && tempThird->maxKey() < k3)) || (k3 == 0 && (tempThird->minKey() > k2))) {
            third = tempThird;
        } else {
            fourth = tempThird;
        }
    }
    if (tempFourth) {
        if (tempFourth->maxKey() < k1) {
            first = tempFourth;
        } else if ((k2 != 0 && (tempFourth->minKey() > k1 && tempFourth->maxKey() < k2)) || (k2 == 0 && (tempFourth->minKey() > k1))) {
            second = tempFourth;
        } else if ((k3 != 0 && (tempFourth->minKey() > k2 && tempFourth->maxKey() < k3)) || (k3 == 0 && (tempFourth->minKey() > k2))) {
            third = tempFourth;
        } else {
            fourth = tempFourth;
        }
    }
}

// To get the very next sibling of the node
Node* Node::getNextSibling() {
    if (parent) {
        if (this == parent->first) {
            return parent->second;
        } else if (this == parent->second) {
            return parent->third;
        } else if (this == parent->third) {
            return parent->fourth;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

// To get the very previous sibling of the node
Node* Node::getPreviousSibling() {
    if (parent) {
        if (this == parent->first) {
            return nullptr;
        } else if (this == parent->second) {
            return parent->first;
        } else if (this == parent->third) {
            return parent->second;
        } else {
            return parent->third;
        }
    } else {
        return nullptr;
    }
}

// To return the rightmost child of the node
Node* Node::rightmostChild(Node* node) {
    if (!node) {
        return nullptr;
    }
    if (node->isLeafNode()) {
        return node;
    }
    Node* temp = node;
    if (node->fourth) {
        temp = temp->fourth;
    } else if (node->third) {
        temp = temp->third;
    } else if (node->second) {
        temp = temp->second;
    } else if (node->first) {
        temp = temp->first;
    }
    return rightmostChild(temp);
}

Node* Node::rightmostChild() {
    return rightmostChild(this);
}

// To return the leftmost child of the node
Node* Node::leftmostChild(Node* node) {
    if (!node) {
        return nullptr;
    }
    if (node->isLeafNode()) {
        return node;
    }
    Node* temp = node;
    if (node->first) {
        temp = temp->first;
    } else if (node->second) {
        temp = temp->second;
    } else if (node->third) {
        temp = temp->third;
    } else if (node->fourth) {
        temp = temp->fourth;
    }
    return leftmostChild(temp);
}

Node* Node::leftmostChild() {
    return leftmostChild(this);
}

// To return the very previous child of the key
Node* Node::previousChildOfKey(int key) {
    if (hasKey(key)) {
        int position = keyPosition(key);
        if (position == 1) {
            return first;
        } else if (position == 2) {
            return second;
        } else {
            return third;
        }
    } else {
        return nullptr;
    }
}

// To return the very next child of the key
Node* Node::nextChildOfKey(int key) {
    if (hasKey(key)) {
        int position = keyPosition(key);
        if (position == 1) {
            return second;
        } else if (position == 2) {
            return third;
        } else {
            return fourth;
        }
    } else {
        return nullptr;
    }
}

#endif  // _NODE_

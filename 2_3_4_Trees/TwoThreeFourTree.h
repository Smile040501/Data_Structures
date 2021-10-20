#ifndef _TWO_THREE_FOUR_TREE_
#define _TWO_THREE_FOUR_TREE_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <vector>

#include "Node.h"

class TwoThreeFourTree {  // class for implementation of 2-3-4 Trees
   private:
    Node* root;  // root of the tree

    // Function to create the 2-3-4 Tree
    void create(std::initializer_list<int> list);

    // Function to return the height of the tree
    int height(Node* node);

    // Function that will rearrange the keys in increasing order while splitting the node
    void rearrangeKeys(Node* node, int& key);
    // Function that will create the new sibling while splitting the node
    Node* createSibling(Node* node, int k1, int k2);
    // Function to insert without splitting in the leaf node
    void insertWithoutSplit(Node* node, int key);
    // Function to insert with splitting in the leaf node
    void insertWithSplit(Node* node, int key);
    // Function to insert a key to the tree
    void insert(Node* node, int key);

    // Function to get the in-order predecessor of the key inside the node
    Node* inOrderPredecessor(Node* node, int key);
    // Function to get the in-order successor of the key inside the node
    Node* inOrderSuccessor(Node* node, int key);
    // Function to borrow a key from its sibling while deletion
    void borrowKey(Node* node, int keyToDelete, Node* parent, Node* sibling);
    // Function to merge a node with its sibling while deletion
    void mergeWithSibling(Node* node, int keyToDelete, Node* parent, Node* sibling);
    // Function to remove a key from the tree
    void remove(Node* node, int key);

    // Function to print in-order Traversal of the tree
    void inOrder(Node* node);

    // Function to print the Level Order Traversal of the tree
    void levelOrder(Node* node);

   public:
    // Constructors
    TwoThreeFourTree();
    TwoThreeFourTree(std::initializer_list<int> list);

    // Destructor
    ~TwoThreeFourTree();

    // Function to return the height of the tree
    int height();

    // Function to insert a key to the tree
    void insert(int key);

    // Function to remove a key from the tree
    void remove(int key);

    // Function to print in-order Traversal of the tree
    void inOrder();

    // Function to print the Level Order Traversal of the tree
    void levelOrder();
};

// Constructors
TwoThreeFourTree::TwoThreeFourTree()
    : root{nullptr} {
}

TwoThreeFourTree::TwoThreeFourTree(std::initializer_list<int> list)
    : root{nullptr} {
    create(list);
}

// Destructor
TwoThreeFourTree::~TwoThreeFourTree() {
    delete root;
}

// Function to create a 2-3-4 Tree from the input list
void TwoThreeFourTree::create(std::initializer_list<int> list) {
    for (auto i{std::begin(list)}; i != std::end(list); i++) {
        insert(*i);
    }
}

// Function to return the height of the tree
int TwoThreeFourTree::height(Node* node) {
    if (!node) {
        return 0;
    }
    int x1 = height(node->first);
    int x2 = height(node->second);
    int x3 = height(node->third);
    int x4 = height(node->fourth);
    return 1 + std::fmax(std::fmax(x1, x2), std::fmax(x3, x4));
}

int TwoThreeFourTree::height() {
    return height(root);
}

// Function that will rearrange the keys in increasing order while splitting the node
void TwoThreeFourTree::rearrangeKeys(Node* node, int& key) {
    std::vector<int> vec{node->k1, node->k2, node->k3, key};
    std::sort(vec.begin(), vec.end());
    node->k1 = vec.at(0);
    node->k2 = vec.at(1);
    node->k3 = vec.at(2);
    key = vec.at(3);
}

// Function that will create the new sibling while splitting the node
Node* TwoThreeFourTree::createSibling(Node* node, int k1, int k2) {
    Node* newSibling = new Node(k1, k2);
    if (node->third) {
        newSibling->first = node->third;
        node->third->parent = newSibling;
    }
    if (node->fourth) {
        newSibling->second = node->fourth;
        node->fourth->parent = newSibling;
    }
    node->k2 = 0;
    node->k3 = 0;
    node->third = nullptr;
    node->fourth = nullptr;
    return newSibling;
}

// Function to insert without splitting in the leaf node
void TwoThreeFourTree::insertWithoutSplit(Node* node, int key) {
    if (node->k1 == 0) {
        node->k1 = key;
    } else {
        if (key < node->k1) {
            node->k3 = node->k2;
            node->k2 = node->k1;
            node->k1 = key;
        } else {
            if (node->k2 == 0) {
                node->k2 = key;
            } else {
                if (key < node->k2) {
                    node->k3 = node->k2;
                    node->k2 = key;
                } else {
                    node->k3 = key;
                }
            }
        }
    }
}

// Function to insert with splitting in the leaf node
void TwoThreeFourTree::insertWithSplit(Node* node, int key) {
    rearrangeKeys(node, key);

    if (node == root) {
        Node* newParent = new Node(node->k2);
        Node* newSibling = createSibling(node, node->k3, key);
        newSibling->parent = newParent;
        node->parent = newParent;
        newParent->first = node;
        newParent->second = newSibling;
        root = newParent;
    } else {
        Node* previousParent = node->parent;
        if (previousParent->hasAnySpace()) {
            int nodeK2 = node->k2;
            Node* newSibling = createSibling(node, node->k3, key);
            newSibling->parent = previousParent;
            previousParent->fourth = newSibling;
            insertWithoutSplit(previousParent, nodeK2);
            previousParent->rearrangeChildren();
        } else {
            if (previousParent->first == node) {
                int nodeK2 = node->k2;
                Node* newSibling = createSibling(node, node->k3, key);
                insertWithSplit(previousParent, nodeK2);
                Node* newParentSibling = previousParent->getNextSibling();
                newSibling->parent = previousParent;
                if (previousParent->second) {
                    newParentSibling->third = previousParent->second;
                    previousParent->second->parent = newParentSibling;
                }
                previousParent->second = newSibling;
                newParentSibling->rearrangeChildren();
            } else {
                int nodeK2 = node->k2;
                Node* newSibling = createSibling(node, node->k3, key);
                insertWithSplit(previousParent, nodeK2);
                Node* newParentSibling = previousParent->getNextSibling();
                newSibling->parent = newParentSibling;
                newParentSibling->third = newSibling;
                newParentSibling->rearrangeChildren();
            }
        }
    }
}

// Function to insert a key to the tree
void TwoThreeFourTree::insert(Node* node, int key) {
    if (node->isLeafNode()) {
        if (node->hasAnySpace()) {
            insertWithoutSplit(node, key);
            node->rearrangeChildren();
        } else {
            insertWithSplit(node, key);
        }
    } else {
        if (key < node->k1) {
            insert(node->first, key);
        } else if ((node->k2 != 0 && (key > node->k1 && key < node->k2)) || (node->k2 == 0 && (key > node->k1))) {
            insert(node->second, key);
        } else if ((node->k3 != 0 && (key > node->k2 && key < node->k3)) || (node->k3 == 0 && (key > node->k2))) {
            insert(node->third, key);
        } else {
            insert(node->fourth, key);
        }
    }
}

void TwoThreeFourTree::insert(int key) {
    if (root) {
        insert(root, key);
    } else {
        root = new Node(key);
    }
}

// Function to get the in-order predecessor of the key inside the node
Node* TwoThreeFourTree::inOrderPredecessor(Node* node, int key) {
    if (node) {
        if (node->isLeafNode()) {
            return nullptr;
        } else {
            Node* predecessor{};
            if (node->keyPosition(key) == 1) {
                predecessor = node->first;
            } else if (node->keyPosition(key) == 2) {
                predecessor = node->second;
            } else if (node->keyPosition(key) == 3) {
                predecessor = node->third;
            } else {
                predecessor = nullptr;
            }
            if (predecessor) {
                return predecessor->rightmostChild();
            } else {
                return nullptr;
            }
        }
    } else {
        return nullptr;
    }
}

// Function to get the in-order successor of the key inside the node
Node* TwoThreeFourTree::inOrderSuccessor(Node* node, int key) {
    if (node) {
        if (node->isLeafNode()) {
            return nullptr;
        } else {
            Node* successor{};
            if (node->keyPosition(key) == 1) {
                successor = node->second;
            } else if (node->keyPosition(key) == 2) {
                successor = node->third;
            } else if (node->keyPosition(key) == 3) {
                successor = node->fourth;
            } else {
                successor = nullptr;
            }
            if (successor) {
                return successor->leftmostChild();
            } else {
                return nullptr;
            }
        }
    } else {
        return nullptr;
    }
}

// Function to borrow a key from its sibling while deletion
void TwoThreeFourTree::borrowKey(Node* node, int keyToDelete, Node* parent, Node* sibling) {
    if (node == parent->first) {
        node->setKeyWithValue(keyToDelete, parent->k1);
        node->rearrangeChildren();
        if (sibling->first) {
            node->fourth = sibling->first;
            sibling->first->parent = node;
        }
        node->rearrangeChildren();
        parent->k1 = sibling->k1;
        sibling->k1 = 0;
        sibling->first = nullptr;
        sibling->sortKeys();
        sibling->rearrangeChildren();
    } else if (node == parent->second) {
        if (sibling == node->getNextSibling()) {
            node->setKeyWithValue(keyToDelete, parent->k2);
            node->rearrangeChildren();
            if (sibling->first) {
                node->fourth = sibling->first;
                sibling->first->parent = node;
            }
            node->rearrangeChildren();
            parent->k2 = sibling->k1;
            sibling->k1 = 0;
            sibling->first = nullptr;
            sibling->sortKeys();
            sibling->rearrangeChildren();
        } else {
            node->setKeyWithValue(keyToDelete, parent->k1);
            node->rearrangeChildren();
            if (sibling->fourth) {
                node->first = sibling->fourth;
                sibling->fourth->parent = node;
                sibling->fourth = nullptr;
            } else if (sibling->third) {
                node->first = sibling->third;
                sibling->third->parent = node;
                sibling->third = nullptr;
            } else if (sibling->second) {
                node->first = sibling->second;
                sibling->second->parent = node;
                sibling->second = nullptr;
            }
            node->rearrangeChildren();
            parent->k1 = sibling->maxKey();
            sibling->setKeyWithValue(sibling->maxKey(), 0);
            sibling->sortKeys();
            sibling->rearrangeChildren();
        }
    } else if (node == parent->third) {
        if (sibling == node->getNextSibling()) {
            node->setKeyWithValue(keyToDelete, parent->k3);
            node->rearrangeChildren();
            if (sibling->first) {
                node->fourth = sibling->first;
                sibling->first->parent = node;
            }
            node->rearrangeChildren();
            parent->k3 = sibling->k1;
            sibling->k1 = 0;
            sibling->first = nullptr;
            sibling->sortKeys();
            sibling->rearrangeChildren();
        } else {
            node->setKeyWithValue(keyToDelete, parent->k2);
            node->rearrangeChildren();
            if (sibling->fourth) {
                node->first = sibling->fourth;
                sibling->fourth->parent = node;
                sibling->fourth = nullptr;
            } else if (sibling->third) {
                node->first = sibling->third;
                sibling->third->parent = node;
                sibling->third = nullptr;
            } else if (sibling->second) {
                node->first = sibling->second;
                sibling->second->parent = node;
                sibling->second = nullptr;
            }
            node->rearrangeChildren();
            parent->k2 = sibling->maxKey();
            sibling->setKeyWithValue(sibling->maxKey(), 0);
            sibling->sortKeys();
            sibling->rearrangeChildren();
        }
    } else {
        node->setKeyWithValue(keyToDelete, parent->k3);
        node->rearrangeChildren();
        if (sibling->fourth) {
            node->first = sibling->fourth;
            sibling->fourth->parent = node;
            sibling->fourth = nullptr;
        } else if (sibling->third) {
            node->first = sibling->third;
            sibling->third->parent = node;
            sibling->third = nullptr;
        } else if (sibling->second) {
            node->first = sibling->second;
            sibling->second->parent = node;
            sibling->second = nullptr;
        }
        node->rearrangeChildren();
        parent->k3 = sibling->maxKey();
        sibling->setKeyWithValue(sibling->maxKey(), 0);
        sibling->sortKeys();
        sibling->rearrangeChildren();
    }
}

// Function to merge a node with its sibling while deletion
void TwoThreeFourTree::mergeWithSibling(Node* node, int keyToDelete, Node* parent, Node* sibling) {
    if (node == parent->first) {
        node->setKeyWithValue(keyToDelete, parent->k1);
        node->k2 = sibling->k1;
        if (sibling->first) {
            node->third = sibling->first;
            sibling->first->parent = node;
        }
        if (sibling->second) {
            node->fourth = sibling->second;
            sibling->second->parent = node;
        }
        node->sortKeys();
        node->rearrangeChildren();
        parent->second = nullptr;
        if (parent->keyCount() >= 2) {
            parent->k1 = 0;
            parent->sortKeys();
            parent->rearrangeChildren();
        } else {
            if (parent == root) {
                node->parent = nullptr;
                root = node;
                parent->first = nullptr;
                delete parent;
            } else {
                if (parent->getNextSibling() && parent->getNextSibling()->keyCount() >= 2) {
                    borrowKey(parent, parent->k1, parent->parent, parent->getNextSibling());
                } else if (parent->getPreviousSibling() && parent->getPreviousSibling()->keyCount() >= 2) {
                    borrowKey(parent, parent->k1, parent->parent, parent->getPreviousSibling());
                } else {
                    if (parent->getNextSibling()) {
                        mergeWithSibling(parent, parent->k1, parent->parent, parent->getNextSibling());
                    } else {
                        mergeWithSibling(parent, parent->k1, parent->parent, parent->getPreviousSibling());
                    }
                }
            }
        }
    } else if (node == parent->second) {
        if (sibling == node->getNextSibling()) {
            node->setKeyWithValue(keyToDelete, parent->k2);
            node->k2 = sibling->k1;
            if (sibling->first) {
                node->third = sibling->first;
                sibling->first->parent = node;
            }
            if (sibling->second) {
                node->fourth = sibling->second;
                sibling->second->parent = node;
            }
            node->sortKeys();
            node->rearrangeChildren();
            parent->third = nullptr;
            if (parent->keyCount() >= 2) {
                parent->k2 = 0;
                parent->sortKeys();
                parent->rearrangeChildren();
            } else {
                if (parent == root) {
                    node->parent = nullptr;
                    root = node;
                    parent->second = nullptr;
                    delete parent;
                } else {
                    if (parent->getNextSibling() && parent->getNextSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k2, parent->parent, parent->getNextSibling());
                    } else if (parent->getPreviousSibling() && parent->getPreviousSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k2, parent->parent, parent->getPreviousSibling());
                    } else {
                        if (parent->getNextSibling()) {
                            mergeWithSibling(parent, parent->k2, parent->parent, parent->getNextSibling());
                        } else {
                            mergeWithSibling(parent, parent->k2, parent->parent, parent->getPreviousSibling());
                        }
                    }
                }
            }
        } else {
            sibling->k2 = parent->k1;
            if (node->first) {
                sibling->third = node->first;
                node->first->parent = sibling;
            }
            if (node->second) {
                sibling->fourth = node->second;
                node->second->parent = sibling;
            }
            sibling->sortKeys();
            sibling->rearrangeChildren();
            parent->second = nullptr;
            if (parent->keyCount() >= 2) {
                parent->k1 = 0;
                parent->sortKeys();
                parent->rearrangeChildren();
            } else {
                if (parent == root) {
                    sibling->parent = nullptr;
                    root = sibling;
                    parent->first = nullptr;
                    delete parent;
                } else {
                    if (parent->getNextSibling() && parent->getNextSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k1, parent->parent, parent->getNextSibling());
                    } else if (parent->getPreviousSibling() && parent->getPreviousSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k1, parent->parent, parent->getPreviousSibling());
                    } else {
                        if (parent->getNextSibling()) {
                            mergeWithSibling(parent, parent->k1, parent->parent, parent->getNextSibling());
                        } else {
                            mergeWithSibling(parent, parent->k1, parent->parent, parent->getPreviousSibling());
                        }
                    }
                }
            }
        }
    } else if (node == parent->third) {
        if (sibling == node->getNextSibling()) {
            node->setKeyWithValue(keyToDelete, parent->k3);
            node->k2 = sibling->k1;
            if (sibling->first) {
                node->third = sibling->first;
                sibling->first->parent = node;
            }
            if (sibling->second) {
                node->fourth = sibling->second;
                sibling->second->parent = node;
            }
            node->sortKeys();
            node->rearrangeChildren();
            parent->fourth = nullptr;
            if (parent->keyCount() >= 2) {
                parent->k3 = 0;
                parent->sortKeys();
                parent->rearrangeChildren();
            } else {
                if (parent == root) {
                    node->parent = nullptr;
                    root = node;
                    parent->second = nullptr;
                    delete parent;
                } else {
                    if (parent->getNextSibling() && parent->getNextSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k3, parent->parent, parent->getNextSibling());
                    } else if (parent->getPreviousSibling() && parent->getPreviousSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k3, parent->parent, parent->getPreviousSibling());
                    } else {
                        if (parent->getNextSibling()) {
                            mergeWithSibling(parent, parent->k3, parent->parent, parent->getNextSibling());
                        } else {
                            mergeWithSibling(parent, parent->k3, parent->parent, parent->getPreviousSibling());
                        }
                    }
                }
            }
        } else {
            sibling->k2 = parent->k2;
            if (node->first) {
                sibling->third = node->first;
                node->first->parent = sibling;
            }
            if (node->second) {
                sibling->fourth = node->second;
                node->second->parent = sibling;
            }
            sibling->sortKeys();
            sibling->rearrangeChildren();
            parent->second = nullptr;
            if (parent->keyCount() >= 2) {
                parent->k2 = 0;
                parent->sortKeys();
                parent->rearrangeChildren();
            } else {
                if (parent == root) {
                    sibling->parent = nullptr;
                    root = sibling;
                    parent->first = nullptr;
                    delete parent;
                } else {
                    if (parent->getNextSibling() && parent->getNextSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k2, parent->parent, parent->getNextSibling());
                    } else if (parent->getPreviousSibling() && parent->getPreviousSibling()->keyCount() >= 2) {
                        borrowKey(parent, parent->k2, parent->parent, parent->getPreviousSibling());
                    } else {
                        if (parent->getNextSibling()) {
                            mergeWithSibling(parent, parent->k2, parent->parent, parent->getNextSibling());
                        } else {
                            mergeWithSibling(parent, parent->k2, parent->parent, parent->getPreviousSibling());
                        }
                    }
                }
            }
        }
    } else {
        sibling->k2 = parent->k3;
        if (node->first) {
            sibling->third = node->first;
            node->first->parent = sibling;
        }
        if (node->second) {
            sibling->fourth = node->second;
            node->second->parent = sibling;
        }
        sibling->sortKeys();
        sibling->rearrangeChildren();
        parent->second = nullptr;
        if (parent->keyCount() >= 2) {
            parent->k3 = 0;
            parent->sortKeys();
            parent->rearrangeChildren();
        } else {
            if (parent == root) {
                sibling->parent = nullptr;
                root = sibling;
                parent->first = nullptr;
                delete parent;
            } else {
                if (parent->getNextSibling() && parent->getNextSibling()->keyCount() >= 2) {
                    borrowKey(parent, parent->k3, parent->parent, parent->getNextSibling());
                } else if (parent->getPreviousSibling() && parent->getPreviousSibling()->keyCount() >= 2) {
                    borrowKey(parent, parent->k3, parent->parent, parent->getPreviousSibling());
                } else {
                    if (parent->getNextSibling()) {
                        mergeWithSibling(parent, parent->k3, parent->parent, parent->getNextSibling());
                    } else {
                        mergeWithSibling(parent, parent->k3, parent->parent, parent->getPreviousSibling());
                    }
                }
            }
        }
    }
}

// Function to remove a key from the tree
void TwoThreeFourTree::remove(Node* node, int key) {
    if (node->isLeafNode()) {
        if (node->keyCount() >= 2) {
            node->setKeyWithValue(key, 0);
            node->sortKeys();
        } else if (node == root) {
            Node* temp = root;
            root = nullptr;
            delete temp;
        } else {
            if (node->getNextSibling() && node->getNextSibling()->keyCount() >= 2) {
                borrowKey(node, key, node->parent, node->getNextSibling());
            } else if (node->getPreviousSibling() && node->getPreviousSibling()->keyCount() >= 2) {
                borrowKey(node, key, node->parent, node->getPreviousSibling());
            } else {
                if (node->getNextSibling()) {
                    mergeWithSibling(node, key, node->parent, node->getNextSibling());
                } else {
                    mergeWithSibling(node, key, node->parent, node->getPreviousSibling());
                }
            }
        }
    } else {
        if (node->hasKey(key)) {
            if (node->keyPosition(key) == 1) {
                if (height(node->first) > height(node->second)) {
                    Node* predecessor = inOrderPredecessor(node, key);
                    node->k1 = predecessor->maxKey();
                    remove(node->first, predecessor->maxKey());
                } else {
                    Node* successor = inOrderSuccessor(node, key);
                    node->k1 = successor->minKey();
                    remove(node->second, successor->minKey());
                }
            } else if (node->keyPosition(key) == 2) {
                if (height(node->second) > height(node->third)) {
                    Node* predecessor = inOrderPredecessor(node, key);
                    node->k2 = predecessor->maxKey();
                    remove(node->second, predecessor->maxKey());
                } else {
                    Node* successor = inOrderSuccessor(node, key);
                    node->k2 = successor->minKey();
                    remove(node->third, successor->minKey());
                }
            } else {
                if (height(node->third) > height(node->fourth)) {
                    Node* predecessor = inOrderPredecessor(node, key);
                    node->k3 = predecessor->maxKey();
                    remove(node->third, predecessor->maxKey());
                } else {
                    Node* successor = inOrderSuccessor(node, key);
                    node->k3 = successor->minKey();
                    remove(node->fourth, successor->minKey());
                }
            }
        } else {
            if (key < node->k1) {
                remove(node->first, key);
            } else if ((node->k2 != 0 && (key < node->k2 && key > node->k1)) || (node->k2 == 0 && (key > node->k1))) {
                remove(node->second, key);
            } else if ((node->k3 != 0 && (key < node->k3 && key > node->k2)) || (node->k3 == 0 && (key > node->k2))) {
                remove(node->third, key);
            } else {
                remove(node->fourth, key);
            }
        }
    }
}

void TwoThreeFourTree::remove(int key) {
    if (root) {
        remove(root, key);
    } else {
        return;
    }
}

// Function to print in-order Traversal of the tree
void TwoThreeFourTree::inOrder(Node* node) {
    if (node) {
        inOrder(node->first);
        std::cout << node->k1 << " ";
        inOrder(node->second);
        std::cout << node->k2 << " ";
        inOrder(node->third);
        std::cout << node->k3 << " ";
        inOrder(node->fourth);
    }
}

void TwoThreeFourTree::inOrder() {
    std::cout << "In-Order Traversal: ";
    inOrder(root);
    std::cout << std::endl;
}

// Function to print the Level Order Traversal of the tree
void TwoThreeFourTree::levelOrder(Node* node) {
    std::queue<Node*> helper;
    helper.push(node);
    helper.push(nullptr);
    while (!helper.empty()) {
        Node* front = helper.front();
        helper.pop();
        if (front == nullptr) {
            if (helper.empty()) {
                break;
            }
            helper.push(nullptr);
            std::cout << std::endl;
            continue;
        }
        if (front->k1 == -1 && front->k2 == -1 && front->k3 == -1) {
            std::cout << -1 << "  ";
        } else {
            std::cout << front->k1 << ":" << front->k2 << ":" << front->k3 << "  ";
            if (front->first) {
                helper.push(front->first);
            } else {
                helper.push(new Node(-1, -1, -1));
            }
            if (front->second) {
                helper.push(front->second);
            } else {
                helper.push(new Node(-1, -1, -1));
            }
            if (front->third) {
                helper.push(front->third);
            } else {
                helper.push(new Node(-1, -1, -1));
            }
            if (front->fourth) {
                helper.push(front->fourth);
            } else {
                helper.push(new Node(-1, -1, -1));
            }
        }
    }
}

void TwoThreeFourTree::levelOrder() {
    std::cout << "Level Order Traversal: " << std::endl;
    levelOrder(root);
    std::cout << std::endl;
}

#endif  // _TWO_THREE_FOUR_TREE_

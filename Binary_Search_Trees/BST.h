#ifndef _BST_
#define _BST_

#include "Node.h"
#include<initializer_list>
#include<iostream>
#include<queue>
#include<cmath>
#include<climits>

class BST {		// BST class for representing Binary Search Tree
private:
    Node* root;			// root of the tree
    
	// Function to create BST from the input list
	void createBST(std::initializer_list<int> list);
	
	// Function to return the height of the tree
	int height(Node* node);
	
	// Function to insert a key to the tree
	void insert(Node* node, int key);
	
	// Function to search for a key in the tree
	bool search(Node* node, int key);
	// Function to check whether the tree is Binary Search Tree or not
	bool checkBST(Node *node, int min, int max);
	
	// Function to return the in-order predecessor of the node
	Node* inOrderPredecessor(Node* node);
	// Function to return the in-order successor of the node
    Node* inOrderSuccessor(Node* node);
	// Function to remove a key from the tree
	Node* remove(Node* node, int key);
	
	// Function to print the in-order traversal of the tree
	void inOrder(Node* node);
	// Function to print the level order traversal of the tree
	void levelOrder(Node *node);
	
public:
	
	// Constructor
    BST(std::initializer_list<int> list);
    
	// Destructor
    ~BST();
    
	// Function to return the height of the tree
	int height();
	
	// Function to insert a key to the tree
    void insert(int key);
	
	// Function to search for a key in the tree
	bool search(int key);
	// Function to check whether the tree is Binary Search Tree or not
	bool checkBST();
	
	// Function to remove a key from the tree
    void remove(int key);
	
	// Function to print the in-order traversal of the tree
    void inOrder();
	// Function to print the level order traversal of the tree
	void levelOrder();

};

// Constructor
BST::BST(std::initializer_list<int> list)
: root{nullptr} {
    createBST(list);
}

// Destructor
BST::~BST() {
	delete root;
}

// Function to create BST from the input list
void BST::createBST(std::initializer_list<int> list) {
    for(auto i{std::begin(list)}; i!=std::end(list); i++) {
        insert(*i);
    }
}

// Function to return the height of the tree
int BST::height(Node* node) {
    if(node) {
        int x = height(node->left);
        int y = height(node->right);
		return std::fmax(x, y) + 1;
    } else {
        return 0;
    }
}

int BST::height() {
	return height(root);
}

// Function to insert a key to the tree
void BST::insert(Node* node, int key) {
    if(node) {
        if(key < node->data) {
            if(node->left) {
                insert(node->left, key);
            } else {
                node->left = new Node(key);
                return;
            }
        } else {
            if(node->right) {
                insert(node->right, key);
            } else {
                node->right = new Node(key);
                return;
            }
        }
    } else {
        return;
    }
}

void BST::insert(int key) {
    if(root) {
        insert(root, key);
    } else {
        root = new Node(key);
    }
}

// Function to search for a key in the tree
bool BST::search(Node* node, int key) {
    if(node) {
        if(key < node->data) {
            return search(node->left, key);
        } else if(key > node->data) {
            return search(node->right, key);
        } else {
            return true;
        }
    } else {
        return false;
    }
}

bool BST::search(int key) {
    return search(root, key);
}

// Function to check whether the tree is Binary Search Tree or not
bool BST::checkBST(Node *node, int min, int max) {
	if(!node) {
		return true;
	}
	if(node->data < min || node->data > max) {
		return false;
	}
	bool left = checkBST(node->left, min, node->data);
	bool right = checkBST(node->right, node->data, max);
	
	return left && right;
}

bool BST::checkBST() {
	return checkBST(root, INT_MIN, INT_MAX);
}

// Function to return in-order predecessor of the node
Node* BST::inOrderPredecessor(Node* node) {
    Node* predecessor = node->left;
    if(predecessor) {
        while(predecessor->right) {
            predecessor = predecessor->right;
        }
    }
    return predecessor;
}

// Function to return the in-order successor of the node
Node* BST::inOrderSuccessor(Node* node) {
    Node* successor = node->right;
    if(successor) {
        while(successor->left) {
            successor = successor->left;
        }
    }
    return successor;
}

// Function to remove a key from the tree
Node* BST::remove(Node* node, int key) {
    if(!node) {
        return nullptr;
    }
    if(!node->left && !node->right) {
        if(node->data==key) {
			if(node == root) {
				root = nullptr;
			}
			delete node;
			return nullptr;
		} else {
			return node;
		}
    }
    if(key < node->data) {
        node->left = remove(node->left, key);
    } else if(key > node->data) {
        node->right = remove(node->right, key);
    } else {
        if(height(node->left) > height(node->right)) {
            Node* predecessor = inOrderPredecessor(node);
            node->data = predecessor->data;
            node->left = remove(node->left, predecessor->data);
        } else {
            Node* successor = inOrderSuccessor(node);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
    }
    return node;
}

void BST::remove(int key) {
    root = remove(root, key);
}

// Function to print the in-order traversal of the tree
void BST::inOrder(Node* node) {
    if(node) {
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }
}

void BST::inOrder() {
    std::cout << "In-Order Traversal: ";
    inOrder(root);
    std::cout << std::endl;
}

// Function to print the level order traversal of the tree
void BST::levelOrder(Node *node) {
	std::queue<Node*> helper;
	helper.push(node);
	helper.push(nullptr);
	while(!helper.empty()) {
		Node *front = helper.front();
		helper.pop();
		if(front==nullptr) {
			if(helper.empty()) {
				break;
			}
			std::cout << std::endl;
			helper.push(nullptr);
			continue;
		}
		std::cout << front->data << " ";
		if(front->data!=-1) {
			if(front->left) {
				helper.push(front->left);
			} else {
				helper.push(new Node(-1));
			}
			if(front->right) {
				helper.push(front->right);
			} else {
				helper.push(new Node(-1));
			}
		}
	}
}

void BST::levelOrder() {
	std::cout << "Level Order Traversal: " << std::endl;
	levelOrder(root);
	std::cout << std::endl;
}

#endif // _BST_

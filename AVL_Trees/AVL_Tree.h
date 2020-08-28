#ifndef _AVL_TREE_
#define _AVL_TREE_

#include "Node.h"
#include<initializer_list>
#include<iostream>
#include<queue>
#include<cmath>

class AVL_Tree {		// AVL Tree class
private:
    Node* root;
	
	// Function to create AVL Tree from the provided list
    void createAVLTree(std::initializer_list<int> list);
    
	// Function to calculate height of the AVL Tree
	int height(Node* node);
	
    // Function to calculate the balance factor for each node
    int balanceFactor(Node* node);
    
	// Functions to do Rotations for balancing the node
	Node* LLRotation(Node* node);
    Node* LRRotation(Node* node);
    Node* RRRotation(Node* node);
    Node* RLRotation(Node* node);
	
	// Function to check the balance factor of newly inserted node and make corresponding rotations
    Node* insertBalanced(Node* node);
	
	// Function to insert a Key in AVL Tree
    void insert(Node* node, int key);
	
	// Function to search for a key in AVL Tree
    bool search(Node* node, int key);
	
	// Function to find the in-order predecessor of a node
    Node* inOrderPre(Node* node);
	
	// Function to find the in-order successor of a node
    Node* inOrderSuc(Node* node);
    
	// Function to check the balance factor of the remaining nodes after deleting the node
    Node* deleteBalanced(Node* node);
	
	// Function to remove a key from the AVL Tree
    Node* remove(Node* node, int key);
	
	// Function to print the in-order traversal of the AVL tree
    void inOrder(Node* node);
	
	// Function to check whether the AVL Tree is balanced or not
    bool isBalanced(Node* node);
	
	// Function to print each level in a new line
	void levelOrder(Node* node);
	
public:
	// Constructors
    AVL_Tree();
    AVL_Tree(std::initializer_list<int> list);
    
	// Destructor
    ~AVL_Tree();
    
	// Function to calculate height of the AVL Tree
    int height();
	
	// Function to insert a Key in AVL Tree
    void insert(int key);
    
	// Function to search for a key in AVL Tree
    bool search(int key);
    
	// Function to remove a key from the AVL Tree
    void remove(int key);
    
	// Function to print the in-order traversal of the AVL tree
    void inOrder();
	
	// Function to print each level in a new line
	void levelOrder();
	
	// Function to check whether the AVL Tree is balanced or not
    bool isBalanced();
	
};

// Constructors
AVL_Tree::AVL_Tree() 
:root{nullptr} {
}

AVL_Tree::AVL_Tree(std::initializer_list<int> list)
: root{nullptr} {
    createAVLTree(list);
}

// Destructor
AVL_Tree::~AVL_Tree() {
	delete root;
}

// Function to create AVL Tree from the provided list
void AVL_Tree::createAVLTree(std::initializer_list<int> list) {
    for(auto i{std::begin(list)}; i!=std::end(list); i++) {
        insert(*i);
    }
}

// Function to calculate height of the AVL Tree
int AVL_Tree::height(Node* node) {
    if(node) {
        int x{height(node->left)};
        int y{height(node->right)};
        return fmax(x, y) + 1;
    } else {
        return 0;
    }
}

int AVL_Tree::height() {
	return height(root);
}

// Function to calculate the balance factor for each node
int AVL_Tree::balanceFactor(Node* node) {
    return height(node->left) - height(node->right);
}

// Function to do LL Rotation for balancing the node
Node* AVL_Tree::LLRotation(Node* node) {
    Node* second{node->left};
    node->left = second->right;
    second->right = node;
	return second;
}

// Function to do LR Rotation for balancing the node
Node* AVL_Tree::LRRotation(Node* node) {
    Node* second{node->left};
    Node* third{second->right};
    node->left = third->right;
    second->right = third->left;
    third->left = second;
    third->right = node;
    return third;
}

// Function to do RR Rotation for balancing the node
Node* AVL_Tree::RRRotation(Node* node) {
    Node* second{node->right};
    node->right = second->left;
    second->left = node;
    return second;
}

// Function to do Rotation for balancing the node
Node* AVL_Tree::RLRotation(Node* node) {
    Node* second{node->right};
    Node* third{second->left};
    node->right = third->left;
    second->left = third->right;
    third->left = node;
    third->right = second;
    return third;
}

// Function to check the balance factor of newly inserted node and make corresponding rotation
Node* AVL_Tree::insertBalanced(Node* node) {
	if(!node || (!node->left && !node->right)) {
		return node;
	}
	int bfNode = balanceFactor(node);
    if(bfNode == 2) {
		int bfLeft = balanceFactor(node->left);
        if(bfLeft == 1) {
            node = LLRotation(node);
        } else if(bfLeft == -1) {
            node = LRRotation(node);
        }
    } else if(bfNode == -2) {
		int bfRight = balanceFactor(node->right);
        if(bfRight == 1) {
            node = RLRotation(node);
        } else if(bfRight == -1) {
            node = RRRotation(node);
        }
    }
	node->left = insertBalanced(node->left);
	node->right = insertBalanced(node->right);
	return node;
}

// Function to insert a Key in AVL Tree
void AVL_Tree::insert(Node* node, int key) {
    if(node) {
        if(key < node->data) {
            if(node->left) {
                insert(node->left, key);
            } else {
                node->left = new Node(key);
            }
        } else {
            if(node->right) {
                insert(node->right, key);
            } else {
                node->right = new Node(key);
            }
        }
    }
}

void AVL_Tree::insert(int key) {
	std::cout << "Inserting key: " << key << std::endl;
    if(root) {
        insert(root, key);
		root = insertBalanced(root);
    } else {
        root = new Node(key);
    }
}

// Function to search for a key in AVL Tree
bool AVL_Tree::search(Node* node, int key) {
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

bool AVL_Tree::search(int key) {
    return search(root, key);
}

// Function to find the in-order predecessor of a node
Node* AVL_Tree::inOrderPre(Node* node) {
    Node* predecessor{node->left};
    if(predecessor) {
        while(predecessor->right) {
            predecessor = predecessor->right;
        }
    }
    return predecessor;
}

// Function to find the in-order successor of a node
Node* AVL_Tree::inOrderSuc(Node* node) {
    Node* successor{node->right};
    if(successor) {
        while(successor->left) {
            successor = successor->left;
        }
    }
    return successor;
}

// Function to check the balance factor of the remaining nodes after deleting the node
Node* AVL_Tree::deleteBalanced(Node* node) {
	if(!node || (!node->left && !node->right)) {
		return node;
	}
	int bfNode = balanceFactor(node);
    if(bfNode == 2) {
		int bfLeft = balanceFactor(node->left);
        if(bfLeft == 1) {
            node = LLRotation(node);
        } else {
            node = LRRotation(node);
        }
    } else if(bfNode == -2) {
		int bfRight = balanceFactor(node->right);
        if(bfRight == 1) {
            node = RLRotation(node);
        } else {
            node = RRRotation(node);
        }
    }
	node->left = deleteBalanced(node->left);
	node->right = deleteBalanced(node->right);
	return node;
}

// Function to remove a key from the AVL Tree
Node* AVL_Tree::remove(Node* node, int key) {
    if(!node) {
        return node;
    }
    if(!node->left && !node->right) {
        if(node->data == key) {
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
            Node* predecessor = inOrderPre(node);
            node->data = predecessor->data;
		    node->left = remove(node->left, predecessor->data);
        } else {
            Node* successor = inOrderSuc(node);
            node->data = successor->data;
			node->right = remove(node->right, successor->data);
        }
    }
    return node;
}

void AVL_Tree::remove(int key) {
	if(search(key)) {
		std::cout << "Removing key: " << key << std::endl;
		remove(root, key);
		root = deleteBalanced(root);
	} else {
		std::cout << "Trying to remove key: " << key << ", Key: " << key << " not found..." << std::endl;
	}
    
}

// Function to print the in-order traversal of the AVL tree
void AVL_Tree::inOrder(Node* node) {
    if(node) {
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }
}

void AVL_Tree::inOrder() {
    std::cout << "In-Order Traversal : ";
    inOrder(root);
    std::cout << std::endl;
}

// Function to print each level in a new line
void AVL_Tree::levelOrder(Node* node) {
	if(!node) {
		std::cout << "-1" << std::endl;
		return;
	}
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
		if(front->data != -1) {
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

void AVL_Tree::levelOrder() {
	std::cout << "Level Order Traversal: " << std::endl;
	levelOrder(root);
	std::cout << std::endl;
}

// Function to check whether the AVL Tree is balanced or not
bool AVL_Tree::isBalanced(Node* node) {
    if(!node) {
		return true;
	}
	if (std::abs(balanceFactor(node)) > 1) {
		return false;
	}
	bool left = isBalanced(node->left);
	bool right = isBalanced(node->right);
	return left && right;
}

bool AVL_Tree::isBalanced() {
    return isBalanced(root);
}

#endif // _AVL_TREE_

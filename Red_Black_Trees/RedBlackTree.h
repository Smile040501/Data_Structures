#ifndef _RED_BLACK_TREE_
#define _RED_BLACK_TREE_

#include<initializer_list>
#include<vector>
#include<iostream>
#include<queue>
#include<cmath>
#include "Node.h"

class RedBlackTree {		// RedBlackTree class for the whole red-black tree
private:
    Node* root;		// root node of the tree
	
	// Getters to get the required member node
	Node* getGrandParent(Node* node);
    Node* getUncle(Node* node);
    Node* getSibling(Node* node);
	Node* inOrderPredecessor(Node* node);
    Node* inOrderSuccessor(Node* node);
	
	// Utility Functions to perform various rotations
	void LLRotation(Node* node);
    void LRRotation(Node* node);
    void RRRotation(Node* node);
    void RLRotation(Node* node);
	
	// Function to make the tree color balanced
    void makeBalanced(Node* node);
	
	// Function to insert  a key in the tree
    void insert(Node* node, int key);
	
	// Function to remove a key from the tree
    void remove(Node* node, int key);
	
	// Function to get the height of the tree
	int height(Node* node);
	
	// Function to print the In-Order Traversal of the tree
	void inOrder(Node* node);
	
	// Function to print the Level Order Traversal of the tree
    void levelOrder(Node* node);
    
public:
	// Constructors
    RedBlackTree();
    RedBlackTree(std::initializer_list<int> list);
    
	// Destructor
    ~RedBlackTree();
    
	// Function to create a Red-Black Tree from the input vector
    void create(std::vector<int> vec);
    
	// Function to insert  a key in the tree
    void insert(int key);
    
	// Function to remove a key from the tree
    void remove(int key);
	
	// Function to get the height of the tree 
    int height();
	
	// Function to print the In-Order Traversal of the tree
    void inOrder();
	
	// Function to print the Level Order Traversal of the tree
    void levelOrder();
};

// Constructors
RedBlackTree::RedBlackTree()
: root{nullptr} {
}

RedBlackTree::RedBlackTree(std::initializer_list<int> list)
: root{nullptr} {
    for(auto i{std::begin(list)}; i!=std::end(list); i++) {
        insert(*i);
    }
}

// Destructor
RedBlackTree::~RedBlackTree() {
}

// Function to create the tree from the input vector
void RedBlackTree::create(std::vector<int> vec) {
    for(const auto &i: vec) {
        insert(i);
    }
}

// Getters to get the required member node
Node* RedBlackTree::getGrandParent(Node* node) {
    if(node==root || node->parent==root) {
        return nullptr;
    } else {
        return node->parent->parent;
    }
}

Node* RedBlackTree::getUncle(Node* node) {
	Node* grandParent = getGrandParent(node);
    if(grandParent) {
        if(node->parent == grandParent->left) {
            return grandParent->right;
        } else {
            return grandParent->left;
        }
    } else {
        return nullptr;
    }
}

Node* RedBlackTree::getSibling(Node* node) {
    if(node == root) {
        return nullptr;
    } else {
        if(node == node->parent->left) {
            return node->parent->right;
        } else {
            return node->parent->left;
        }
    }
}

Node* RedBlackTree::inOrderPredecessor(Node* node) {
    if(!node) {
        return nullptr;
    }
    Node* predecessor = node->left;
	while(predecessor->right) {
		predecessor = predecessor->right;
	}
    return predecessor;
}

Node* RedBlackTree::inOrderSuccessor(Node* node) {
    if(!node) {
        return nullptr;
    }
    Node* successor = node->right;
    while(successor->left) {
        successor = successor->left;
    }
    return successor;
}

// Utility function to perform various rotations
void RedBlackTree::LLRotation(Node* node) {
    Node* parent = node->parent;
    Node* second = node->left;
    if(parent) {
        if(node == parent->left) {
            parent->left = second;
        } else {
            parent->right = second;
        }
    }
    if(second->right) {
        node->left = second->right;
        second->right->parent = node;
    } else {
        node->left = nullptr;
    }
    second->right = node;
    node->parent = second;
    second->parent = parent;
    if(node==root) {
        root = second;
    }
}

void RedBlackTree::LRRotation(Node* node) {
    Node* parent = node->parent;
    Node* second = node->left;
    Node* third = second->right;
    if(third->right) {
        node->left= third->right;
        third->right->parent = node;
    } else {
        node->left = nullptr;
    }
    if(third->left) {
        second->right = third->left;
        third->left->parent = second;
    } else {
        second->right = nullptr;
    }
    if(parent) {
        if(node == parent->left) {
            parent->left = third;
        } else {
            parent->right = third;
        }
    }
    third->left = second;
    third->right = node;
    node->parent = third;
    second->parent = third;
    third->parent = parent;
    if(node==root) {
        root = third;
    }
}

void RedBlackTree::RRRotation(Node* node) {
    Node* parent = node->parent;
    Node* second = node->right;
    if(parent) {
        if(node == parent->left) {
            parent->left = second;
        } else {
            parent->right = second;
        }
    }
    if(second->left) {
        node->right = second->left;
        second->left->parent = node;
    } else {
        node->right = nullptr;
    }
    second->left = node;
    node->parent = second;
    second->parent = parent;
    if(node==root) {
        root = second;
    }
}

void RedBlackTree::RLRotation(Node* node) {
    Node* parent = node->parent;
    Node* second = node->right;
    Node* third = second->left;
    if(third->left) {
        node->right = third->left;
        third->left->parent = node;
    } else {
        node->right = nullptr;
    }
    if(third->right) {
        second->left = third->right;
        third->right->parent = second;
    } else {
        second->left = nullptr;
    }
    if(parent) {
        if(node == parent->left) {
            parent->left = third;
        } else {
            parent->right = third;
        }
    }
    third->right = second;
    third->left = node;
    node->parent = third;
    second->parent = third;
    third->parent = parent;
    if(node==root) {
        root = third;
    }
}

// Function to make the tree color balanced
void RedBlackTree::makeBalanced(Node* node) {
    if(!node) {
        return;
    } else if(node==root) {
        node->color = 'B';
    } else if(node->color == 'R' && node->parent->color == 'R') {
        Node* uncle = getUncle(node);
        if(uncle && uncle->color=='R') {		// Uncle exists and its color is Red
			Node *grandParent = getGrandParent(node);
            node->parent->color = 'B';
            uncle->color = 'B';
            grandParent->color = 'R';
            makeBalanced(grandParent);
        } else {		// Either Uncle is nullptr or color of Uncle is Black
            Node* grandParent = getGrandParent(node);
            Node* parent = node->parent;
            if(grandParent) {
                if(node==parent->left && parent==grandParent->left) {
                    LLRotation(grandParent);
                    parent->color = 'B';
                    grandParent->color = 'R';
                    node->color = 'R';
                } else if(node==parent->right && parent==grandParent->left) {
                    LRRotation(grandParent);
                    node->color = 'B';
                    parent->color = 'R';
                    grandParent->color = 'R';
                } else if(node==parent->right && parent==grandParent->right) {
                    RRRotation(grandParent);
                    parent->color = 'B';
                    grandParent->color = 'R';
                    node->color = 'R';
                } else if(node==parent->left && parent==grandParent->right) {
                    RLRotation(grandParent);
                    node->color = 'B';
                    parent->color = 'R';
                    grandParent->color = 'R';
                }
            } else {
                node->parent->flipColor();
            }
        }
    }
}

// Function to insert a key to the tree
void RedBlackTree::insert(Node* node, int key) {
    if(key < node->data) {
        if(node->left) {
            insert(node->left, key);
        } else {
            node->left = new Node(key);
            node->left->parent = node;
            makeBalanced(node->left);
        }
    } else {
        if(node->right) {
            insert(node->right, key);
        } else {
            node->right = new Node(key);
            node->right->parent = node;
            makeBalanced(node->right);
        }
    }
}

void RedBlackTree::insert(int key) {
	std::cout << "Inserting key: " << key << std::endl;
    if(root) {
        insert(root, key);
    } else {
        root = new Node(key, 'B');
    }
}

// Function to remove a key from the tree
void RedBlackTree::remove(Node* node, int key) {
    if(node) {  	// If node exists
        if(key < node->data) {   		// When node value is greater than key
            remove(node->left, key);
        } else if(key > node->data) {   	// When node value is less than key
            remove(node->right, key);
        } else {  // When node value is equal to key
            if(node->left || node->right) { 	 // When node is not a leaf node
                if(height(node->left) > height(node->right)) {
                    Node* predecessor = inOrderPredecessor(node);
                    node->data = predecessor->data;
                    remove(node->left, predecessor->data);
                } else {
                    Node* successor = inOrderSuccessor(node);
                    node->data = successor->data;
                    remove(node->right, successor->data);
                }
            } else {  	// When node is a leaf node
                if(node==root) {
                    Node* temp = root;
                    root = nullptr;
                    delete temp;
                } else {
                    if(node->color == 'R') { 		// When color of leaf node is Red
                        if(node == node->parent->left) {
                            node->parent->left = nullptr;
                        } else {
                            node->parent->right = nullptr;
                        }
                        node->parent = nullptr;
                        delete node;
                    } else {  		// When color of leaf node is Black
                        Node* parent = node->parent;
                        Node* sibling = getSibling(node);
                        if(!sibling) {  	// When sibling doesn't exists
                            parent->color = 'B';
                            if(node == parent->left) {
                                parent->left = nullptr;
                            } else {
                                parent->right = nullptr;
                            }
                            node->parent = nullptr;
                            delete node;
                        } else {  	// When sibling exists
                            Node* siblingLeftChild = sibling->left;
                            Node* siblingRightChild = sibling->right;
                            if(sibling->color == 'R') {  // When color of sibling is Red
                                if(sibling == parent->left) {
                                    LLRotation(parent);
                                    parent->right = nullptr;
                                    if(parent->left) {
                                        parent->left->flipColor();
                                    }
                                } else {
                                    RRRotation(parent);
                                    parent->left = nullptr;
                                    if(parent->right) {
                                        parent->right->flipColor();
                                    }
                                }
                                makeBalanced(sibling);
                            } else {  // When color of sibling is Black
                                if( (!siblingLeftChild && !siblingRightChild) || (!siblingLeftChild && (siblingRightChild && siblingRightChild->color=='B')) || (!siblingRightChild && (siblingLeftChild && siblingLeftChild->color=='B')) || ((siblingLeftChild && siblingLeftChild->color=='B') && (siblingRightChild && siblingRightChild->color=='B')) ) {
									  // Sibling has both Black children
                                    sibling->color = 'R';
                                    parent->color = 'B';
                                } else {  // Sibling has atleast one Red Child
                                    if( ((siblingLeftChild && siblingLeftChild->color=='R') && (siblingRightChild && siblingRightChild->color=='R')) ) {   // When both the children are Red
                                        if(sibling == parent->left) {
                                            LRRotation(parent);
                                            if(parent->left) {
                                                parent->left->flipColor();
                                            }
                                            if(sibling->right) {
                                                sibling->right->flipColor();
                                            }
                                            sibling->parent->left->color = 'B';
                                            sibling->parent->right->color = 'B';
                                            makeBalanced(sibling->parent);
                                        } else {
                                            RLRotation(parent);
                                            if(parent->right) {
                                                parent->right->flipColor();
                                            }
                                            if(sibling->left) {
                                                sibling->left->flipColor();
                                            }
                                            sibling->parent->left->color = 'B';
                                            sibling->parent->right->color = 'B';
                                            makeBalanced(sibling->parent);
                                        }
                                    } else {
                                        if( (siblingLeftChild && siblingLeftChild->color=='R') ) {  // When left child of sibling is Red
                                            if(sibling == parent->left) {
                                                LLRotation(parent);
                                                if(parent->left) {
                                                    parent->left->flipColor();
                                                }
                                                sibling->color = parent->color;
                                                sibling->left->color = 'B';
                                                sibling->right->color = 'B';
                                            } else {
                                                RLRotation(parent);
                                                if(parent->right) {
                                                    parent->right->flipColor();
                                                }
                                                if(sibling->left) {
                                                    sibling->left->flipColor();
                                                }
                                                sibling->parent->left->color = 'B';
                                                sibling->parent->right->color = 'B';
                                                makeBalanced(sibling->parent);
                                            }
                                        } else if( (siblingRightChild && siblingRightChild->color=='R') ) {  // When right child of sibling is Red
                                            if(sibling == parent->left) {
                                                LRRotation(parent);
                                                if(parent->left) {
                                                    parent->left->flipColor();
                                                }
                                                if(sibling->right) {
                                                    sibling->right->flipColor();
                                                }
                                                sibling->parent->left->color = 'B';
                                                sibling->parent->right->color = 'B';
                                                makeBalanced(sibling->parent);
                                            } else {
                                                RRRotation(parent);
                                                if(parent->right) {
                                                    parent->right->flipColor();
                                                }
                                                sibling->color = parent->color;
                                                sibling->left->color = 'B';
                                                sibling->right->color = 'B';
                                            }
                                        }
                                    }
                                }
                            }
                            if(node == parent->left) {
                                parent->left = nullptr;
                            } else {
                                parent->right = nullptr;
                            }
                            node->parent = nullptr;
                            delete node;
                        }
                    }
                }
            }
        }
    } else {
        return;
    }
}

void RedBlackTree::remove(int key) {
	std::cout << "Removing key: " << key << std::endl;
    if(root) {
        remove(root, key);
    }
}

// Function to calculate the height of the tree
int RedBlackTree::height(Node* node) {
    if(node) {
        int x{height(node->left)};
        int y{height(node->right)};
        return std::fmax(x, y) + 1;
    } else {
        return 0;
    }
}

int RedBlackTree::height() {
	return height(root);
}

// Function to print the In-Order Traversal of the tree
void RedBlackTree::inOrder(Node* node) {
    if(node) {
        inOrder(node->left);
        std::cout << node->color << ":" << node->data << "  ";
        inOrder(node->right);
    }
}

void RedBlackTree::inOrder() {
    std::cout << "In-Order Traversal: ";
	inOrder(root);
    std::cout << std::endl;
}

// Function to print the Level Order Traversal of the tree
void RedBlackTree::levelOrder(Node* node) {
	std::queue<Node*> nodeQueue;
    nodeQueue.push(node);
    nodeQueue.push(nullptr);
	while(!nodeQueue.empty()) {
		Node* front = nodeQueue.front();
		nodeQueue.pop();
		if(front==nullptr) {
			if(nodeQueue.empty()) {
				break;
			}
			std::cout << std::endl;
			nodeQueue.push(nullptr);
			continue;
		}
		if(front->data != -1) {
			std::cout << front->color << ":";
		}
		std::cout << front->data << "  ";
		if(front->data!=-1) {
			if(front->left) {
				nodeQueue.push(front->left);
			} else {
				nodeQueue.push(new Node(-1));
			}
			if(front->right) {
				nodeQueue.push(front->right);
			} else {
				nodeQueue.push(new Node(-1));
			}
		}
	}
}

void RedBlackTree::levelOrder() {
	std::cout << "Level Order Traversal: " << std::endl;
    levelOrder(root);
    std::cout << std::endl;
}


#endif // _RED_BLACK_TREE_

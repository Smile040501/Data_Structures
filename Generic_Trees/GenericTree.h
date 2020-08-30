#ifndef _GENERIC_TREE_
#define _GENERIC_TREE_

#include "Node.h"
#include<vector>
#include<queue>
#include<cmath>

class GenericTree {		// GenericTree class for representing a generic tree

private:
	Node *root;			// root of the tree
	
	// Function to return the number of nodes of the tree
	int countNodes(Node *node);
	
	// Function to return the height of the tree
	int height(Node *node);
	
	// Function to print the level order traversal of the tree
	void levelOrder(Node *node);
	
	// Function to print the pre-order traversal of the tree
	void preOrder(Node *node);
	
	// Function to print the post-order traversal of the tree
	void postOrder(Node *node);

public:
	GenericTree();
	
	~GenericTree();
	
	// Function to take the input tree
	void createTree();
	
	// Function to return the number of nodes of the tree
	int countNodes();
	
	// Function to return the height of the tree
	int height();
	
	// Function to print the level order traversal of the tree
	void levelOrder();
	
	// Function to print the pre-order traversal of the tree
	void preOrder();
	
	// Function to print the post-order traversal of the tree
	void postOrder();
};

// Constructor
GenericTree::GenericTree()
: root{nullptr} {
}

// Destructor
GenericTree::~GenericTree() {
	delete root;
}

// Function to take the input tree
void GenericTree::createTree() {
	int rootValue=0;
	std::cout << "Enter the root value: ";
	std::cin >> rootValue;
	root = new Node(rootValue);
	std::queue<Node*> helper;
	helper.push(root);
	while(!helper.empty()) {
		Node *front = helper.front();
		helper.pop();
		int numChildren=0;
		std::cout << "Enter the number of children of " << front->data << ": ";
		std::cin >> numChildren;
		if(numChildren!=0) {
			std::cout << "Enter the children of " << front->data << " separated by spaces: ";
			for(int i=0; i<numChildren; i++) {
				int nodeValue=0;
				std::cin >> nodeValue;
				front->children->push_back(new Node(nodeValue));
				helper.push(front->children->at(i));
			}
		}
	}
}

// Function to print the level order traversal of the tree
void GenericTree::levelOrder(Node *node) {
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
			if(front->children->size()==0) {
				helper.push(new Node(-1));
			} else {
				for(int i=0; i<front->children->size(); i++) {
					helper.push(front->children->at(i));
				}
			}
		}
	}
}

void GenericTree::levelOrder() {
	std::cout << "Level Order Traversal: " << std::endl;
	levelOrder(root);
	std::cout << std::endl;
}

// Function to return the number of nodes of the tree
int GenericTree::countNodes(Node *node) {
	int ans=1;
	for(int i=0; i<node->children->size(); i++) {
		ans += countNodes(node->children->at(i));
	}
	return ans;
}

int GenericTree::countNodes() {
	return countNodes(root);
}

// Function to return the height of the tree
int GenericTree::height(Node *node) {
	int ans=0;
	for(int i=0; i<node->children->size(); i++) {
		ans = std::fmax(ans, height(node->children->at(i)));
	}
	return ans+1;
}

int GenericTree::height() {
	return height(root);
}

// Function to print the pre-order traversal of the tree
void GenericTree::preOrder(Node *node) {
	if(node) {
		std::cout << node->data << " ";
		for(int i=0; i<node->children->size(); i++) {
			preOrder(node->children->at(i));
		}
	}
}

void GenericTree::preOrder() {
	std::cout << "Pre-Order Traversal: ";
	preOrder(root);
	std::cout << std::endl;
}

// Function to print the post-order traversal of the tree
void GenericTree::postOrder(Node *node) {
	if(node) {
		for(int i=0; i<node->children->size(); i++) {
			postOrder(node->children->at(i));
		}
		std::cout << node->data << " ";
	}
}

void GenericTree::postOrder() {
	std::cout << "Post-order Traversal: ";
	postOrder(root);
	std::cout << std::endl;
}

#endif // _GENERIC_TREE_

#ifndef _BINARY_TREE_
#define _BINARY_TREE_

#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

#include "Node.h"

class BinaryTree {  // BinaryTree class for representing Binary Trees
   private:
    Node* root;  // root of the tree

    // Function to count the total number of nodes in the tree
    int countTotalNodes(Node* node);
    // Function to count the number of degree 0 nodes i.e. leaf nodes in the tree
    int countDegreeZeroNodes(Node* node);
    // Function to count the number of degree 1 nodes i.e. nodes having only one child
    int countDegreeOneNodes(Node* node);
    // Function to count the number of degree 2 nodes i.e. nodes having both the children
    int countDegreeTwoNodes(Node* node);

    // Function to calculate the height of the tree
    int height(Node* node);

    // Function to print the pre-order traversal of the tree
    void preOrder(Node* node);
    // Function to print the in-order traversal of the tree
    void inOrder(Node* node);
    // Function to print the post-order traversal of the tree
    void postOrder(Node* node);
    // Function to print the level order traversal of the tree
    void levelOrder(Node* node);

    // Function to create the tree from given pre-order and in-order
    Node* createTreeFromPreInOrder(std::vector<int> preOrder, std::vector<int> inOrder, int preS, int preE, int inS, int inE);
    // Function to create the tree from given post-order and in-order
    Node* createTreeFromPostInOrder(std::vector<int> postOrder, std::vector<int> inOrder, int postS, int postE, int inS, int inE);

   public:
    // Constructors
    BinaryTree();

    // Destructor
    ~BinaryTree();

    // Function to take the input binary tree from the user
    void createTree();

    // Function to count the total number of nodes in the tree
    int countTotalNodes();
    // Function to count the number of degree 0 nodes i.e. leaf nodes in the tree
    int countDegreeZeroNodes();
    // Function to count the number of degree 1 nodes i.e. nodes having only one child
    int countDegreeOneNodes();
    // Function to count the number of degree 2 nodes i.e. nodes having both the children
    int countDegreeTwoNodes();

    // Function to calculate the height of the tree
    int height();

    // Function to print the pre-order traversal of the tree
    void preOrder();
    // Function to print the in-order traversal of the tree
    void inOrder();
    // Function to print the post-order traversal of the tree
    void postOrder();
    // Function to print the level order traversal of the tree
    void levelOrder();

    // Function to create the tree from given pre-order and in-order
    void createTreeFromPreInOrder(std::vector<int> preOrder, std::vector<int> inOrder);
    // Function to create the tree from given post-order and in-order
    void createTreeFromPostInOrder(std::vector<int> postOrder, std::vector<int> inOrder);
};

// Constructors
BinaryTree::BinaryTree()
    : root{nullptr} {
}

// Destructor
BinaryTree::~BinaryTree() {
    delete root;
}

// Function to take the input binary tree from the user
void BinaryTree::createTree() {
    int rootValue = 0;
    std::cout << "Enter root value : ";
    std::cin >> rootValue;
    root = new Node(rootValue);

    std::queue<Node*> ptrQueue;
    ptrQueue.push(root);

    while (!ptrQueue.empty()) {
        Node* p = ptrQueue.front();
        ptrQueue.pop();
        int nodeValue = 0;

        std::cout << "Enter the left child of " << p->data << " : ";
        std::cin >> nodeValue;
        if (nodeValue != -1) {
            p->left = new Node(nodeValue);
            ptrQueue.push(p->left);
        }

        std::cout << "Enter the right child of " << p->data << " : ";
        std::cin >> nodeValue;
        if (nodeValue != -1) {
            p->right = new Node(nodeValue);
            ptrQueue.push(p->right);
        }
    }
    std::cout << std::endl;
}

// Function to count the total number of nodes in the tree
int BinaryTree::countTotalNodes(Node* node) {
    if (node) {
        return countTotalNodes(node->left) + countTotalNodes(node->right) + 1;
    } else {
        return 0;
    }
}

int BinaryTree::countTotalNodes() {
    return countTotalNodes(root);
}

// Function to count the number of degree 0 nodes i.e. leaf nodes in the tree
int BinaryTree::countDegreeZeroNodes(Node* node) {
    if (node) {
        int x = countDegreeZeroNodes(node->left);
        int y = countDegreeZeroNodes(node->right);
        if (!node->left && !node->right) {
            return x + y + 1;
        } else {
            return x + y;
        }
    } else {
        return 0;
    }
}

int BinaryTree::countDegreeZeroNodes() {
    return countDegreeZeroNodes(root);
}

// Function to count the number of degree 1 nodes i.e. nodes having only one child
int BinaryTree::countDegreeOneNodes(Node* node) {
    if (node) {
        int x = countDegreeOneNodes(node->left);
        int y = countDegreeOneNodes(node->right);
        if (!node->left ^ !node->right) {
            return x + y + 1;
        } else {
            return x + y;
        }
    } else {
        return 0;
    }
}

int BinaryTree::countDegreeOneNodes() {
    return countDegreeOneNodes(root);
}

// Function to count the number of degree 2 nodes i.e. nodes having both the children
int BinaryTree::countDegreeTwoNodes(Node* node) {
    if (node) {
        int x = countDegreeTwoNodes(node->left);
        int y = countDegreeTwoNodes(node->right);
        if (node->left && node->right) {
            return x + y + 1;
        } else {
            return x + y;
        }
    } else {
        return 0;
    }
}

int BinaryTree::countDegreeTwoNodes() {
    return countDegreeTwoNodes(root);
}

// Function to calculate the height of the tree
int BinaryTree::height(Node* node) {
    if (node) {
        int x = height(node->left);
        int y = height(node->right);
        return std::fmax(x, y) + 1;
    } else {
        return 0;
    }
}

int BinaryTree::height() {
    return height(root);
}

// Function to print the pre-order traversal of the tree
void BinaryTree::preOrder(Node* node) {
    if (node) {
        std::cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

void BinaryTree::preOrder() {
    std::cout << "Pre-Order Traversal : ";
    preOrder(root);
    std::cout << std::endl;
}

// Function to print the in-order traversal of the tree
void BinaryTree::inOrder(Node* node) {
    if (node) {
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }
}

void BinaryTree::inOrder() {
    std::cout << "In-Order Traversal : ";
    inOrder(root);
    std::cout << std::endl;
}

// Function to print the post-order traversal of the tree
void BinaryTree::postOrder(Node* node) {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << " ";
    }
}

void BinaryTree::postOrder() {
    std::cout << "Post-Order Traversal : ";
    postOrder(root);
    std::cout << std::endl;
}

// Function to print the level order traversal of the tree
void BinaryTree::levelOrder(Node* node) {
    if (!node) {
        std::cout << "-1" << std::endl;
        return;
    }
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
            std::cout << std::endl;
            helper.push(nullptr);
            continue;
        }
        std::cout << front->data << " ";
        if (front->data != -1) {
            if (front->left) {
                helper.push(front->left);
            } else {
                helper.push(new Node(-1));
            }
            if (front->right) {
                helper.push(front->right);
            } else {
                helper.push(new Node(-1));
            }
        }
    }
}

void BinaryTree::levelOrder() {
    std::cout << "Level Order Traversal: " << std::endl;
    levelOrder(root);
    std::cout << std::endl;
}

//Function to create the tree from given pre-order and in-order
Node* BinaryTree::createTreeFromPreInOrder(std::vector<int> preOrder, std::vector<int> inOrder, int preS, int preE, int inS, int inE) {
    if (preS > preE || inS > inE) {
        return nullptr;
    }
    int rootData = preOrder[preS];
    int rootIndex = 0;
    for (int i = inS; i <= inE; i++) {
        if (inOrder[i] == rootData) {
            rootIndex = i;
            break;
        }
    }
    int lInS = inS;
    int lInE = rootIndex - 1;
    int lPreS = preS + 1;
    int lPreE = lInE - lInS + lPreS;
    int rPreS = lPreE + 1;
    int rPreE = preE;
    int rInS = rootIndex + 1;
    int rInE = inE;
    Node* rootNode = new Node(rootData);
    rootNode->left = createTreeFromPreInOrder(preOrder, inOrder, lPreS, lPreE, lInS, lInE);
    rootNode->right = createTreeFromPreInOrder(preOrder, inOrder, rPreS, rPreE, rInS, rInE);
    return rootNode;
}

void BinaryTree::createTreeFromPreInOrder(std::vector<int> preOrder, std::vector<int> inOrder) {
    root = createTreeFromPreInOrder(preOrder, inOrder, 0, preOrder.size() - 1, 0, inOrder.size() - 1);
}

//Function to create the tree from given post-order and in-order
Node* BinaryTree::createTreeFromPostInOrder(std::vector<int> postOrder, std::vector<int> inOrder, int postS, int postE, int inS, int inE) {
    if (postS > postE || inS > inE) {
        return nullptr;
    }
    int rootData = postOrder[postE];
    int rootIndex = 0;
    for (int i = inS; i <= inE; i++) {
        if (inOrder[i] == rootData) {
            rootIndex = i;
            break;
        }
    }
    int lInS = inS;
    int lInE = rootIndex - 1;
    int lPostS = postS;
    int lPostE = lInE - lInS + lPostS;
    int rPostS = lPostE + 1;
    int rPostE = postE - 1;
    int rInS = rootIndex + 1;
    int rInE = inE;
    Node* rootNode = new Node(rootData);
    rootNode->left = createTreeFromPostInOrder(postOrder, inOrder, lPostS, lPostE, lInS, lInE);
    rootNode->right = createTreeFromPostInOrder(postOrder, inOrder, rPostS, rPostE, rInS, rInE);
    return rootNode;
}

void BinaryTree::createTreeFromPostInOrder(std::vector<int> postOrder, std::vector<int> inOrder) {
    root = createTreeFromPostInOrder(postOrder, inOrder, 0, postOrder.size() - 1, 0, inOrder.size() - 1);
}

#endif  // _BINARY_TREE_

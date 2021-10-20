#include <iostream>
#include <vector>

#include "BinaryTree.h"

// Sample Main

// Test tree: 5 6 10 11 9 -1 15 -1 -1 1 4 -1 20 14 -1 2 -1 16 12 -1 -1 -1 7 3 8 -1 -1 -1 -1 -1 -1 13 -1 -1 -1
// Number of nodes = 17
// Pre-Order: 5 6 11 9 1 14 4 2 7 10 15 20 16 3 8 13 12
// In-Order: 11 6 14 1 9 2 7 4 5 10 15 3 16 13 8 20 12
// Post-Order: 11 14 1 7 2 4 9 6 3 13 8 16 12 20 15 10 5
int main() {
    BinaryTree tree;
    tree.createTree();

    tree.levelOrder();

    std::cout << "Total number of nodes : " << tree.countTotalNodes() << std::endl;
    std::cout << "Degree 0 nodes : " << tree.countDegreeZeroNodes() << std::endl;
    std::cout << "Degree 1 nodes : " << tree.countDegreeOneNodes() << std::endl;
    std::cout << "Degree 2 nodes : " << tree.countDegreeTwoNodes() << std::endl;
    std::cout << "Height : " << tree.height() << std::endl;

    tree.preOrder();
    tree.inOrder();
    tree.postOrder();

    std::cout << std::endl;

    int numOfNodesPreIn = 0;
    std::cout << "Enter the number of nodes of the tree : ";
    std::cin >> numOfNodesPreIn;
    std::cout << "Enter the Pre-Order traversal of elements separated by spaces : ";
    std::vector<int> preOrder;
    for (int i{}; i < numOfNodesPreIn; i++) {
        int node = 0;
        std::cin >> node;
        preOrder.push_back(node);
    }
    std::cout << "Enter the In-Order traversal of elements separated by spaces : ";
    std::vector<int> inOrder{};
    for (int i{}; i < numOfNodesPreIn; i++) {
        int node{};
        std::cin >> node;
        inOrder.push_back(node);
    }

    BinaryTree preInTree;
    preInTree.createTreeFromPreInOrder(preOrder, inOrder);
    preInTree.levelOrder();

    std::cout << std::endl;

    int numOfNodesPostIn{};
    std::cout << "Enter the number of nodes of the tree : ";
    std::cin >> numOfNodesPostIn;
    std::cout << "Enter the Post-Order traversal of elements separated by spaces : ";
    std::vector<int> postOrder{};
    for (int i{}; i < numOfNodesPostIn; i++) {
        int node{};
        std::cin >> node;
        postOrder.push_back(node);
    }
    //std::cout << "Enter the In-Order traversal of elements separated by spaces : ";
    //std::vector<int> inOrder{};
    //for(int i{}; i<numOfNodesPostIn; i++) {
    //    int node{};
    //    std::cin >> node;
    //    inOrder.push_back(node);
    //}

    BinaryTree postInTree{};
    postInTree.createTreeFromPostInOrder(postOrder, inOrder);
    postInTree.levelOrder();

    std::cout << std::endl;

    std::cout << std::endl;
    return 0;
}

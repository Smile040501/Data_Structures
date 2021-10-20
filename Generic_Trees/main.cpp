#include <iostream>

#include "GenericTree.h"

// Sample main

// Test tree: 10 3 18 20 25 2 4 1 4 6 15 13 40 1 19 1 24 0 1 16 2 12 17 0 3 14 30 35 0 0 1 11 2 7 5 1 2 0 1 21 2 23 27 0 0 1 3 2 9 8 0 0 0 0 0 0
int main() {
    GenericTree tree;
    tree.createTree();

    tree.levelOrder();

    std::cout << "Total number of nodes: " << tree.countNodes() << std::endl;
    std::cout << "Height of the tree: " << tree.height() << std::endl;

    tree.preOrder();
    tree.postOrder();

    std::cout << std::endl;
    return 0;
}

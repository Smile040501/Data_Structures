#include <iostream>

#include "RedBlackTree.h"

// Sample Main
int main() {
    RedBlackTree tree{7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};

    tree.levelOrder();

    std::cout << "Height of the tree: " << tree.height() << std::endl;

    tree.insert(15);

    tree.levelOrder();

    tree.inOrder();

    tree.remove(10);

    tree.levelOrder();

    std::cout << std::endl;
    return 0;
}

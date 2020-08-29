# include<iostream>
#include "TwoThreeFourTree.h"

// Sample main
int main() {
    TwoThreeFourTree tree{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
	
	tree.levelOrder();
	
	std::cout << "Height of the tree: " << tree.height() << std::endl;
	
	tree.insert(120);
	tree.levelOrder();
	tree.inOrder();
	
	tree.remove(40);
	tree.levelOrder();

    std::cout << std::endl;
    return 0;
}

#include<iostream>
#include<iomanip>
#include "BST.h"

// Sample main
int main() {
    BST tree{5, 6, 11, 9, 1, 14, 4, 2, 7, 10, 15, 20, 16, 3, 8, 13, 12};
	
	tree.levelOrder();
	tree.inOrder();
	
	std::cout << "Height of the tree: " << tree.height() << std::endl;
	std::cout << "Is Tree BST: " << std::boolalpha << tree.checkBST() << std::endl;
	
	tree.insert(18);
	tree.levelOrder();
	std::cout << "Height of the tree: " << tree.height() << std::endl;
	std::cout << "Is Tree BST: " << std::boolalpha << tree.checkBST() << std::endl;
	
	tree.remove(5);
	tree.levelOrder();
	std::cout << "Is Tree BST: " << std::boolalpha << tree.checkBST() << std::endl;
    
    std::cout << std::endl;
    return 0;
}

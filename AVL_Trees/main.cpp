# include<iostream>
#include<iomanip>
#include "AVL_Tree.h"
using namespace std;

// Sample Main
int main() {
	AVL_Tree tree{10, 5, 1, 9, 8, 4, 0, 12, 3, 7, 2, 11};
	tree.levelOrder();
	std::cout << std::endl << "Height of the tree: " << tree.height() << std::endl;
	std::cout << std::endl << "Is Tree Balanced: " << std::boolalpha << tree.isBalanced() << std::endl;
	tree.insert(11);
	tree.levelOrder();
	tree.inOrder();
	std::cout << std::endl << "Is Tree Balanced: " << std::boolalpha << tree.isBalanced() << std::endl;
	std::cout << std::endl << "Is 8 present: " << tree.search(8) << std::endl;
	std::cout << std::endl << "Is 20 present: " << tree.search(20) << std::endl;
	
	tree.remove(5);
	tree.levelOrder();
	std::cout << std::endl << "Is Tree Balanced: " << std::boolalpha << tree.isBalanced() << std::endl;
	tree.remove(7);
	tree.levelOrder();
	std::cout << std::endl << "Is Tree Balanced: " << std::boolalpha << tree.isBalanced() << std::endl;
    
    std::cout << std::endl;
    return 0;
}

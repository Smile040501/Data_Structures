#include<iostream>
using namespace std;

#include "MinMaxHeap.h"

// Sample Main
int main() {
	
	MinMaxHeap heap1{7, 20, 12, 50, 45, 70, 40, 9, 30, 10, 15};
	heap1.print();
	cout << "Size of Heap: " << heap1.size() << endl;
	cout << "Minimum element in the heap: " << heap1.topMin() << endl;
	cout << "Maximum element in the heap: " << heap1.topMax() << endl;
	heap1.push(5);
	heap1.push(85);
	heap1.print();
	cout << "Minimum element in the heap: " << heap1.topMin() << endl;
	cout << "Maximum element in the heap: " << heap1.topMax() << endl;
	
	cout << "Elements in decreasing order: ";
	while(!heap1.empty()) {
		cout << heap1.topMax() << " ";
		heap1.popMax();
	}
	cout << endl;
	
	MinMaxHeap heap2{20, 31, 23, 42, 79, 4, 54, 52, 12, 32, 19, 63, 59, 11};
	heap2.print();
	
	cout << "Elements in increasing order: ";
	while(!heap2.empty()) {
		cout << heap2.topMin() << " ";
		heap2.popMin();
	}
	cout << endl;
	
	std::cout << std::endl;
	return 0;
}

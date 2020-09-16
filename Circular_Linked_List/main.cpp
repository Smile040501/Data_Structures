#include<iostream>
#include<iomanip>
using namespace std;

#include "SinglyCircularLinkedList.h"

// Sample main
int main() {
	SinglyCircularLinkedList list{1, 2, 3, 4, 5};
	
	list.makeLoop(2);
	list.print();
	cout << "Size of the linked list: " << list.size() << endl;
	cout << "Is list empty: " << boolalpha << list.isEmpty() << endl;
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	cout << "Length of the loop: " << list.loopLength() << endl;
	
	
	list.push_back(6);
	list.push_front(0);
	list.print();
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	
	list.pop_back();
	list.pop_front();
	list.print();
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	
	list.insert(6, 4);
	list.print();
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	
	list.erase(3);
	list.print();
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	
	list.reverse();
	list.print();
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	
	list.removeLoop();
	list.print();
	cout << "Is loop present: " << boolalpha << list.hasLoop() << endl;
	
	list.clear();
	cout << "Is list empty: " << boolalpha << list.isEmpty() << endl;
	
	cout << endl;
	return 0;
}

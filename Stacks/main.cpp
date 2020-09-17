#include<iostream>
#include<iomanip>
using namespace std;

#include "Stack.h"

// Sample main
int main() {
	Stack s1;
	s1.push(10);
	s1.push(20);
	s1.push(30);
	s1.push(40);
	s1.push(50);
	s1.print();
	
	cout << "Top most element: " << s1.top() << endl;
	cout << "Size of the stack: " << s1.size() << endl;
	cout << "Is empty stack: " << boolalpha << s1.is_empty() << endl;
	
	s1.pop();
	s1.pop();
	cout << "Top most element: " << s1.top() << endl;
	cout << "Size of the stack: " << s1.size() << endl;
	
	Stack s2;
	s2.push(11);
	s2.push(22);
	s2.push(33);
	s2.push(44);
	s2.push(55);
	
	cout << "Initially the two stacks..." << endl;
	s1.print();
	s2.print();
	
	cout << "Swapping the two stacks..." << endl;
	s1.swap(s2);
	s1.print();
	s2.print();
	
	cout << endl;
	return 0;
}

#ifndef _STACK_
#define _STACK_

#include "Node.h"
#include<climits>

class Stack {			// Stack class for representing a stack

private:
	Node *topNode;		// Top node element of the stack
	int count;		// Size of the stack
	
public:
	// Constructor
	Stack();
	
	// Destructor
	~Stack();
	
	// Function to push an element to the stack
	void push(int data);
	// Function to pop out an element from the stack
	void pop();
	// Function to return the topmost element of the stack
	int top();
	// Function to return the size of the stack
	int size();
	// Function to return if the stack is empty of not
	bool is_empty();
	// Function to swap the two stacks
	void swap(Stack &s);
	
	// Function to print the stack elements
	void print();

};

// Constructor
Stack::Stack()
: topNode{nullptr}, count{} {
}

// Destructor
Stack::~Stack() {
	if(topNode) {
		delete topNode;
	}
}

// Function to push an element to the stack
void Stack::push(int data) {
	Node *newNode = new Node(data);
	if(topNode) {
		newNode->bottom = topNode;
		topNode = newNode;
	} else {
		topNode = newNode;
	}
	count++;
}

// Function to pop out an element from the stack
void Stack::pop() {
	if(!topNode) {
		return;
	}
	Node *nodeToDelete = topNode;
	topNode = topNode->bottom;
	nodeToDelete->bottom = nullptr;
	delete nodeToDelete;
	count--;
}

// Function to return the topmost element of the stack
int Stack::top() {
	if(topNode) {
		return topNode->data;
	} else {
		return INT_MIN;
	}
}
// Function to return the size of the stack
int Stack::size() {
	return count;
}

// Function to return if the stack is empty of not
bool Stack::is_empty() {
	return count==0;
}

// Function to swap the two stacks
void Stack::swap(Stack &s) {
	Node *temp1 = topNode;
	topNode = s.topNode;
	s.topNode = temp1;
	
	int temp2 = count;
	count = s.count;
	s.count = temp2;
}

// Function to print the stack elements
void Stack::print() {
	cout << "The Stack is: ";
	Node *curr = topNode;
	while(curr) {
		cout << curr->data << " ";
		curr = curr->bottom;
	}
	cout << endl;
}

#endif // _STACK_

#ifndef _DEQUEUE_
#define _DEQUEUE_

#include "Node.h"
#include<climits>

class Dequeue {			// Dequeue class for representing a dequeue
private:
	Node *head;		// Head node of the linked list representing dequeue
	Node *tail;		// Tail node of the linked list representing dequeue
	int count;			// Number of elements in the dequeue
	
public:
	// Constructors
	Dequeue();
	
	// Destructor
	~Dequeue();
	
	// Function to push an element to the back of the dequeue
	void push_back(int data);
	// Function to push an element to the front of the dequeue
	void push_front(int data);
	// Function to pop an element from the back of the dequeue
	void pop_back();
	// Function to pop an element from the front of the dequeue
	void pop_front();
	// Function to return the frontmost element of the dequeue
	int front();
	// Function to return the last element of the dequeue
	int back();
	// Function to return the size of the dequeue
	int size();
	// Function to return if the dequeue is empty of not
	bool empty();
	// Function to swap the two dequeues
	void swap(Dequeue &q);
	
	// Function to print the dequeue elements
	void print();
	// Function to print the dequeue elements in reverse
	void printReverse();

};

// Constructors
Dequeue::Dequeue()
: head{nullptr}, tail{nullptr}, count{} {
}

// Destructor
Dequeue::~Dequeue() {
	Node *curr = head;
	while(curr) {
		Node *nodeToDelete = curr;
		curr = curr->next;
		if(curr) {
			curr->prev = nullptr;
		}
		nodeToDelete->next = nullptr;
		delete nodeToDelete;
	}
	head = tail = nullptr;
	count = 0;
}

// Function to push an element to the back of the dequeue
void Dequeue::push_back(int data) {
	Node *newNode = new Node(data);
	if(tail) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	} else {
		head = tail = newNode;
	}
	count++;
}

// Function to push an element to the front of the dequeue
void Dequeue::push_front(int data) {
	Node *newNode = new Node(data);
	if(head) {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	} else {
		head = tail = newNode;
	}
	count++;
}

// Function to pop an element from the back of the dequeue
void Dequeue::pop_back() {
	if(!tail) {
		return;
	} else if(head==tail) {
		Node *nodeToDelete = tail;
		head = tail = nullptr;
		delete nodeToDelete;
		count = 0;
		return;
	}
	Node *nodeToDelete = tail;
	tail = tail->prev;
	tail->next = nullptr;
	nodeToDelete->prev = nullptr;
	delete nodeToDelete;
	count--;
}

// Function to pop an element from the front of the dequeue
void Dequeue::pop_front() {
	if(!head) {
		return;
	} else if(head==tail) {
		Node *nodeToDelete = head;
		head = tail = nullptr;
		delete nodeToDelete;
		count = 0;
		return;
	}
	Node *nodeToDelete = head;
	head = head->next;
	head->prev = nullptr;
	nodeToDelete->next = nullptr;
	delete nodeToDelete;
	count--;
}

// Function to return the frontmost element of the dequeue
int Dequeue::front() {
	if(head) {
		return head->data;
	} else {
		return INT_MIN;
	}
}

// Function to return the last element of the dequeue
int Dequeue::back() {
	if(tail) {
		return tail->data;
	} else {
		return INT_MIN;
	}
}

// Function to return the size of the dequeue
int Dequeue::size() {
	return count;
}

// Function to return if the dequeue is empty of not
bool Dequeue::empty() {
	return count==0;
}

// Function to swap the two dequeues
void Dequeue::swap(Dequeue &q) {
	Node *temp1 = head, *temp2 = tail;
	head = q.head;
	tail = q.tail;
	q.head = temp1;
	q.tail = temp2;
	
	int temp3 = count;
	count = q.count;
	q.count = temp3;
}

// Function to print the dequeue elements
void Dequeue::print() {
	cout << "The Dequeu is: ";
	Node *curr = head;
	while(curr) {
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}

// Function to print the dequeue elements in reverse
void Dequeue::printReverse() {
	cout << "The reverse Dequeue is: ";
	Node *curr = tail;
	while(curr) {
		cout << curr->data << " ";
		curr = curr->prev;
	}
	cout << endl;
}

#endif // _DEQUEUE_

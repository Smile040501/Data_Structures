#ifndef _MEMORY_EFFICIENT_DOUBLY_LINKED_LIST
#define _MEMORY_EFFICIENT_DOUBLY_LINKED_LIST

#include<initializer_list>
#include<iostream>
using namespace std;

#include "Node.h"

// MemoryEfficientDoublyLinkedList for representing memory efficient doubly linked list
class MemoryEfficientDoublyLinkedList {
private:
	Node *head;			// head node of the linked list
	Node *tail;				// tail node of the linked list
	
	// Function that will return the XOR of the two pointers
	Node * XOR(Node *first, Node *second);
	
public:
	// Constructors
	MemoryEfficientDoublyLinkedList();
	MemoryEfficientDoublyLinkedList(initializer_list<int> list);
	
	// Destructor
	~MemoryEfficientDoublyLinkedList();
	
	// Function to insert an element at the end of the linked list
	void push_back(int data);
	// Function to insert an element at the beginning of the linked list	
	void push_front(int data);
	
	// Function to delete the last element of the linked list
	void pop_back();
	// Function to delete the first element of the linked list
	void pop_front();
	
	// Function to insert an element at the given index
	void insert(int data, int index);
	// Function to delete an element at the given index
	void erase(int index);
	
	// Function to return the size of the linked list
	int size();
	// Function to know whether the linked list is empty or not
	bool isEmpty();
	// Function to print the linked list
	void print();
	// Function to print the reverse linked list
	void printReverse();
	
	// Function to reverse the linked list	
	void reverse();
	
	// Function to delete the whole linked list
	void clear();

};

// Constructors
MemoryEfficientDoublyLinkedList::MemoryEfficientDoublyLinkedList()
: head{nullptr}, tail{nullptr} {
}

MemoryEfficientDoublyLinkedList::MemoryEfficientDoublyLinkedList(initializer_list<int> list)
: head{nullptr}, tail{nullptr} {
	for(auto i=begin(list); i!=end(list); i++) {
		push_back(*i);
	}
}

// Destructor
MemoryEfficientDoublyLinkedList::~MemoryEfficientDoublyLinkedList() {
	clear();
}

// Function that will return the XOR of the two pointers
Node * MemoryEfficientDoublyLinkedList::XOR(Node *first, Node *second) {
	return (Node*) ((uintptr_t)(first) ^ (uintptr_t)(second));
}

// Function to insert an element at the end of the linked list
void MemoryEfficientDoublyLinkedList::push_back(int data) {
	if(tail) {
		Node *newNode = new Node(data, tail, nullptr);
		Node *prev = XOR(tail->ptrDiff, nullptr);
		tail->ptrDiff = XOR(prev, newNode);
		tail = newNode;
	} else {
		head = tail = new Node(data);
	}
}

// Function to insert an element at the beginning of the linked list	
void MemoryEfficientDoublyLinkedList::push_front(int data) {
	if(head) {
		Node *newNode = new Node(data, nullptr, head);
		Node *next = XOR(nullptr, head->ptrDiff);
		head->ptrDiff = XOR(newNode, next);
		head = newNode;
	} else {
		head = tail = new Node(data);
	}
}

// Function to delete the last element of the linked list
void MemoryEfficientDoublyLinkedList::pop_back() {
	if(!tail) {
		return;
	} else if(head==tail) {
		delete tail;
		head = tail = nullptr;
	} else {
		Node *prev = XOR(tail->ptrDiff, nullptr);
		prev->ptrDiff = XOR(XOR(prev->ptrDiff, tail), nullptr);
		delete tail;
		tail = prev;
	}
}

// Function to delete the first element of the linked list
void MemoryEfficientDoublyLinkedList::pop_front() {
	if(!head) {
		return;
	} else if(head==tail) {
		delete head;
		head = tail = nullptr;
	} else {
		Node *next = XOR(nullptr, head->ptrDiff);
		next->ptrDiff = XOR(nullptr, XOR(head, next->ptrDiff));
		delete head;
		head = next;
	}
}

// Function to insert an element at the given index
void MemoryEfficientDoublyLinkedList::insert(int data, int index) {
	if(index<0 || (!head && index!=0)) {
		return;
	}
	Node *prev = nullptr, *curr = head;
	for(int i=0; curr && i<index; i++) {
		Node *next = XOR(prev, curr->ptrDiff);
		prev = curr;
		curr = next;
	}
	if(!prev) {
		push_front(data);
	} else if(!curr) {
		push_back(data);
	} else {
		Node *newNode = new Node(data, prev, curr);
		prev->ptrDiff = XOR(XOR(prev->ptrDiff, curr), newNode);
		curr->ptrDiff = XOR(newNode, XOR(prev, curr->ptrDiff));
	}
}

// Function to delete an element at the given index
void MemoryEfficientDoublyLinkedList::erase(int index) {
	if(index<0 || !head) {
		return;
	}
	Node *prev = nullptr, *curr = head;
	for(int i=0; curr && i<index; i++) {
		Node *next = XOR(prev, curr->ptrDiff);
		prev = curr;
		curr = next;
	}
	if(!curr) {
		return;
	} else if(prev) {
		Node *next = XOR(prev, curr->ptrDiff);
		prev->ptrDiff = XOR(XOR(prev->ptrDiff, curr), next);
		if(next) {
			next->ptrDiff = XOR(prev, XOR(curr, next->ptrDiff));
		} else {
			tail = prev;
		}
		delete curr;
	} else {
		Node *nodeToDelete = head;
		head = XOR(nullptr, head->ptrDiff);
		if(head) {
			head->ptrDiff = XOR(nullptr, XOR(nodeToDelete, head->ptrDiff));
		} else {
			tail = head;
		}
		delete nodeToDelete;
	}
}

// Function to return the size of the linked list
int MemoryEfficientDoublyLinkedList::size() {
	Node *prev = nullptr, *curr = head;
	int length=0;
	while(curr) {
		Node *next = XOR(prev, curr->ptrDiff);
		prev = curr;
		curr = next;
		length++;
	}
	return length;
}

// Function to know whether the linked list is empty or not
bool MemoryEfficientDoublyLinkedList::isEmpty() {
	return (head) ? false : true;
}

// Function to print the linked list
void MemoryEfficientDoublyLinkedList::print() {
	cout << "The list is: ";
	Node *prev = nullptr, *curr = head;
	while(curr) {
		cout << curr->data << " ";
		Node *next = XOR(prev, curr->ptrDiff);
		prev = curr;
		curr = next;
	}
	cout << endl;
}

// Function to print the reverse linked list
void MemoryEfficientDoublyLinkedList::printReverse() {
	cout << "The reverse list is: ";
	Node *next = nullptr, *curr = tail;
	while(curr) {
		cout << curr->data << " ";
		Node *prev = XOR(curr->ptrDiff, next);
		next = curr;
		curr = prev;
	}
	cout << endl;
}

// Function to reverse the linked list
void MemoryEfficientDoublyLinkedList::reverse() {
	Node *newHead = tail;
	tail = head;
	head = newHead;
}

// Function to delete the whole linked list
void MemoryEfficientDoublyLinkedList::clear() {
	Node *curr = head;
	while(curr) {
		Node *next = XOR(nullptr, curr->ptrDiff);
		if(next) {
			next->ptrDiff = XOR(nullptr, XOR(curr, next->ptrDiff));
		}
		delete curr;
		curr = next;
	}
	head = tail = nullptr;
}

#endif // _MEMORY_EFFICIENT_DOUBLY_LINKED_LIST

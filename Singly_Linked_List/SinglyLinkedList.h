#ifndef _SINGLY_LINKED_LIST_
#define _SINGLY_LINKED_LIST_

#include "Node.h"
#include<initializer_list>
#include<iostream>
using namespace std;

class SinglyLinkedList {		// SinglyLinkedList class for representing singly linked list
private:
	Node *head;		// Head node of the linked list
	Node *tail;			// Tail node of the linked list
	
	// Function to print the reverse linked list
	void printReverse(Node *node);
	
	// Function to reverse the linked list
	void reverse(Node *prev, Node *curr);
	
public:
	// Constructors
	SinglyLinkedList();
	SinglyLinkedList(initializer_list<int> list);
	
	// Destructor
	~SinglyLinkedList();
	
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
SinglyLinkedList::SinglyLinkedList()
: head{nullptr}, tail{nullptr} {
}

SinglyLinkedList::SinglyLinkedList(initializer_list<int> list)
: head{nullptr}, tail{nullptr} {
	for(auto i=begin(list); i!=end(list); i++) {
		push_back(*i);
	}
}

// Destructor
SinglyLinkedList::~SinglyLinkedList() {
	if(head) {
		delete head;
	}
}

// Function to insert an element at the end of the linked list
void SinglyLinkedList::push_back(int data) {
	Node *newNode = new Node(data);
	if(tail) {
		tail->next = newNode;
		tail = newNode;
	} else {		// the list is empty
		head = tail = newNode;
	}
}

// Function to insert an element at the beginning of the linked list
void SinglyLinkedList::push_front(int data) {
	Node *newNode = new Node(data);
	if(head) {
		newNode->next = head;
		head = newNode;
	} else {			// the list is empty
		head = tail = newNode;
	}
}

// Function to delete the last element of the linked list
void SinglyLinkedList::pop_back() {
	if(!head) {
		return;
	} else if(head==tail) {
		delete tail;
		head = tail = nullptr;
		return;
	}
	Node *prev = head;
	while(prev->next != tail) {
		prev = prev->next;
	}
	delete tail;
	prev->next = nullptr;
	tail = prev;
}

// Function to delete the first element of the linked list
void SinglyLinkedList::pop_front() {
	if(!head) {
		return;
	} else if(head==tail) {
		delete head;
		head = tail = nullptr;
		return;
	}
	Node *nodeToDelete = head;
	head = head->next;
	nodeToDelete->next = nullptr;
	delete nodeToDelete;
}

// Function to insert an element at the given index
void SinglyLinkedList::insert(int data, int index) {
	if(index<0 || (!head && index!=0)) {
		return;
	}
	Node *prev = nullptr, *curr = head;
	for(int i=0; curr && i<index; i++) {
		prev = curr;
		curr = curr->next;
	}
	Node *newNode = new Node(data);
	if(prev) {
		prev->next = newNode;
		if(!curr) {
			tail = newNode;
		} else {
			newNode->next = curr;
		}
	} else {
		newNode->next = curr;
		head = newNode;
	}
}

// Function to delete an element at the given index
void SinglyLinkedList::erase(int index) {
	if(index<0 || (!head)) {
		return;
	}
	Node *prev = nullptr, *curr = head;
	for(int i=0; curr && i<index; i++) {
		prev = curr;
		curr = curr->next;
	}
	if(!curr) {
		return;
	} else if(!prev) {
		if(head==tail) {
			head = tail = nullptr;
		} else {
			head = head->next;
		}
		curr->next = nullptr;
		delete curr;
	} else {
		prev->next = curr->next;
		curr->next = nullptr;
		if(curr==tail) {
			tail = prev;
		}
		delete curr;
	}
}

// Function to return the size of the linked list
int SinglyLinkedList::size() {
	Node *curr = head;
	int length=0;
	while(curr) {
		curr = curr->next;
		length++;
	}
	return length;
}

// Function to know whether the linked list is empty or not
bool SinglyLinkedList::isEmpty() {
	return (head) ? false : true;
}

// Function to print the linked list
void SinglyLinkedList::print() {
	Node *curr = head;
	cout << "The list is: ";
	while(curr) {
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}

// Function to print the reverse linked list
void SinglyLinkedList::printReverse(Node *node) {
	if(node) {
		printReverse(node->next);
		cout << node->data << " ";
	}
}

void SinglyLinkedList::printReverse() {
	cout << "The reverse list is: ";
	printReverse(head);
	cout << endl;
}

// Function to reverse the linked list
void SinglyLinkedList::reverse(Node *prev, Node *curr) {
	if(curr) {
		reverse(curr, curr->next);
		curr->next = prev;
		if(!prev) {
			tail = curr;
		}
	} else {
		head = prev;
	}
}

void SinglyLinkedList::reverse() {
	reverse(nullptr, head);
}

// Function to delete the whole linked list
void SinglyLinkedList::clear() {
	if(head) {
		delete head;
		head = tail = nullptr;
	}
}

#endif // _SINGLY_LINKED_LIST_

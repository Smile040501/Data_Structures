#ifndef _DOUBLY_LINKED_LIST
#define _DOUBLY_LINKED_LIST

#include "Node.h"
#include<initializer_list>
#include<iostream>
using namespace std;

class DoublyLinkedList {		// DoublyLinkedList class for representing a Doubly Linked List
private:
	Node *head;		// Head node of the linked list
	Node *tail;			// Tail node of the linked list
	
	// Function to reverse the linked list	
	void reverse(Node *prev, Node *curr, Node *next);
	
public:
	// Constructors
	DoublyLinkedList();
	DoublyLinkedList(initializer_list<int> list);
	
	// Destructor
	~DoublyLinkedList();
	
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
DoublyLinkedList::DoublyLinkedList()
: head{nullptr}, tail{nullptr} {
}

DoublyLinkedList::DoublyLinkedList(initializer_list<int> list)
: head{nullptr}, tail{nullptr} {
	for(auto i=begin(list); i!=end(list); i++) {
		push_back(*i);
	}
}

// Destructor
DoublyLinkedList::~DoublyLinkedList() {
	if(head) {
		delete head;
	}
}

// Function to insert an element at the end of the linked list
void DoublyLinkedList::push_back(int data) {
	Node *newNode = new Node(data);
	if(tail) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	} else {
		head = tail = newNode;
	}
}

// Function to insert an element at the beginning of the linked list	
void DoublyLinkedList::push_front(int data) {
	Node *newNode = new Node(data);
	if(head) {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	} else {
		head = tail = newNode;
	}
}

// Function to delete the last element of the linked list
void DoublyLinkedList::pop_back() {
	if(!tail) {
		return;
	} else if(head==tail) {
		delete tail;
		head = tail = nullptr;
	} else {
		Node *prev = tail->prev;
		tail->prev = nullptr;
		delete tail;
		prev->next = nullptr;
		tail = prev;
	}
}

// Function to delete the first element of the linked list
void DoublyLinkedList::pop_front() {
	if(!head) {
		return;
	} else if(head==tail) {
		delete head;
		head = tail = nullptr;
	} else {
		Node *next = head->next;
		head->next = nullptr;
		delete head;
		next->prev = nullptr;
		head = next;
	}
}

// Function to insert an element at the given index
void DoublyLinkedList::insert(int data, int index) {
	if(index<0 && (!head && index!=0)) {
		return;
	}
	Node *prev = nullptr, *curr = head;
	for(int i=0; curr && i<index; i++) {
		prev = curr;
		curr = curr->next;
	}
	Node *newNode = new Node(data);
	if(!prev) {
		newNode->next = curr;
		curr->prev = newNode;
		head = newNode;
	} else {
		prev->next = newNode;
		newNode->prev = prev;
		newNode->next = curr;
		if(curr) {
			curr->prev = newNode;
		}
	}
}

// Function to delete an element at the given index
void DoublyLinkedList::erase(int index) {
	if(index<0 || !head) {
		return;
	}
	Node *prev = nullptr, *curr = head;
	for(int i=0; curr && i<index; i++) {
		prev = curr;
		curr = curr->next;
	}
	if(!curr) {
		return;
	} else if(prev) {
		prev->next = curr->next;
		curr->prev = nullptr;
		if(curr->next) {
			curr->next->prev = prev;
			curr->next = nullptr;
		} else {
			tail = prev;
		}
		delete curr;
	} else {
		Node *nodeToDelete = head;
		head = head->next;
		nodeToDelete->next = nullptr;
		if(head) {
			head->prev = nullptr;
		} else {
			tail = head;
		}
		delete nodeToDelete;
	}
}

// Function to return the size of the linked list
int DoublyLinkedList::size() {
	Node *curr = head;
	int length=0;
	while(curr) {
		curr = curr->next;
		length++;
	}
	return length;
}

// Function to know whether the linked list is empty or not
bool DoublyLinkedList::isEmpty() {
	return (head) ? false : true;
}

// Function to print the linked list
void DoublyLinkedList::print() {
	cout << "The list is: ";
	Node *curr = head;
	while(curr) {
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}

// Function to print the reverse linked list
void DoublyLinkedList::printReverse() {
	cout << "The reverse List is: ";
	Node *curr = tail;
	while(curr) {
		cout << curr->data << " ";
		curr = curr->prev;
	}
	cout << endl;
}

// Function to reverse the linked list
void DoublyLinkedList::reverse(Node *prev, Node *curr, Node *next) {
	if(next) {
		reverse(curr, next, next->next);
	} else {
		head = curr;
	}
	curr->prev = next;
	curr->next = prev;
	if(!prev) {
		tail = curr;
	}
}

void DoublyLinkedList::reverse() {
	if(!head) {
		return;
	}
	reverse(nullptr, head, head->next);
}

// Function to delete the whole linked list
void DoublyLinkedList::clear() {
	if(head) {
		delete head;
		head = tail = nullptr;
	}
}

#endif // _DOUBLY_LINKED_LIST

#ifndef _DEQUE_
#define _DEQUE_

#include <climits>
#include <iostream>

#include "Node.h"

class Deque {  // Deque class for representing a deque
   private:
    Node *head;  // Head node of the linked list representing deque
    Node *tail;  // Tail node of the linked list representing deque
    int count;   // Number of elements in the deque

   public:
    // Constructors
    Deque();

    // Destructor
    ~Deque();

    // Function to push an element to the back of the deque
    void push_back(int data);
    // Function to push an element to the front of the deque
    void push_front(int data);
    // Function to pop an element from the back of the deque
    void pop_back();
    // Function to pop an element from the front of the deque
    void pop_front();
    // Function to return the frontmost element of the deque
    int front();
    // Function to return the last element of the deque
    int back();
    // Function to return the size of the deque
    int size();
    // Function to return if the deque is empty of not
    bool empty();
    // Function to swap the two deques
    void swap(Deque &q);

    // Function to print the deque elements
    void print();
    // Function to print the deque elements in reverse
    void printReverse();
};

// Constructors
Deque::Deque()
    : head{nullptr}, tail{nullptr}, count{} {
}

// Destructor
Deque::~Deque() {
    Node *curr = head;
    while (curr) {
        Node *nodeToDelete = curr;
        curr = curr->next;
        if (curr) {
            curr->prev = nullptr;
        }
        nodeToDelete->next = nullptr;
        delete nodeToDelete;
    }
    head = tail = nullptr;
    count = 0;
}

// Function to push an element to the back of the deque
void Deque::push_back(int data) {
    Node *newNode = new Node(data);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    count++;
}

// Function to push an element to the front of the deque
void Deque::push_front(int data) {
    Node *newNode = new Node(data);
    if (head) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {
        head = tail = newNode;
    }
    count++;
}

// Function to pop an element from the back of the deque
void Deque::pop_back() {
    if (!tail) {
        return;
    } else if (head == tail) {
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

// Function to pop an element from the front of the deque
void Deque::pop_front() {
    if (!head) {
        return;
    } else if (head == tail) {
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

// Function to return the frontmost element of the deque
int Deque::front() {
    if (head) {
        return head->data;
    } else {
        return INT_MIN;
    }
}

// Function to return the last element of the deque
int Deque::back() {
    if (tail) {
        return tail->data;
    } else {
        return INT_MIN;
    }
}

// Function to return the size of the deque
int Deque::size() {
    return count;
}

// Function to return if the deque is empty of not
bool Deque::empty() {
    return count == 0;
}

// Function to swap the two deques
void Deque::swap(Deque &q) {
    Node *temp1 = head, *temp2 = tail;
    head = q.head;
    tail = q.tail;
    q.head = temp1;
    q.tail = temp2;

    int temp3 = count;
    count = q.count;
    q.count = temp3;
}

// Function to print the deque elements
void Deque::print() {
    std::cout << "The Deque is: ";
    Node *curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

// Function to print the deque elements in reverse
void Deque::printReverse() {
    std::cout << "The reverse Deque is: ";
    Node *curr = tail;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->prev;
    }
    std::cout << std::endl;
}

#endif  // _DEQUE_

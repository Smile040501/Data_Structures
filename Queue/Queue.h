#ifndef _QUEUE_
#define _QUEUE_

#include <climits>
#include <iostream>

#include "Node.h"

class Queue {  // Queue class for representing a queue
   private:
    Node *head;  // Head node of the linked list representing the queue
    Node *tail;  // Tail node of the linked list representing the queue
    int count;   // Number of elements in the queue

   public:
    // Constructor
    Queue();

    // Destructor
    ~Queue();

    // Function to push an element to the queue
    void push(int data);
    // Function to pop out an element from the queue
    void pop();
    // Function to return the frontmost element of the queue
    int front();
    // Function to return the size of the queue
    int size();
    // Function to return if the queue is empty of not
    bool empty();
    // Function to swap the two queue
    void swap(Queue &q);

    // Function to print the queue elements
    void print();
};

// Constructor
Queue::Queue()
    : head{nullptr}, tail{nullptr}, count{} {
}

// Destructor
Queue::~Queue() {
    Node *curr = head;
    while (curr) {
        Node *nodeToDelete = curr;
        curr = curr->next;
        nodeToDelete->next = nullptr;
        delete nodeToDelete;
    }
    head = tail = nullptr;
    count = 0;
}

// Function to push an element to the queue
void Queue::push(int data) {
    Node *newNode = new Node(data);
    if (tail) {
        tail->next = newNode;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    count++;
}

// Function to pop out an element from the queue
void Queue::pop() {
    if (!head) {
        return;
    } else if (head == tail) {
        Node *nodeToDelete = head;
        head = tail = nullptr;
        count = 0;
        delete nodeToDelete;
        return;
    }
    Node *nodeToDelete = head;
    head = head->next;
    nodeToDelete->next = nullptr;
    delete nodeToDelete;
    count--;
}

// Function to return the frontmost element of the queue
int Queue::front() {
    if (head) {
        return head->data;
    } else {
        return INT_MIN;
    }
}

// Function to return the size of the queue
int Queue::size() {
    return count;
}

// Function to return if the queue is empty of not
bool Queue::empty() {
    return count == 0;
}

// Function to swap the two queue
void Queue::swap(Queue &q) {
    Node *temp1 = head, *temp2 = tail;
    head = q.head;
    tail = q.tail;
    q.head = temp1;
    q.tail = temp2;

    int temp3 = count;
    count = q.count;
    q.count = temp3;
}

// Function to print the queue elements
void Queue::print() {
    std::cout << "The Queue is: ";
    Node *curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

#endif  // _QUEUE_

#ifndef _SINGLY_CIRCULAR_LINKED_LIST_
#define _SINGLY_CIRCULAR_LINKED_LIST_

#include <initializer_list>
#include <iostream>

#include "Node.h"
using namespace std;

class SinglyCircularLinkedList {  // SinglyCircularLinkedList class for representing a singly circular linked list
   private:
    Node *head;  // Head node of the linked list
    Node *tail;  // Tail node of the linked list

    // Function to return the loop head of the linked list
    Node *getLoopHead();

    // Function that reverse the linked list and make final tail->next = head
    void reverse(Node *prev, Node *curr);

   public:
    // Constructors
    SinglyCircularLinkedList();
    SinglyCircularLinkedList(initializer_list<int> list);

    // Destructor
    ~SinglyCircularLinkedList();

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

    // Function that reverse the linked list and make final tail->next = head
    void reverse();

    // Function to delete the whole linked list
    void clear();

    // Function to make the loop from tail to the required index node of the linked list
    void makeLoop(int index);
    // Function to remove the loop from the linked list
    void removeLoop();
    // Function to detect if there is any loop in the linked list
    bool hasLoop();
    // Function to return the length of the loop in the linked list
    int loopLength();
};

// Constructors
SinglyCircularLinkedList::SinglyCircularLinkedList()
    : head{nullptr}, tail{nullptr} {
}

SinglyCircularLinkedList::SinglyCircularLinkedList(initializer_list<int> list)
    : head{nullptr}, tail{nullptr} {
    for (auto i = list.begin(); i != list.end(); i++) {
        push_back(*i);
    }
}

// Destructor
SinglyCircularLinkedList::~SinglyCircularLinkedList() {
    clear();
}

// Function to return the loop head of the linked list
Node *SinglyCircularLinkedList::getLoopHead() {
    if (!head) {
        return head;
    }
    // Method-1
    // If tail pointer is available
    //return tail->next;

    // Method-2
    // If tail pointer is not avalable
    Node *slow = head, *fast = head;
    do {
        fast = fast->next;
        slow = slow->next;
        if (fast) {
            fast = fast->next;
        }
    } while (fast && fast != slow);

    if (!fast) {
        return nullptr;
    }
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// Function to insert an element at the end of the linked list
void SinglyCircularLinkedList::push_back(int data) {
    Node *newNode = new Node(data);
    if (tail) {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
}

// Function to insert an element at the beginning of the linked list
void SinglyCircularLinkedList::push_front(int data) {
    Node *newNode = new Node(data);
    if (head) {
        newNode->next = head;
        head = newNode;
    } else {
        head = tail = newNode;
    }
}

// Function to delete the last element of the linked list
void SinglyCircularLinkedList::pop_back() {
    if (!tail) {
        return;
    } else if (head == tail) {
        delete tail;
        head = tail = nullptr;
        return;
    }
    Node *curr = head;
    while (curr->next != tail) {
        curr = curr->next;
    }
    if (tail->next == tail) {
        curr->next = nullptr;
    } else {
        curr->next = tail->next;
    }
    tail->next = nullptr;
    delete tail;
    tail = curr;
}

// Function to delete the first element of the linked list
void SinglyCircularLinkedList::pop_front() {
    if (!head) {
        return;
    } else if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }
    Node *curr = head->next;
    if (tail->next == head) {
        tail->next = curr;
    }
    head->next = nullptr;
    delete head;
    head = curr;
}

// Function to insert an element at the given index
void SinglyCircularLinkedList::insert(int data, int index) {
    if (index < 0 || (!head && index != 0)) {
        return;
    }
    if (!head) {
        head = tail = new Node(data);
        return;
    }
    Node *prev = nullptr, *curr = head;
    for (int i = 0; curr && i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    Node *newNode = new Node(data);
    if (!prev) {
        newNode->next = head;
        head = newNode;
    } else {
        prev->next = newNode;
        newNode->next = curr;
    }
}

// Function to delete an element at the given index
void SinglyCircularLinkedList::erase(int index) {
    if (index < 0 || !head) {
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }
    Node *prev = nullptr, *curr = head;
    for (int i = 0; curr && i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        return;
    } else if (!prev) {
        pop_front();
    } else {
        if (curr->next != curr) {
            prev->next = curr->next;
        } else {
            prev->next = nullptr;
        }
        curr->next = nullptr;
        if (tail->next == curr) {
            tail->next = prev->next;
        }
        if (tail == curr) {
            tail = prev;
        }
        delete curr;
    }
}

// Function to return the size of the linked list
int SinglyCircularLinkedList::size() {
    Node *loopHead = getLoopHead(), *curr = head;
    int length = 0;
    bool visited = false;
    while (curr && (!visited || curr != loopHead)) {
        if (curr == loopHead) {
            visited = true;
        }
        curr = curr->next;
        length++;
    }
    return length;
}

// Function to know whether the linked list is empty or not
bool SinglyCircularLinkedList::isEmpty() {
    return (head) ? false : true;
}

// Function to print the linked list
void SinglyCircularLinkedList::print() {
    Node *curr = head, *loopHead = getLoopHead();
    bool visited = false;
    while (curr && (!visited || curr != loopHead)) {
        cout << curr->data << " -> ";
        if (curr == loopHead) {
            visited = true;
        }
        curr = curr->next;
    }
    if (curr) {
        cout << "*" << curr->data;
    } else {
        cout << "NULL";
    }
    cout << endl;
}

// Function that reverse the linked list and make final tail->next = head
void SinglyCircularLinkedList::reverse(Node *prev, Node *curr) {
    if (curr) {
        reverse(curr, curr->next);
        curr->next = prev;
        if (!prev) {
            tail = curr;
        }
    } else {
        head = prev;
    }
}

void SinglyCircularLinkedList::reverse() {
    if (head && head != tail) {
        tail->next = nullptr;
        reverse(nullptr, head);
        tail->next = head;
    }
}

// Function to delete the whole linked list
void SinglyCircularLinkedList::clear() {
    if (head) {
        Node *curr = head;
        while (curr != tail) {
            Node *nodeToDelete = curr;
            curr = curr->next;
            nodeToDelete->next = nullptr;
            delete nodeToDelete;
        }
        curr->next = nullptr;
        delete curr;
        head = tail = nullptr;
    }
}

// Function to make the loop from tail to the required index node of the linked list
void SinglyCircularLinkedList::makeLoop(int index) {
    Node *curr = head;
    for (int i = 0; curr && i < index; i++) {
        curr = curr->next;
    }
    tail->next = curr;
}

// Function to remove the loop from the linked list
void SinglyCircularLinkedList::removeLoop() {
    // Method-1
    // If tail pointer is available
    //if(tail) {
    //	tail->next = nullptr;
    //}

    // Method-2
    // If tail pointer is not available
    if (!head) {
        return;
    }
    Node *slow = head, *fast = head, *prev = nullptr;
    do {
        prev = fast;
        fast = fast->next;
        slow = slow->next;
        if (fast) {
            prev = fast;
            fast = fast->next;
        }
    } while (fast && fast != slow);

    if (fast) {
        slow = head;
        while (fast != slow) {
            prev = fast;
            fast = fast->next;
            slow = slow->next;
        }
        prev->next = nullptr;
    }
}

// Function to detect if there is any loop in the linked list
bool SinglyCircularLinkedList::hasLoop() {
    // Method-1
    // If tail pointer is available
    //if(!tail || tail->next) {
    //	return true;
    //} else {
    //	return false;
    //}

    // Method-2
    // If tail pointer is not available
    Node *slow = head, *fast = head;
    do {
        fast = fast->next;
        slow = slow->next;
        if (fast) {
            fast = fast->next;
        }
    } while (fast && fast != slow);

    return (fast) ? true : false;
}

// Function to return the length of the loop in the linked list
int SinglyCircularLinkedList::loopLength() {
    Node *loopHead = getLoopHead();
    if (!loopHead) {
        return 0;
    }
    Node *curr = loopHead;
    int length = 0;
    do {
        curr = curr->next;
        length++;
    } while (curr && curr != loopHead);
    return length;
}

#endif  // _SINGLY_CIRCULAR_LINKED_LIST_

#ifndef _MIN_PRIORITY_QUEUE_
#define _MIN_PRIORITY_QUEUE_

#include <vector>

//MinPriorityQueue class for representing a min priority queue
// Min Binary Heap
class MinPriorityQueue {
    vector<int> arr;  // Array to store the values of the priority queue

   public:
    // Constructor
    MinPriorityQueue();

    // Destructor
    ~MinPriorityQueue();

    // Function to push an element into the priority queue
    void push(int data);
    // Function to pop out the minimum element from the priority queue
    void pop();
    // Function to get the minimum value from the priority queue
    int top();
    // Function to return the size of the priority queue
    int size();
    // Function to return whether the priority queue is empty or not
    bool empty();
    // Function to swap two priority queues
    void swap(MinPriorityQueue &pq);
};

// Constructor
MinPriorityQueue::MinPriorityQueue() {
}

// Destructor
MinPriorityQueue::~MinPriorityQueue() {
}

// Function to push an element into the priority queue
void MinPriorityQueue::push(int data) {
    arr.push_back(data);
    int ci = arr.size() - 1;
    int pi = (ci - 1) / 2;
    while (ci > 0) {
        if (arr[ci] < arr[pi]) {
            int temp = arr[ci];
            arr[ci] = arr[pi];
            arr[pi] = temp;
        }
        ci = pi;
        pi = (ci - 1) / 2;
    }
}

// Function to pop out the minimum element from the priority queue
void MinPriorityQueue::pop() {
    if (arr.size() == 0) {
        return;
    } else {
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        int pi = 0;
        int lci = 2 * pi + 1, rci = 2 * pi + 2;
        while (lci < arr.size()) {
            int minIndex = pi;
            if (arr[lci] < arr[minIndex]) {
                minIndex = lci;
            }
            if (rci < arr.size() && arr[rci] < arr[minIndex]) {
                minIndex = rci;
            }
            if (minIndex == pi) {
                break;
            }
            int temp = arr[pi];
            arr[pi] = arr[minIndex];
            arr[minIndex] = temp;
            pi = minIndex;
            lci = 2 * pi + 1;
            rci = 2 * pi + 2;
        }
    }
}

// Function to get the minimum value from the priority queue
int MinPriorityQueue::top() {
    return (arr.size() == 0) ? INT_MIN : arr[0];
}

// Function to return the size of the priority queue
int MinPriorityQueue::size() {
    return arr.size();
}

// Function to return whether the priority queue is empty or not
bool MinPriorityQueue::empty() {
    return arr.size() == 0;
}

// Function to swap two priority queues
void MinPriorityQueue::swap(MinPriorityQueue &pq) {
    vector<int> temp = arr;
    arr = pq.arr;
    pq.arr = temp;
}

#endif  // _MIN_PRIORITY_QUEUE_

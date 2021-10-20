#ifndef _MAX_PRIORITY_QUEUE_
#define _MAX_PRIORITY_QUEUE_

#include <vector>

//MaxPriorityQueue class for representing a max priority queue
// Max Binary Heap
class MaxPriorityQueue {
    vector<int> arr;  // Array to store the values of the priority queue

   public:
    // Constructor
    MaxPriorityQueue();

    // Destructor
    ~MaxPriorityQueue();

    // Function to push an element into the priority queue
    void push(int data);
    // Function to pop out the maximun element from the priority queue
    void pop();
    // Function to get the maximum value from the priority queue
    int top();
    // Function to return the size of the priority queue
    int size();
    // Function to return whether the priority queue is empty or not
    bool empty();
    // Function to swap two priority queues
    void swap(MaxPriorityQueue &pq);
};

// Constructor
MaxPriorityQueue::MaxPriorityQueue() {
}

// Destructor
MaxPriorityQueue::~MaxPriorityQueue() {
}

// Function to push an element into the priority queue
void MaxPriorityQueue::push(int data) {
    arr.push_back(data);
    int ci = arr.size() - 1;
    int pi = (ci - 1) / 2;
    while (ci > 0) {
        if (arr[ci] > arr[pi]) {
            int temp = arr[ci];
            arr[ci] = arr[pi];
            arr[pi] = temp;
        }
        ci = pi;
        pi = (ci - 1) / 2;
    }
}

// Function to pop out the maximun element from the priority queue
void MaxPriorityQueue::pop() {
    if (arr.size() == 0) {
        return;
    } else {
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        int pi = 0;
        int lci = 2 * pi + 1, rci = 2 * pi + 2;
        while (lci < arr.size()) {
            int maxIndex = pi;
            if (arr[lci] > arr[maxIndex]) {
                maxIndex = lci;
            }
            if (rci < arr.size() && arr[rci] > arr[maxIndex]) {
                maxIndex = rci;
            }
            if (maxIndex == pi) {
                break;
            }
            int temp = arr[pi];
            arr[pi] = arr[maxIndex];
            arr[maxIndex] = temp;
            pi = maxIndex;
            lci = 2 * pi + 1;
            rci = 2 * pi + 2;
        }
    }
}

// Function to get the maximum value from the priority queue
int MaxPriorityQueue::top() {
    return (arr.size() == 0) ? INT_MIN : arr[0];
}

// Function to return the size of the priority queue
int MaxPriorityQueue::size() {
    return arr.size();
}

// Function to return whether the priority queue is empty or not
bool MaxPriorityQueue::empty() {
    return arr.size() == 0;
}

// Function to swap two priority queues
void MaxPriorityQueue::swap(MaxPriorityQueue &pq) {
    vector<int> temp = arr;
    arr = pq.arr;
    pq.arr = temp;
}

#endif  // _MAX_PRIORITY_QUEUE_

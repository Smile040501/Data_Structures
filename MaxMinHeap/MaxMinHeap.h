#ifndef _MAX_MIN_HEAP_
#define _MAX_MIN_HEAP_

#include <cmath>
#include <initializer_list>
#include <vector>

// MaxMinHeap class for representing a max-min heap
class MaxMinHeap {
    vector<int> arr;  // vector for storing the elements of the max-min Heap

    // Function to return the level of the key given its index in the array
    int level(int index);
    // Function to return the parent index of the element given its index
    int parent(int index);
    // Function to return the index of left child of the element given its index
    int leftChild(int index);
    // Function to return the index of right child of the element given its index
    int rightChild(int index);

    // Function to build the heap
    void buildHeap();

    // Function to push down an element
    void pushDown(int index);
    // Function to push down an element if it is at min level
    void pushDownMin(int index);
    // Function to push down an element if it is at max level
    void pushDownMax(int index);

    // Function to push up an element
    void pushUp(int index);
    // Function to push up an element if it is at min level
    void pushUpMin(int index);
    // Function to push up an element if it is at max level
    void pushUpMax(int index);

   public:
    // Constructors
    MaxMinHeap();
    MaxMinHeap(initializer_list<int> list);

    // Destructor
    ~MaxMinHeap();

    // Function to push an element into the heap
    void push(int data);
    // Function to pop the minimum element from the heap
    void popMin();
    // Function to pop the maximum element from the heap
    void popMax();
    // Function to get the minimum element from the heap
    int topMin();
    // Function to get it maximum element from the heap
    int topMax();
    // Function to return the size of the heap
    int size();
    // Function to return whether the heap is empty or not
    bool empty();

    // Function to print the heap elements in the form of a tree
    // For Testing purposes
    void print();
};

// Constructors
MaxMinHeap::MaxMinHeap() {
}

MaxMinHeap::MaxMinHeap(initializer_list<int> list) {
    for (auto i = list.begin(); i != list.end(); i++) {
        arr.push_back(*i);
    }
    buildHeap();
}

// Destructor
MaxMinHeap::~MaxMinHeap() {
}

// Function to return the level of the key given its index in the array
int MaxMinHeap::level(int index) {
    return log2(index + 1);
}

// Function to return the parent index of the element given its index
int MaxMinHeap::parent(int index) {
    return (index == 0) ? -1 : (index - 1) / 2;
}
// Function to return the index of left child of the element given its index
int MaxMinHeap::leftChild(int index) {
    return 2 * index + 1;
}

// Function to return the index of right child of the element given its index
int MaxMinHeap::rightChild(int index) {
    return 2 * index + 2;
}

// Function to build the heap
void MaxMinHeap::buildHeap() {
    for (int i = arr.size() - 1; i >= 0; i--) {
        pushDown(i);
    }
}

// Function to push down an element
void MaxMinHeap::pushDown(int index) {
    if (level(index) % 2 == 0) {
        pushDownMax(index);
    } else {
        pushDownMin(index);
    }
}

// Function to push down an element if it is at min level
void MaxMinHeap::pushDownMin(int index) {
    int lci = leftChild(index), rci = rightChild(index);
    vector<int> directChildren = {lci, rci};
    vector<int> grandChildren = {leftChild(lci), rightChild(lci), leftChild(rci), rightChild(rci)};
    int minIndex = index;
    char smallestChild = 'p';
    for (const auto &i : directChildren) {
        if (i < arr.size() && arr[i] < arr[minIndex]) {
            minIndex = i;
            smallestChild = 'd';
        }
    }
    for (const auto &i : grandChildren) {
        if (i < arr.size() && arr[i] < arr[minIndex]) {
            minIndex = i;
            smallestChild = 'g';
        }
    }
    if (minIndex == index) {
        return;
    } else {
        swap(arr[index], arr[minIndex]);
        if (smallestChild == 'g') {
            if (arr[minIndex] > arr[parent(minIndex)]) {
                swap(arr[minIndex], arr[parent(minIndex)]);
            }
            pushDownMin(minIndex);
        }
    }
}

// Function to push down an element if it is at max level
void MaxMinHeap::pushDownMax(int index) {
    int lci = leftChild(index), rci = rightChild(index);
    vector<int> directChildren = {lci, rci};
    vector<int> grandChildren = {leftChild(lci), rightChild(lci), leftChild(rci), rightChild(rci)};
    int maxIndex = index;
    char biggestChild = 'p';
    for (const auto &i : directChildren) {
        if (i < arr.size() && arr[i] > arr[maxIndex]) {
            maxIndex = i;
            biggestChild = 'd';
        }
    }
    for (const auto &i : grandChildren) {
        if (i < arr.size() && arr[i] > arr[maxIndex]) {
            maxIndex = i;
            biggestChild = 'g';
        }
    }
    if (maxIndex == index) {
        return;
    } else {
        swap(arr[index], arr[maxIndex]);
        if (biggestChild == 'g') {
            if (arr[maxIndex] < arr[parent(maxIndex)]) {
                swap(arr[maxIndex], arr[parent(maxIndex)]);
            }
            pushDownMax(maxIndex);
        }
    }
}

// Function to push up an element
void MaxMinHeap::pushUp(int index) {
    if (level(index) % 2 == 0) {
        if (arr[index] < arr[parent(index)]) {
            swap(arr[index], arr[parent(index)]);
            pushUpMin(parent(index));
        } else {
            pushUpMax(index);
        }
    } else {
        if (arr[index] > arr[parent(index)]) {
            swap(arr[index], arr[parent(index)]);
            pushUpMax(parent(index));
        } else {
            pushUpMin(index);
        }
    }
}

// Function to push up an element if it is at min level
void MaxMinHeap::pushUpMin(int index) {
    int grandParent = parent(parent(index));
    if (grandParent >= 0 && arr[index] < arr[grandParent]) {
        swap(arr[index], arr[grandParent]);
        pushUpMin(grandParent);
    }
}

// Function to push up an element if it is at max level
void MaxMinHeap::pushUpMax(int index) {
    int grandParent = parent(parent(index));
    if (grandParent >= 0 && arr[index] > arr[grandParent]) {
        swap(arr[index], arr[grandParent]);
        pushUpMax(grandParent);
    }
}

// Function to push an element into the heap
void MaxMinHeap::push(int data) {
    arr.push_back(data);
    pushUp(arr.size() - 1);
}
// Function to pop the minimum element from the heap
void MaxMinHeap::popMin() {
    if (arr.size() == 0) {
        return;
    } else if (arr.size() == 1 || arr.size() == 2) {
        arr.pop_back();
    } else {
        int minIndex = (arr[1] < arr[2]) ? 1 : 2;
        arr[minIndex] = arr[arr.size() - 1];
        arr.pop_back();
        pushDown(minIndex);
    }
}

// Function to pop the maximum element from the heap
void MaxMinHeap::popMax() {
    if (arr.size() == 0) {
        return;
    } else {
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        pushDown(0);
    }
}

// Function to get the minimum element from the heap
int MaxMinHeap::topMin() {
    if (arr.size() == 0) {
        return INT_MIN;
    } else if (arr.size() == 1 || arr.size() == 2) {
        return arr[arr.size() - 1];
    } else {
        return fmin(arr[1], arr[2]);
    }
}

// Function to get it maximum element from the heap
int MaxMinHeap::topMax() {
    return (arr.size() == 0) ? INT_MAX : arr[0];
}

// Function to return the size of the heap
int MaxMinHeap::size() {
    return arr.size();
}

// Function to return whether the heap is empty or not
bool MaxMinHeap::empty() {
    return arr.size() == 0;
}

// Function to print the heap elements in the form of a tree
// For Testing purposes
void MaxMinHeap::print() {
    cout << "The Heap is: " << endl;
    for (int i = 0; i < arr.size(); i++) {
        if (i == 0) {
            cout << arr[i] << endl;
        } else {
            cout << arr[i] << " ";
            if (level(i) != level(i + 1)) {
                cout << endl;
            }
        }
    }
    cout << endl;
}

#endif  // _MAX_MIN_HEAP_

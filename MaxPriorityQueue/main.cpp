#include <iostream>
using namespace std;

#include "MaxPriorityQueue.h"

// Sample Main
int main() {
    MaxPriorityQueue pq;
    pq.push(10);
    pq.push(40);
    pq.push(50);
    pq.push(104);
    pq.push(420);
    pq.push(540);
    pq.push(310);
    pq.push(140);
    pq.push(650);
    pq.push(710);
    pq.push(405);
    pq.push(501);
    cout << "Size of priority queue: " << pq.size() << endl;
    cout << "The priority queue is: " << endl;
    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }

    pq.push(10);
    pq.push(40);
    pq.push(50);
    pq.push(20);
    pq.push(30);

    MaxPriorityQueue pq2;
    pq2.push(100);
    pq2.push(50);
    pq2.push(60);
    pq2.push(70);

    cout << "Swapping the two priority queues..." << endl;
    pq.swap(pq2);

    cout << "First priority queue after swapping..." << endl;
    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }

    cout << "Second priority queue after swapping..." << endl;
    while (!pq2.empty()) {
        cout << pq2.top() << endl;
        pq2.pop();
    }

    std::cout << std::endl;
    return 0;
}

#include <iomanip>
#include <iostream>
using namespace std;

#include "Deque.h"

// Sample main
int main() {
    Deque q1;
    q1.push_back(1);
    q1.push_front(2);
    q1.push_back(3);
    q1.push_front(4);
    q1.push_back(5);
    q1.push_front(6);

    q1.print();
    q1.printReverse();

    q1.pop_back();
    q1.pop_front();
    q1.print();
    q1.printReverse();

    cout << "The size of the deque is: " << q1.size() << endl;
    cout << "The front element of the deque is: " << q1.front() << endl;
    cout << "The last element of the deque is: " << q1.back() << endl;
    cout << "Is deque empty: " << boolalpha << q1.empty() << endl;

    Deque q2;
    q2.push_back(10);
    q2.push_front(20);
    q2.push_back(30);
    q2.push_front(40);
    q2.push_back(50);
    q2.push_front(60);

    cout << "Before swapping..." << endl;
    q1.print();
    q2.print();

    cout << "After swapping..." << endl;
    q1.swap(q2);
    q1.print();
    q2.print();

    cout << endl;
    return 0;
}

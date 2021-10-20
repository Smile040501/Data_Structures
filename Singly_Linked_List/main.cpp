#include <iomanip>
#include <iostream>
using namespace std;

#include "SinglyLinkedList.h"

// Sample main
int main() {
    SinglyLinkedList list1{1, 2, 3, 4, 5};

    list1.print();
    list1.printReverse();

    list1.push_back(6);
    list1.push_front(0);
    list1.print();

    list1.pop_back();
    list1.pop_front();
    list1.print();

    list1.insert(6, 3);
    list1.print();

    list1.erase(3);
    list1.print();

    cout << "Size of the list: " << list1.size() << endl;
    cout << "Is List empty: " << boolalpha << list1.isEmpty() << endl;

    list1.reverse();
    list1.print();

    list1.clear();
    cout << "Is List empty: " << boolalpha << list1.isEmpty() << endl;

    cout << endl;
    return 0;
}

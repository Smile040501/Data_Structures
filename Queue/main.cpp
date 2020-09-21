#include<iostream>
#include<iomanip>
using namespace std;

#include "Queue.h"

// Sample main
int main() {
	Queue q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);
	q1.print();
	
	q1.pop();
	q1.print();
	
	cout << "Size of the queue: " << q1.size() << endl;
	cout << "Is Queue empty: " << boolalpha << q1.empty() << endl;
	cout << "Front element of the queue: " << q1.front() << endl;
	
	Queue q2;
	q2.push(10);
	q2.push(20);
	q2.push(30);
	q2.push(40);
	q2.push(50);
	q2.push(60);
	
	cout << "Before swapping..." << endl;
	q1.print();
	q2.print();
	
	q1.swap(q2);
	
	cout << "After swapping..." << endl;
	q1.print();
	q2.print();
	
	cout << endl;
	return 0;
}

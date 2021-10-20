#include <iostream>
using namespace std;

#include "Deap.h"

// Sample Main
int main() {
    Deap deap1{-1, 24, 5, 7, 9, 11, 13, 8, 50, 70, 100, 2, 4};
    deap1.print();
    cout << "Size of the Deap: " << deap1.size() << endl;
    cout << "Minimum element of the deap: " << deap1.topMin() << endl;
    cout << "Maximum element of the deap: " << deap1.topMax() << endl;

    cout << "Elements in increasing order: ";
    while (!deap1.empty()) {
        cout << deap1.topMin() << " ";
        deap1.popMin();
    }
    cout << endl;

    Deap deap2{28, 31, 24, 20, 25, 30, 52, 40, 23, 37, 7, 89, 42};
    deap2.print();

    cout << "Elements in decreasing order: ";
    while (!deap2.empty()) {
        cout << deap2.topMax() << " ";
        ;
        deap2.popMax();
    }
    cout << endl;

    std::cout << std::endl;
    return 0;
}

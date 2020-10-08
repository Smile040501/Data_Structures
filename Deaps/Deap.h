#ifndef _DEAP_
#define _DEAP_

#include<vector>
#include<initializer_list>
#include<cmath>

// Deap class for representing a Deap data structure
// Doubly Ended Priority Queue
class Deap {
	vector<int> arr;		// vector for storing the elements of the Deap
	
	// Function to get the level of an element given its index
	int level(int index);
	// Function to get the index of parent of an element given its index
	int parent(int index);
	// Function to get the index of left child of an element given its index
	int leftChild(int index);
	// Function to get the index of right child of an element given its index
	int rightChild(int index);
	
	// Function to get the index of corresponding element in min-heap of an element in max-heap
	int minPartner(int index);
	// Function to get the index of corresponding element in max-heap of an element in min-heap
	int maxPartner(int index);
	
	// Function to check whether the given index is in min-heap or not
	bool inMinHeap(int index);
	// Function to check whether the given index is in max-heap or not
	bool inMaxHeap(int index);
	
	// Function to push up an element in the min-heap
	void pushUpMin(int index);
	// Function to push up an element in the max-heap
	void pushUpMax(int index);
	
	// Function to push down an element in the min-heap and return the index of final position
	int pushDownMin(int index);
	// Function to push down an element in the max-heap and return the index of final position
	int pushDownMax(int index);
	
	// Function to check the correspondence condition of an element in min-heap given its index
	void correctCorrespondenceConditionMin(int index);
	// Function to check the correspondence condition of an element in max-heap given its index
	void correctCorrespondenceConditionMax(int index);
	
public:
	// Constructors
	Deap();
	Deap(initializer_list<int> list);
	
	// Destructor
	~Deap();
	
	// Function to push an element into the deap
	void push(int data);
	// Function to pop out the minimum element from the deap
	void popMin();
	// Function to pop out the maximum element from the deap
	void popMax();
	// Function to return the value of the minimum element in the deap
	int topMin();
	// Function to return the value of the maximum element in the deap
	int topMax();
	// Function to return the size of the deap
	int size();
	// Function to check if the deap is empty or not 
	bool empty();
	
	// Function to print the elements of the deap in form of a tree
	// For Testing purposes
	void print();
};

// Constructors
Deap::Deap() {
}

Deap::Deap(initializer_list<int> list) {
	arr.push_back(INT_MIN);
	for(auto i=list.begin(); i!=list.end(); i++) {
		push(*i);
	}
}

// Destructor
Deap::~Deap() {
}

// Function to get the level of an element given its index
int Deap::level(int index) {
	return log2(index+1);
}

// Function to get the index of parent of an element given its index
int Deap::parent(int index) {
	return (index==0) ? -1 : (index-1)/2;
}

// Function to get the index of left child of an element given its index
int Deap::leftChild(int index) {
	return 2*index+1;
}

// Function to get the index of right child of an element given its index
int Deap::rightChild(int index) {
	return 2*index+2;
}

// Function to get the index of corresponding element in min-heap of an element in max-heap
int Deap::minPartner(int index) {
	return index - (1<<(level(index)-1));		// index - 2^(level -1)
}

// Function to get the index of corresponding element in max-heap of an element in min-heap
int Deap::maxPartner(int index) {
	int ans = index + (1<<(level(index)-1));		// index + 2^(level-1)
	return (ans>=arr.size()) ? parent(ans) : ans;
}

// Function to check whether the given index is in min-heap or not
bool Deap::inMinHeap(int index) {
	while(index > 2) {
		index = parent(index);
	}
	return index==1;
}

// Function to check whether the given index is in max-heap or not
bool Deap::inMaxHeap(int index) {
	while(index>3) {
		index = parent(index);
	}
	return index==2;
}

// Function to push up an element in the min-heap
// Same as push up in Min Binary Heap
void Deap::pushUpMin(int index) {
	int ci = index;
	int pi = parent(ci);
	while(pi>=1 && arr[ci] < arr[pi]) {
		swap(arr[ci], arr[pi]);
		ci = pi;
		pi = parent(ci);
	}
}

// Function to push up an element in the max-heap
// Same as push up in Max Binary Heap
void Deap::pushUpMax(int index) {
	int ci = index;
	int pi = parent(ci);
	while(pi>=2 && arr[ci] > arr[pi]) {
		swap(arr[ci], arr[pi]);
		ci = pi;
		pi = parent(ci);
	}
}

// Function to push down an element in the min-heap and return the index of final position
// Same as push down in Min Binary Heap
int Deap::pushDownMin(int index) {
	int pi = index;
	int lci = leftChild(pi), rci = rightChild(pi);
	while(lci<arr.size()) {
		int minIndex = pi;
		if(arr[lci] < arr[minIndex]) {
			minIndex = lci;
		}
		if(rci<arr.size() && arr[rci] < arr[minIndex]) {
			minIndex = rci;
		}
		if(minIndex == pi) {
			break;
		}
		swap(arr[pi], arr[minIndex]);
		pi = minIndex;
		lci = leftChild(pi);
		rci = rightChild(pi);
	}
	return pi;
}

// Function to push down an element in the max-heap and return the index of final position
// Same as push down in Max Binary Heap
int Deap::pushDownMax(int index) {
	int pi = index;
	int lci = leftChild(pi), rci = rightChild(pi);
	while(lci<arr.size()) {
		int maxIndex = pi;
		if(arr[lci] > arr[maxIndex]) {
			maxIndex = lci;
		}
		if(rci<arr.size() && arr[rci] > arr[maxIndex]) {
			maxIndex = rci;
		}
		if(maxIndex == pi) {
			break;
		}
		swap(arr[pi], arr[maxIndex]);
		pi = maxIndex;
		lci = leftChild(pi);
		rci = rightChild(pi);
	}
	return pi;
}

// Function to correct the correspondence condition of an element in min-heap given its index
void Deap::correctCorrespondenceConditionMin(int index) {
	// Only possible case: maxPartner
	int partner = maxPartner(index);
	if(partner>=2 && arr[index] > arr[partner]) {
		swap(arr[index], arr[partner]);
		pushUpMax(partner);
	}
}

// Function to correct the correspondence condition of an element in max-heap given its index
void Deap::correctCorrespondenceConditionMax(int index) {
	// Possible cases: minPartner and its children if they exists
	int partner = minPartner(index);
	int lci = leftChild(partner), rci = rightChild(partner);
	if(partner>=1 && arr[partner] > arr[index]) {
		swap(arr[index], arr[partner]);
		pushUpMin(partner);
	}
	if(lci<arr.size() && arr[lci] > arr[index]) {
		swap(arr[lci], arr[index]);
		pushUpMin(lci);
	}
	if(rci<arr.size() && arr[rci] > arr[index]) {
		swap(arr[rci], arr[index]);
		pushUpMin(rci);
	}
}

// Function to push an element into the deap
void Deap::push(int data) {
	if(empty()) {
		arr.push_back(data);
	} else {
		arr.push_back(data);
		int index = arr.size()-1;
		if(inMinHeap(index)) {		// it is inserted in min heap
			int partner = maxPartner(index);
			if(partner<2) {
				return;
			} else if(arr[index] <= arr[partner]) {		// correspondence condition is satisfied
				pushUpMin(index);
			} else {		// correspondence condition is violated
				correctCorrespondenceConditionMin(index);
			}
		} else {		// it is inserted in max heap
			int partner = minPartner(index);
			if(partner <1) {
				return;
			} else if(arr[index] >= arr[partner]) {		// correspondence condition is satisfied
				pushUpMax(index);
			} else {		// correspondence condition is violated
				correctCorrespondenceConditionMax(index);
			}
		}
	}
}

// Function to pop out the minimum element from the deap
void Deap::popMin() {
	if(empty()) {
		return;
	} else if(arr.size()==2) {		// Deap has only 1 element
		arr.pop_back();
	} else {
		arr[1] = arr[arr.size()-1];		// putting the last element at place of minimum element
		arr.pop_back();
		int stableIndex = pushDownMin(1);		// pushing it down in min heap and getting the final index
		correctCorrespondenceConditionMin(stableIndex);
	}
}

// Function to pop out the maximum element from the deap
void Deap::popMax() {
	if(empty()) {
		return;
	} else if(arr.size()==2) {		// Deap has only one element
		arr.pop_back();
	} else {
		arr[2] = arr[arr.size()-1];		// putting the last element at place of maximum element
		arr.pop_back();
		int stableIndex = pushDownMax(2);		// pushing it down in min heap and getting the final index
		correctCorrespondenceConditionMax(stableIndex);
	}
}

// Function to return the value of the minimum element in the deap
int Deap::topMin() {
	return (empty()) ? INT_MIN : arr[1];
}

// Function to return the value of the maximum element in the deap
int Deap::topMax() {
	if(empty()) {
		return INT_MAX;
	} else if(arr.size()==2) {
		return arr[1];
	} else {
		return arr[2];
	}
}

// Function to return the size of the deap
int Deap::size() {
	return arr.size()-1;
}

// Function to check if the deap is empty or not
bool Deap::empty() {
	return arr.size()==1;
}

// Function to print the elements of the deap in form of a tree
// For Testing purposes
void Deap::print() {
	cout << "The Deap is: " << endl;
	cout << "X" << endl;
	for(int i=1; i<arr.size(); i++) {
		cout << arr[i] << " ";
		if(level(i)!=level(i+1)) {
			cout << endl;
		}
	}
	cout << endl;
}

#endif // _DEAP_

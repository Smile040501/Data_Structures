#include<iostream>
#include<queue>
#include<unordered_map>
#include<sstream>
#include<string>
using namespace std;

// ****************** Huffman Coding ******************

// BinaryTreeNode class to represent a node of the tree in Huffman Coding
class BinaryTreeNode {
public:
	char data;		// Data value of the node
	int freq;		// Frequency of that data value
	BinaryTreeNode *left;		// pointer to left child
	BinaryTreeNode *right;	// pointer to right child
	
	// Constructors
	BinaryTreeNode(char data, int freq, BinaryTreeNode *left, BinaryTreeNode *right)
	: data{data}, freq{freq}, left{left}, right{right} {
	}
	
	BinaryTreeNode(char data, int freq)
	: BinaryTreeNode(data, freq, nullptr, nullptr) {
	}
	
	// Destructor
	~BinaryTreeNode() {
		if(left) {
			delete left;
		}
		if(right) {
			delete right;
		}
	}
	
};

// Function to count the frequency of each char in the given input line
void countFrequency(string line, unordered_map<char, int> &freq) {
	stringstream ss{line};
	string word;
	while(ss>>word) {
		for(const auto &c: word) {
			freq[c]++;
		}
	}
}

// Function to make the code of each char as per Huffman Coding
void makeCharCodes(BinaryTreeNode *root, string code, unordered_map<char, string> &charCodes, unordered_map<string, char> &codesChar) {
	if(!root->left && !root->right) {
		charCodes[root->data] = code;
		codesChar[code] = root->data;
		return;
	}
	makeCharCodes(root->left, code+'0', charCodes, codesChar);
	makeCharCodes(root->right, code+'1', charCodes, codesChar);
}

// Function to compress a line
string compress(string line, unordered_map<char, string> &charCodes) {
	stringstream ss{line};
	string word, result;
	while(ss >> word) {
		for(const auto &c: word) {
			result += charCodes[c];
		}
		result += " ";
	}
	return result;
}

// Function to decompress a compressed line
string decompress(string line, unordered_map<string, char> &codesChar) {
	stringstream ss{line};
	string word, result;
	while(ss >> word) {
		string temp;
		for(const auto &c: word) {
			temp += c;
			if(codesChar.count(temp)!=0) {
				result += codesChar[temp];
				temp = "";
			}
		}
		result += " ";
	}
	return result;
}

int main() {
	// Sample input file string
	string line = "lorem ipsum dolor sit amet consectetur adipiscing elit sed do eiusmod tempor incididunt ut labore et dolore magna aliqua faucibus et molestie ac feugiat lectus mauris ultrices eros in cursus turpis massa tincidunt massa sapien faucibus et molestie ac feugiat sed non enim praesent elementum facilisis sem nulla pharetra diam sit amet nisl suscipit turpis massa tincidunt dui ut ornare lectus sit semper risus in hendrerit gravida rutrum amet est placerat in egestas erat imperdiet sed euismod nisi convallis a cras semper auctor neque vitae tempus diam maecenas sed enim ut sem pellentesque massa placerat duis ultricies sit amet mauris commodo quis imperdiet massa tincidunt nunc pulvinar laoreet sit amet cursus sit amet dictum sit amet justo scelerisque mauris pellentesque pulvinar pellentesque habitant morbi fringilla ut morbi tincidunt augue interdum ssenectus et netus et malesuada felis imperdiet proin fermentum leo vel orci id volutpat lacus laoreet non";
	unordered_map<char, int> freq;			// To store the frequency of each char
	countFrequency(line, freq);
	
	// Comparison function for making priority queue of BinaryTreeNode *
	auto cmp = [](BinaryTreeNode *x, BinaryTreeNode *y) {
		if(x->freq != y->freq) {
			return x->freq > y->freq;
		} else {
			return x->data > y->data;
		}
	};
	priority_queue<BinaryTreeNode *, vector<BinaryTreeNode *>, decltype(cmp)> pq(cmp);
	
	// Initially pushing all the characters as leaf nodes to the priority queue
	for(const auto &p: freq) {
		pq.push(new BinaryTreeNode(p.first, p.second));
	}
	
	// Building the Huffman Coding tree
	while(pq.size()>1) {
		BinaryTreeNode *left = pq.top();
		pq.pop();
		BinaryTreeNode *right = pq.top();
		pq.pop();
		BinaryTreeNode *newNode = new BinaryTreeNode('\0', left->freq+right->freq, left, right);
		pq.push(newNode);
	}
	
	BinaryTreeNode *root = pq.top();
	unordered_map<char, string> charCodes;		// map(char, code)		for compressing
	unordered_map<string, char> codesChar;		// map(code, char)		for decompressing
	makeCharCodes(root, "", charCodes, codesChar);
	
	// cout << "The compressed line after Huffman Coding is: " << endl;
	string compressedLine = compress(line, charCodes);
	cout << compressedLine << endl;
	
	// cout << "Decompressing the compressed line: " << endl;
	string decompressedLine = decompress(compressedLine, codesChar);
	cout << decompressedLine << endl;
	
	std::cout << std::endl;
	return 0;
}

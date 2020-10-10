#ifndef _TRIE_NODE_
#define _TRIE_NODE_

// TrieNode class for representing a node of a Trie
class TrieNode {
public:
	char data;		// Data of the node
	TrieNode **children;		// The array of pointers to the children of the node
	bool isTerminal;		// To check whether a node is end of a word or not
	
	// Constructor
	TrieNode(char data);
	
	// Destructor
	~TrieNode();
};

// Constructor
TrieNode::TrieNode(char data)
: data{data}, children{new TrieNode*[26]}, isTerminal{false} {
	for(int i=0; i<26; i++) {
		children[i] = nullptr;
	}
}

// Destructor
TrieNode::~TrieNode() {
	for(int i=0; i<26; i++) {
		if(children[i]) {
			delete children[i];
		}
	}
}

#endif // _TRIE_NODE_

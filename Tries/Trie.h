#ifndef _TRIE_
#define _TRIE_

#include "TrieNode.h"

// Trie class of representation of a Trie
class Trie {
	TrieNode *root;		// root of the Trie
	
	// Function to insert a word in the Trie
	void insert(TrieNode *root, string word);
	// Function to search for a word in the Trie
	bool search(TrieNode *root, string word);
	// Function to check whether a node has any children or not
	bool hasChildren(TrieNode *root);
	// Function to remove a word from the Trie
	TrieNode * remove(TrieNode *root, string word);
	// Function to print all the words in the Trie
	void printAllWords(TrieNode *root, string word);
	// Function to count the total number of words in the Trie
	int countWords(TrieNode *root);
	
	// Function to add all the suffixes of a word in the Trie
	void addAllSuffixes(string word);
	// Function search for a pattern in the Trie
	bool searchPattern(TrieNode *root, string pattern);
	// Function to print all the words that start with the given pattern of a word
	void autoComplete(TrieNode *root, string pattern, string output);
	// Function to check if a string is palindrome or not
	bool isPalindrome(string str);
	// Function to store all those nodes in the map whose rest string is a palindrome
	void populate(TrieNode *root, string word, unordered_map<TrieNode *, bool> &m);
	// Function to search for a palindrome pair in the Trie
	bool searchPalindrome(TrieNode *root, string word, const unordered_map<TrieNode *, bool> &m);
	
public:
	// Constructors
	Trie();
	Trie(initializer_list<string> list);
	
	// Destructor
	~Trie();
	
	// Function to insert a word in the Trie
	void insert(string word);
	// Function to search for a word in the Trie
	bool search(string word);
	// Function to remove a word from the Trie
	void remove(string word);
	// Function to print all the words in the Trie
	void printAllWords();
	// Function to count the total number of words in the Trie
	int countWords();
	
	// Function to search for a pattern in the given words
	bool patternMatching(vector<string> words, string pattern);
	// Function to print all the words that start with the given pattern of a word
	void autoComplete(string pattern);
	// Function to check whether any two words can be joined to form a palindrome or any word itself is a palindrome
	bool isPalindromePair(vector<string> words);
};

// Constructors
Trie::Trie()
: root{new TrieNode('\0')} {
}

Trie::Trie(initializer_list<string> list)
: root{new TrieNode('\0')} {
	for(auto i=list.begin(); i!=list.end(); i++) {
		insert(*i);
	}
}

// Destructor
Trie::~Trie() {
	delete root;
}

// Function to insert a word in the Trie
void Trie::insert(TrieNode *root, string word) {
	if(word.length()==0) {
		root->isTerminal = true;
		return;
	}
	int index = word[0] - 'a';
	if(!root->children[index]) {
		root->children[index] = new TrieNode(word[0]);
	}
	insert(root->children[index], word.substr(1));
}

void Trie::insert(string word) {
	if(word.length()==0) {
		return;
	}
	insert(root, word);
}

// Function to search for a word in the Trie
bool Trie::search(TrieNode *root, string word) {
	if(word.length()==0) {
		return root->isTerminal;
	}
	int index = word[0] - 'a';
	return (!root->children[index]) ? false : search(root->children[index], word.substr(1));
}

bool Trie::search(string word) {
	return search(root, word);
}

// Function to check whether a node has any children or not
bool Trie::hasChildren(TrieNode *root) {
	if(!root) {
		return false;
	}
	for(int i=0; i<26; i++) {
		if(root->children[i]) {
			return true;
		}
	}
	return true;
}

// Function to remove a word from the Trie
TrieNode * Trie::remove(TrieNode *root, string word) {
	if(word.length()==0) {
		root->isTerminal = false;
		if(hasChildren(root)) {
			return root;
		} else {
			delete root;
			return nullptr;
		}
	}
	int index = word[0] - 'a';
	if(root->children[index]) {
		root->children[index] = remove(root->children[index], word.substr(1));
		if(hasChildren(root)) {
			return root;
		} else {
			delete root;
			return nullptr;
		}
	} else {
		return root;
	}
}

void Trie::remove(string word) {
	remove(root, word);
}

// Function to print all the words in the Trie
void Trie::printAllWords(TrieNode *root, string word) {
	if(root->isTerminal) {
		cout << word << " ";
	}
	for(int i=0; i<26; i++) {
		if(root->children[i]) {
			printAllWords(root->children[i], word+root->children[i]->data);
		}
	}
}

void Trie::printAllWords() {
	cout << "Words in the Trie are: ";
	printAllWords(root, "");
	cout << endl;
}

// Function to count the total number of words in the Trie
int Trie::countWords(TrieNode *root) {
	int ans = (root->isTerminal) ? 1 : 0;
	for(int i=0; i<26; i++) {
		if(root->children[i]) {
			ans += countWords(root->children[i]);
		}
	}
	return ans;
}

int Trie::countWords() {
	return countWords(root);
}

// Function to add all the suffixes of a word in the Trie
void Trie::addAllSuffixes(string word) {
	if(word.length()==0) {
		return;
	}
	insert(word);
	addAllSuffixes(word.substr(1));
}

// Function search for a pattern in the Trie
bool Trie::searchPattern(TrieNode *root, string pattern) {
	if(pattern.length()==0) {
		return true;
	}
	int index = pattern[0] - 'a';
	return (!root->children[index]) ? false : searchPattern(root->children[index], pattern.substr(1));
}

// Function to search for a pattern in the given words
bool Trie::patternMatching(vector<string> words, string pattern) {
	for(const auto &w: words) {
		addAllSuffixes(w);
	}
	return searchPattern(root, pattern);
}

// Function to print all the words that start with the given pattern of a word
void Trie::autoComplete(TrieNode *root, string pattern, string output) {
	if(pattern.length()==0) {
		if(root->isTerminal) {
			cout << output << " ";
		}
		for(int i=0; i<26; i++) {
			if(root->children[i]) {
				autoComplete(root->children[i], pattern, output + root->children[i]->data);
			}
		}
		return;
	}
	int index = pattern[0] - 'a';
	if(root->children[index]) {
		autoComplete(root->children[index], pattern.substr(1), output+root->children[index]->data);
	} else {
		return;
	}
}

void Trie::autoComplete(string pattern) {
	cout << "Words starting with \"" << pattern << "\" : ";
	autoComplete(root, pattern, "");
	cout << endl;
}

// Function to check if a string is palindrome or not
bool Trie::isPalindrome(string str) {
	int i=0, j=str.length()-1;
	while(i<j) {
		if(str[i] != str[j]) {
			return false;
		}
		i++;
		j--;
	}
	return true;
}

// Function to store all those nodes in the map whose rest string is a palindrome
void Trie::populate(TrieNode *root, string word, unordered_map<TrieNode *, bool> &m) {
	if(word.length()==0) {
		m[root] = true;
	} else {
		if(isPalindrome(word)) {
			m[root] = true;
		}
		populate(root->children[word[0] - 'a'], word.substr(1), m);
	}
}

// Function to search for a palindrome pair in the Trie
bool Trie::searchPalindrome(TrieNode *root, string word, const unordered_map<TrieNode *, bool> &m) {
	if(word.length()==0) {
		return m.count(root) != 0;
	}
	int index = word[0] - 'a';
	if(root->children[index]) {
		return searchPalindrome(root->children[index], word.substr(1), m);
	} else {
		return root->isTerminal && isPalindrome(word);
	}
}

// Function to check whether any two words can be joined to form a palindrome or any word itself is a palindrome
bool Trie::isPalindromePair(vector<string> words) {
	unordered_map<TrieNode *, bool> m;
	for(auto w: words) {
		reverse(w.begin(), w.end());
		insert(w);
		populate(root->children[w[0]-'a'], w.substr(1), m);
	}
	for(const auto &w: words) {
		if(searchPalindrome(root, w, m)) {
			return true;
		}
	}
	return false;
}

#endif // _TRIE_

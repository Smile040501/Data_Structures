#include<iostream>
#include<vector> 
#include<string>
#include<initializer_list>
#include<unordered_map>
#include<algorithm>
using namespace std;

#include "Trie.h"

// Sample main
int main() {
	Trie trie1{"do", "dont", "no", "not", "note", "notes", "den"};
	trie1.printAllWords();
	cout << "Number of words in the trie: " << trie1.countWords() << endl;
	cout << boolalpha;
	cout << "Is \"node\" word present in the trie: " << trie1.search("node") << endl;
	cout << "Is \"notes\" word present in the trie: " << trie1.search("notes") << endl;
	trie1.remove("notes");
	cout << "Is \"notes\" word present in the trie: " << trie1.search("notes") << endl;
	
	vector<string> words = {"do", "dont", "no", "not", "note", "notes", "noted", "den"};
	Trie trie2;
	cout << "Is \"ot\" pattern present: " << trie2.patternMatching(words, "ot") << endl;
	cout << "Is \"et\" pattern present: " << trie2.patternMatching(words, "et") << endl;
	cout << "Words starting with \"no\":" << endl;
	trie2.autoComplete("no");
	
	words = {"cba", "def", "jkl", "bc"};
	Trie trie3;
	cout << "Is palindrome pair present: " << trie3.isPalindromePair(words) << endl;
	
	words = {"aaa", "bcd", "efg", "hij"};
	Trie trie4;
	cout << "Is palindrome pair present: " << trie4.isPalindromePair(words) << endl;
	
	words = {"def", "abc", "jkl", "mno", "pqr"};
	Trie trie5;
	cout << "Is palindrome pair present: " << trie5.isPalindromePair(words) << endl;
	
	std::cout << std::endl;
	return 0;
}

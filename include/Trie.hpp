#pragma once
// THIS IS THE TEMPLATE COPIED FROM GOOGLE DOCS ONLY, WITH FUNCTION PROTOTYPE SUGGESTION, FOR EASY WORK

#include<Libraries.hpp>

const int ALPHABET_SIZE=26;

class Trie
{
private:
	struct Node
	{
		int numWords;
		bool isEnd;
		Node* child[ALPHABET_SIZE];
  	};

	Node* root;

	// Get the index from the given character in the alphabet
	int getIndex(char c);//
	// Get the character in the alphabet from the given index
	char rGetIndex(int index);
	
public:
	Trie();			

	// Deallocate all nodes
	void clear();									

	// Load from binary file
	bool import(const std::string& path);					

	// Save as binary file
	bool save(const std::string& path);						

	// Insert a word in the trie
	void insert(const std::string& word);					

	// Remove a word out of trie
	void remove(const std::string& word);					
	
	// Check whether a word is in the trie
	bool checkExist(const std::string& key);//					

	// Returns a list of std::strings which have identical prefix
	std::vector<std::string> searchPrefix(const std::string& prefix);//
	void recursiveFind(std::vector<std::string>& res,std::string prefix, Trie::Node* cur, int& cnt);		

	// Get all the words that was embedded in the trie
	std::vector<std::string> getList();							
};


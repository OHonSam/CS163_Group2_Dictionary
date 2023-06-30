
#pragma once

#include <string>
#include <vector>
#include <fstream>

const int ALPHABET_SIZE=26;

class Trie
{
private:
	const char TERMINATOR='\0';

	struct Node
	{
		int numWords; // Number of words that have this prefix
		bool isEnd;
		Node* child[ALPHABET_SIZE];
  	};

	Node* root;

	int getIndex(char c);
	char rGetIndex(int index);

	void remove(Node* &root, const std::string& word, int index);

	void import(Node* &node, std::ifstream& file);
	void save(Node* node, std::ofstream& file);
	
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
	bool check(const std::string& word);					

	// Returns a list of strings which have identical prefix
	std::vector<std::string> searchPrefix(const std::string& prefix);		

	// Get all the words that was embedded in the trie
	std::vector<std::string> getList();							
};


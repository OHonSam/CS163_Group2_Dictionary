#ifndef SMALLTRIE_HPP
#define SMALLTRIE_HPP

#include<iostream>
#include<fstream>
#include<vector>
#include<utility>//to use pair
#include<string>
#include <sstream>
#include <time.h>
// #include <algorithm>
#include<cstring>


const int ALPHABET_SIZE = 26;
const char TERMINATOR = '\0';

class SmallTrie
{

public:
    struct Node
    {
        bool isRoot;
        bool isEnd;
        int numWords;
        std::vector<Node*> child;
        std::vector<int> childNum;
        Node()
        {
            isRoot = false;
            isEnd = false;
            numWords = 0;
            child.resize(26, nullptr);
        }
    };
    Node* root;
    // std::vector <std::string> keywords; // for listing all keywords in linear time

    // Get the index from the given character in the alphabet
	int getIndex(char c);
	// Get the character in the alphabet from the given index
	char rGetIndex(int index);

    void import(Node* &root, std::ifstream& in); 
    void save(Node* root, std::ofstream& out); 

    SmallTrie()
    { 
        root = new Node();
        root -> isRoot = true;
    }
    ~SmallTrie() {
        deallocate(root);
    }

    // Deallocate all nodes
    void deallocate(Node* &root);

    // Load from binary file
    bool import(const std::string& path);

    // Save as binary file
    bool save(const std::string& path);

    // Insert a keyword in trie
    void insert(const std::string& word);

    // Remove a keyword out of trie
    void remove(const std::string& word); 
    void remove(Node* &root, const std::string& word, int index);

    // Check if keyword exists
    bool search(const std::string& word);

    // Get all words in the trie
    std::vector<std::string> keywords();
    void get(std::vector<std::string> &res, Node* root, std::string word);

};
#endif
#ifndef DEFTRIE_HPP
#define DEFTRIE_HPP

// #include "Libraries.hpp"
#include "Word.hpp"
#include "SmallTrie.hpp"

#include<iostream>
#include<fstream>
#include<vector>
#include<utility>//to use pair
#include<string>
#include <sstream>
#include <time.h>
// #include <algorithm>
#include<cstring>


// const int ALPHABET_SIZE = 26;
// const char TERMINATOR = '\0';

class DefTrie: public SmallTrie
{

private:
    struct Node
    {
        bool isEnd;
        int numWords;
        std::vector<Node*> child;

        //each sequence of characters in the DefTrie is a single word of keywords' definition
        //each sequence of characters contains a list of possible keywords

        SmallTrie* st;
        Node()
        {
            isEnd = false;
            numWords = 0;
            child.resize(26, nullptr);
            st = new SmallTrie();
        }
    };
    Node* root;

    // Get the index from the given character in the alphabet
	int getIndex(char c);
	// Get the character in the alphabet from the given index
	char rGetIndex(int index);

    std::vector<std::string> defWord(const std::string def);

    void insert(const std::string& word, const std::string& def);
    void remove(Node* &root, const std::string& word, const std::string &keyword, int index);

    void recursiveFind(std::vector<std::string>& res, std::string prefix, DefTrie::Node* cur, int& cnt); 

    Node* search(const std::string defword);
    std::vector<std::string> getKeyWords(DefTrie::Node* cur);

    void merge(SmallTrie* &res, SmallTrie::Node* p1, SmallTrie::Node* p2, std::string keyword);

    void import(Node* &root, std::ifstream& in); 
    void save(Node* root, std::ofstream& out); 

    void deallocate(Node* &root);
public:
    DefTrie() 
    { 
        root = new Node();
    }
    ~DefTrie() {
        clear();
    }

    // Deallocate all nodes
    void clear();

    // Load from binary file
    bool import(const std::string& path); 

    // Save as binary file
    bool save(const std::string& path); 

    // Insert a word in the trie
    void insert(Word* word);

    // Remove a word out of trie
    void remove(Word* word);

    // Update definition of a word would call thiss function to modify DefTrie
    void updateDef(const std::string& word, unsigned int type, const std::string& oldDef, const std::string& newDef);

    // Returns a list of std::strings which have identical prefix
    std::vector<std::string> searchPrefix(const std::string& prefix); 

    // Search for a word that has the definition
    std::vector<std::string> searchKeyWord(const std::string def); 

    // Merge two small trie
    SmallTrie* merge(SmallTrie* st1, SmallTrie* st2);

};
#endif
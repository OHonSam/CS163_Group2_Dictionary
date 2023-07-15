#ifndef DEFTRIE_HPP
#define DEFTRIE_HPP

#include "Libraries.hpp"
#include "Word.hpp"

const int ALPHABET_SIZE=26;
const char TERMINATOR = '\0';

class DefTrie
{
private:
    struct Node
    {
        bool isEnd;
        int numWords;
        //std::string def;
        std::vector<Node*> child;
        //each sequence of characters in the DefTrie is a substring of keywords' definition
        //each sequence of characters contains a list of possible keywords
        std::vector<std::string> keywords;
        Node()
        {
            isEnd = false;
            numWords = 0;
            //def = "";
            child.resize(26, nullptr);
            keywords.resize(0);
        }
    };
    Node* root;

    // Get the index from the given character in the alphabet
	int getIndex(char c);
	// Get the character in the alphabet from the given index
	char rGetIndex(int index);

    // std::string getDef(const std::string word);
    std::vector<std::string> defWord(const std::string def);

    void remove(Node* &root, const std::string& word, const std::string &keyword, int index);
    // void insert(Node* &root, const std::string& word, const std::string &keyword, int index);
    // void insert(const std::string& word, const std::string& def);

    void recursiveFind(std::vector<std::string>& res, std::string prefix, DefTrie::Node* cur, int& cnt); //x

    void import(Node* &root, std::ifstream& in); //x
    void save(Node* root, std::ofstream& out); //x
public:
    DefTrie() 
    { 
        root = new Node();
    }
    ~DefTrie();

    // Deallocate all nodes
    void clear();
    void deallocate(Node* root);

    // Load from binary file
    bool import(const std::string& path); //x

    // Save as binary file
    bool save(const std::string& path); //x

    // Insert a definition in the trie
    void insert(const std::string& word, const std::string& def);
    // Insert a word in the trie
    void insert(Word* word);

    // Remove a word out of trie
    void remove(Word* word); 

    // Returns a list of std::strings which have identical prefix
    std::vector<std::string> searchPrefix(const std::string& prefix); //x

    // Search for a word that has the definition
    std::vector<std::string> searchKeyWord(const std::string def); //x
};
#endif
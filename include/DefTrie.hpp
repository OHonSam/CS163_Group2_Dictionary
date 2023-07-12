#ifndef DEFTRIE_HPP
#define DEFTRIE_HPP

#include <Libraries.hpp>

const int ALPHABET_SIZE=26;
const char TERMINATOR = '\0';

class DefTrie
{
private:
    struct Node
    {
        bool isEnd;
        int numWords;
        // std::string def;
        std::vector<Node*> child;
        std::vector<std::string> keywords;
        Node()
        {
            isEnd = false;
            numWords = 0;
            // def = "";
            child.resize(26, nullptr);
            keywords.resize(0);
        }
    };
    Node* root;

    // Get the index from the given character in the alphabet
	int getIndex(char c);
	// Get the character in the alphabet from the given index
	char rGetIndex(int index);

    std::string getDef(const std::string word);
    std::vector<std::string> defWord(const std::string def);

    void remove(Node* &root, const std::string& word, const std::string &keyword, int index);
    void insert(Node* &root, const std::string& word, const std::string &keyword, int index);

    void recursiveFind(std::vector<std::string>& res,std::string prefix, DefTrie::Node* cur, int& cnt);

    void import(Node* &node, std::ifstream& file);
    void save(Node* node, std::ofstream& file);
public:
    DefTrie() 
    { 
        root = new Node();
    }
    ~DefTrie();

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

    // Returns a list of std::strings which have identical prefix
    std::vector<std::string> searchPrefix(const std::string& prefix);

    // Search for a word that has the definition
    std::vector<std::string> searchDef(std::vector<std::string> def);
};
#endif
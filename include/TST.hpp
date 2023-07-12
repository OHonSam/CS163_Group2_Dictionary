// Ternary Search Tree
#ifndef TST_HPP
#define TST_HPP

#include "Libraries.hpp"
#include "Word.hpp"

class TSTNode
{
    TSTNode *left, *mid, *right;
    char c; // character contained in TSTNode
    bool isEnd;
    int numWords; // Number of words that have this prefix
    bool isLeaf;

    friend class TST;

public:
    TSTNode(char _c) : c(_c), left(nullptr), mid(nullptr), right(nullptr) {}
    TSTNode() {}

    ~TSTNode()
    {
        delete left;
        left = nullptr;

        delete right;
        right = nullptr;

        delete mid;
        mid = nullptr;
    }
};

class TST
{
    TSTNode *root;
    const char TERMINATOR = '\0';
    const int LIMIT_NUM_OF_RESULTS_PREFIX_FAVLIST = 20;

    void import(TSTNode *&root, std::ifstream &file);
    void save(TSTNode *root, std::ofstream &file);

    // Insert into the TST
    void TST::recursiveInsert(TSTNode *&node, const std::string &str, int index);
    // TSTNode *recursiveInsert(TSTNode *&node, const std::string &str, int index);

    void deletion(TSTNode *&node, const std::string &str, int index);

    // Get Node containing the last word in the string
    TSTNode *getNodeLastChar(TSTNode *node, const std::string &str, int index);

public:
    TST()
    {
        root = nullptr;
    }

    ~TST()
    {
        delete root;
        root = nullptr;
    }

    void insert(const std::string &word);
    void deletion(const std::string &word);

    // Return true if the word is in the TST
    bool wordExists(const std::string &word);

    // Return true if there is any word in the trie that starts with the given prefix
    bool isStartedWith(const std::string &prefix);

    //Return words in the trie that starts with the given prefix
    std::vector<std::string>startsWith(const std::string &prefix);
    std::vector<std::string>startsWithRecursiveSearch(std::vector<std::string> &res, const std::string &prefix, TSTNode *cur, int &cnt);

    bool import(const std::string &path);
    bool save(const std::string &path);
};

#endif

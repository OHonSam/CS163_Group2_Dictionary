// Ternary Search Tree
#ifndef TST_HPP
#define TST_HPP

#include "Libraries.hpp"
#include "Word.hpp"

class TSTNode
{
    char c; // character contained in TSTNode
    TSTNode *left, *mid, *right;
    bool isEnd;
    int numWords; // Number of words that have this prefix

    friend class TST;
    friend class favList;

public:
    TSTNode(char _c) : c(_c), left(nullptr), mid(nullptr), right(nullptr), isEnd(0), numWords(0) {}
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
    void traverse(std::vector<std::string> &res, TSTNode *root, std::string str, int &cnt);


    // Insert into the TST
    void recursiveInsert(TSTNode *&node, const std::string &str, int index);
    // TSTNode *recursiveInsert(TSTNode *&node, const std::string &str, int index);

    void remove(TSTNode *&node, const std::string &str, int index);

    // Get Node containing the last word in the string
    TSTNode *getNodeLastChar(TSTNode *node, const std::string &str, int index);

    friend class favList;

public:
    TST()
    {
        root = nullptr;
    }

    ~TST()
    {
        clear();
    }

    void clear();

    void insert(const std::string &word);
    void remove(const std::string &word);
    std::vector<std::string> traverse();


    // Return true if the word is in the TST
    bool wordExists(const std::string &word);

    // Return true if there is any word in the trie that starts with the given prefix
    bool isStartedWith(const std::string &prefix);

    //Return words in the trie that starts with the given prefix
    std::vector<std::string>startWith(const std::string &prefix);

    bool import(const std::string &path);
    bool save(const std::string &path);    

    bool treeExists();

    void uppercase2Lowercase(std::string &str);
    
    
    
    //for screen type2RemoveWord
    void type2RemoveWord();
    
    //for screen type2InsertWord
    void type2InsertWord();

    //for screen searchPrefix
    void searchPrefix();
};

#endif

// Ternary Search Tree
#ifndef TST_HPP
#define TST_HPP

#include "Libraries.hpp"
#include "Word.hpp"

class TSTNode
{
    TSTNode *left, *mid, *right;
    char c; //character contained in TSTNode
    bool isEnd;
    int numWords; // Number of words that have this prefix

    //Insert into the TST
    TSTNode *insert(TSTNode *node, const std::string &str, int index);

    //Get Node containing the last word in the string
    TSTNode *get(TSTNode *node, const std::string &str, int index);

    friend class TST;

public:
    TSTNode(char _c) : c(_c), left(nullptr), mid(nullptr), right(nullptr)
    {
    }
    TSTNode(){}

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

    void import(TSTNode *&node, std::ifstream &file);
    void save(TSTNode *node, std::ofstream &file);

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

    bool search(const std::string &word);
    
    // Returns if there is any word in the trie that starts with the given prefix.
    bool startsWith(const std::string &prefix);

    bool import(const std::string &path);
    bool save(const std::string &path);
};

#endif

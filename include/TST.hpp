// Ternary Search Tree
#ifndef TST_HPP
#define TST_HPP

class TSTNode
{
    TSTNode *left, *mid, *right;
    char c;
    bool is_end;

    friend class TST;

    TSTNode* get(TSTNode* node, const std::string & str, int index);

public:
    TSTNode(char _c) : c(_c), left(nullptr), mid(nullptr), right(nullptr) {}

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

    void insert(const std::string& word);
    void deletion(const std::string& word);
    bool search(const std::string& word);
    bool startsWith(const std::string& prefix);
};

#endif

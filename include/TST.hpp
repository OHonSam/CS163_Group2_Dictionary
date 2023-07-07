// Ternary Search Tree
#ifndef TST_HPP
#define TST_HPP

class TSTNode
{
    TSTNode *left, *mid, *right;
    char c;
    bool isEnd;
    int numWords; // Number of words that have this prefix

    TSTNode *put(TSTNode *node, const std::string &str, int index);
    TSTNode *get(TSTNode *node, const std::string &str, int index);

    friend class TST;

public:
    TSTNode(char _c) : c(_c), left(nullptr), mid(nullptr), right(nullptr)
    {
    }
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
    bool startsWith(const std::string &prefix);
    bool import(const std::string &path);
    bool save(const std::string &path);
};

#endif

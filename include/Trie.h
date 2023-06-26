#pragma once

#include <vector>
#include <string>

const int ALPHABET_SIZE = 26;

class Trie
{
private:
    struct Node
    {
        int numWords;
        bool isEnd;
        Node* children[26];
    };

    Node* root;

public:
    Trie();
    ~Trie();

    void insert(const std::string& word);
    bool search(const std::string& word);
    std::vector<std::string> searchPrefix(const std::string& prefix);
};
// #include <Libraries.hpp>
// #include <DefTrie.hpp>
// #include<Trie.hpp>

#include "D:\cs163\CS163_Group2_Dictionary\include\DefTrie.hpp"

int DefTrie::getIndex(char c)
{
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return -1;
}

char DefTrie::rGetIndex(int index)
{
    if (index < 0 || index >= ALPHABET_SIZE) return '\0';
    return index + 'a';
}

void DefTrie::remove(Node *&root, const std::string &word, const std::string &keyword, int index)
{
    // index initialized with 0, word's length = max index including root
    if (root == NULL) return;
    root->numWords--;
        
    if (index == word.length()) {
        for (int i = 0; i < root -> keywords.size(); i++)
        {
            if (root -> keywords[i] == keyword) root -> keywords.erase(root -> keywords.begin() + i); break;
        }
        if (!root -> keywords.size()) root -> isEnd = false;
    }
    else
    {
        int i = getIndex(word[index]);
        remove(root -> child[i], word, keyword, index + 1);
    }
    
    if (root -> numWords == 0)
    {
        delete root;
        root = NULL;
    }
    return;
}

std::vector<std::string> DefTrie::defWord(const std::string def) {
    std::stringstream s(def);
    std::string word;
    std::vector <std::string> res;
    while (s >> word) res.push_back(word);
    return res;
}

// void DefTrie::insert(Node* &root, const std::string& word, const std::string &keyword, int index) {
//     if (!root) root = new Node();
//     root -> numWords++;
//     if (index == word.length()) {
//         root -> isEnd = true;
//         root -> keywords.push_back(keyword);
//     }
//     else {
//         int i = getIndex(word[index]);
//         insert(root -> child[i], word, keyword, index + 1);
//     }
//     return;
// }

// I need to test it before continue

void DefTrie::insert(const std::string& word, const std::string& def){
    // if (root == nullptr) {
    //     root = new Node();
    // }
    for (int i = 0; i < def.size(); ++i) {
        int index = getIndex(def[i]);
        if (!root -> child[index]) root -> child[index] = new Node();
        ++root -> child[index] -> numWords;
        root = root -> child[index];
    }
    root -> isEnd = true;
    root -> keywords.push_back(word);
    return;
}

void DefTrie::insert(Word* word) {
    for (int i = 0; i < POS::Count; i++) {
        if (word -> type & (1 << i)) {
            for (int j = 0; j < word -> def[i].size(); j++) {
                std::vector <std::string> defW;
                defW = defWord(word -> def[i][j]);
                for (int k = 0; k < defW.size(); k++) insert(word -> word, defW[k]);
            }
        }
    }
    return;
}

void DefTrie::remove(Word* word) {
    for (int i = 0; i < POS::Count; i++) {
        if (word -> type & (1 << i)) {
            for (int j = 0; j < word -> def[i].size(); j++) {
                std::vector <std::string> defW;
                defW = defWord(word -> def[i][j]);
                for (int k = 0; k < defW.size(); k++) remove(DefTrie::root, defW[k], word -> word, 0);
            }
        }
    }
    return;
}

void DefTrie::deallocate(Node* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) deallocate(root -> child[i]);
    delete root;
    return;
}

void DefTrie::clear() {
    deallocate(DefTrie::root);
    return;
}
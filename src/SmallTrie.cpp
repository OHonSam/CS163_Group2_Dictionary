#include "D:\cs163\CS163_Group2_Dictionary\include\SmallTrie.hpp"

int SmallTrie::getIndex(char c)
{
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return -1;
}

char SmallTrie::rGetIndex(int index)
{
    if (index < 0 || index >= ALPHABET_SIZE) return '\0';
    return index + 'a';
}

void SmallTrie::insert(const std::string& word) {
    Node* cur = SmallTrie::root;
    ++cur -> numWords;
    for (int i = 0; i < word.size(); ++i) {
        int index = getIndex(word[i]);
        if (!cur -> child[index]) {
            cur -> child[index] = new Node();
            cur -> childNum.push_back(index);
        }
        ++cur -> child[index] -> numWords;
        cur = cur -> child[index];
    }
    cur -> isEnd = true;
    return;
}

void SmallTrie::remove(const std::string& word) {
    remove(SmallTrie::root, word, 0);
    return;
}

void SmallTrie::remove(Node* &root, const std::string& word, int index) {
    // index initialized with 0, word's length = max index including root
    if (!root) return;
    --root -> numWords;
        
    if (index == word.length()) root -> isEnd = false;
    else
    {
        int i = getIndex(word[index]);
        remove(root -> child[i], word, index + 1);
    }
    
    if (root -> numWords == 0 && root != SmallTrie::root)
    {
        delete root;
        root = nullptr;
    }
    return;
}

bool SmallTrie::search(const std::string& word) {
    Node* cur = SmallTrie::root;
    for (int i = 0; i < word.size(); ++i) {
        int index = getIndex(word[i]);
        if (!cur -> child[index]) return false;
        cur = cur -> child[index];
    }
    return true;
}

std::vector<std::string> SmallTrie::keywords() {
    std::vector<std::string> res;
    get(res, SmallTrie::root, "");
    return res;
}

void SmallTrie::get(std::vector<std::string> &res, Node* root, std::string word) {
    if (root -> isEnd) res.push_back(word);
    for (int i = 0; i < root -> childNum.size(); i++) if (root -> child[root -> childNum[i]]) get(res, root -> child[root -> childNum[i]], word + rGetIndex(root -> childNum[i]));
    return;
}

void SmallTrie::deallocate(Node* &root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) deallocate(root -> child[i]);
    delete root;
    root = nullptr;
    return;
}
#include <fstream>
#include <Trie.hpp>

void Trie::remove(Node *&root, const std::string &word, int index)
{
    if (root == NULL) return;
    root->numWords--;
        
    if (index == word.length()) root->isEnd = false;
    else
    {
        int i = getIndex(word[index]);
        remove(root->child[i], word, index + 1);
    }
    
    if (root->numWords == 0)
    {
        delete root;
        root = NULL;
    }
}

void Trie::remove(const std::string &word)
{
    remove(root, word, 0);
}

#include <Libraries.hpp>
#include <DefTrie.hpp>

// int DefTrie::getIndex(char c)
// {
//     return c - 'a';
// }

// char DefTrie::rGetIndex(int index)
// {
//     return index + 'a';
// }
int DefTrie::getIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return -1;
}

char DefTrie::rGetIndex(int index) {
    if (index < 0 || index >= ALPHABET_SIZE) return '\0';
    return index + 'a';
}

void DefTrie::remove(Node *&root, const std::string &word, int index)
{
    // index initialized with 0, word's length = max index including root
    if (root == NULL) return;
    root->numWords--;
        
    if (index == word.length()) root -> isEnd = false;
    else
    {
        int i = getIndex(word[index]);
        remove(root -> child[i], word, index + 1);
    }
    
    if (root -> numWords == 0)
    {
        delete root;
        root = NULL;
    }
    return;
}
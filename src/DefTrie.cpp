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
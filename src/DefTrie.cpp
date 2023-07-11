#include <Libraries.hpp>
#include <DefTrie.hpp>
#include<Trie.hpp>

int DefTrie::getIndex(char c)
{
    if (c>='a'&&c<='z') return c-'a';
    if (c>='A'&&c<='Z') return c-'A';
    return -1;
}

char DefTrie::rGetIndex(int index)
{
    if(index<0||index>=ALPHABET_SIZE) return '\0';
    return index+'a';
}
#include "Trie.hpp"

int main()
{
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hi");
    trie.insert("hey");

    trie.save("test'\'output.bin");    
    
    return 0;
}
#include <Trie.hpp>
int Trie::getIndex(char c){
    if (c>='a'&&c<='z') return c-'a';
    if (c>='A'&&c<='Z') return c-'A';
    return -1;
}
bool Trie::checkExist(const std::string& key)
{
    Trie::Node* cur=root;
    int n=key.size();
   
}
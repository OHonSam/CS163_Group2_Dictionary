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

void DefTrie::insert(const std::string& word, const std::string& def){
    if(root==nullptr){
        root==new Node();
    }
    for(int i=0;i<def.size();++i){
        int index=getIndex(word[i]);
        if(root->child[index]==nullptr){
            root->child[index]=new Node;
            root->child[index]->numWords=1;
        }
        else{
            ++root->child[index]->numWords;
        }
        root->keywords.push_back(word);
        root=root->child[index];
    }
    root->isEnd=true;
        
}
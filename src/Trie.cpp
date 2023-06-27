#include <Trie.hpp>

void Trie::save(Node *node, std::ofstream &file)
{
    if(root==nullptr) return;
    file.write((char*)&root->numWords,sizeof(int));
    file.write((char*)&root->isEnd,sizeof(bool));
    for(int i=0;i<ALPHABET_SIZE;i++)
        if(root->child[i]!=nullptr)
        {
            char c=rGetIndex(i);
            file.write((char*)&c,sizeof(char));
            save(root->child[i],file);
        }
    char marker='\0';
    file.write((char*)&marker,sizeof(char));
}

bool Trie::save(const std::string &path)
{
    std::ofstream file(path,std::ios::binary);
    if(!file.is_open()) return false;
    save(root,file);
    file.close();
    return true;
}

#include <Trie.hpp>

void Trie::import(Node *&node, std::ifstream &file)
{
    if(root==nullptr) root=new Node;
    file.read((char*)&root->numWords,sizeof(int));
    file.read((char*)&root->isEnd,sizeof(bool));
    char c;
    while(1)
    {
        file.read((char*)&c,sizeof(char));
        if(c==TERMINATOR) break;
        int pos=getIndex(c);
        import(root->child[pos],file);
    }
}

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
    char marker=TERMINATOR;
    file.write((char*)&marker,sizeof(char));
}

bool Trie::import(const std::string &path)
{
    std::ifstream file(path,std::ios::binary);
    if(!file.is_open()) return false;
    import(root,file);
    file.close();
    return true;
}

bool Trie::save(const std::string &path)
{
    std::ofstream file(path,std::ios::binary);
    if(!file.is_open()) return false;
    save(root,file);
    file.close();
    return true;
}


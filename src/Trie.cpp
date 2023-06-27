#include <Trie.hpp>
int Trie::getIndex(char c){
    if (c>='a'&&c<='z') return c-'a';
    if (c>='A'&&c<='Z') return c-'A';
    return -1;
}
char Trie::rGetIndex(int index){
    if(index<0||index>=ALPHABET_SIZE) return '\0';
    return index+'a';
}


bool Trie::checkExist(const std::string& key)
{
    Trie::Node* cur=root;
    int n=key.size();
    for(int i=0;i<n;++i){
        int index=getIndex(key[i]);
        if(cur->child[index]==nullptr)
            return false;
        cur=cur->child[index];
    }
    return (cur->isEnd);
}



void Trie::recursiveFind(std::vector<std::string>& res,std::string prefix, Trie::Node* cur, int& cnt){
    if(cnt==20) 
        return;
    if(cur->isEnd==true) {
        res.push_back(prefix);
        ++cnt;
        return;
    }
    for(int i=0;i<ALPHABET_SIZE;++i){
        if(cur->child[i]!=nullptr){
            char c=rGetIndex(i);
            recursiveFind(res,prefix+c,cur->child[i],cnt);
        }
    }
}


#include <iostream>
#include <vector>
#include <string.h>
#include "..\include\HashTable.hpp"

std::string HashTable::searchDef(const std::string& word) {
    HashTable::numWords = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[HashTable::numWords].size(); i++)
    {
        if (buckets[HashTable::numWords][i].first == word) return buckets[HashTable::numWords][i].second;
    }
    return "";
}

int HashTable::insert(const std::string& word, const std::string& def) {
    return 0;
}

int HashTable::hash(const std::string& word) {
    int res=0;
    for(int i=0; i<NMOD; i++)
    {
        int tot=0;
        for(char c: word)
            tot=(1LL*tot*BASE%MOD[i]+c)%MOD[i];
        res=(res+1LL*i*tot%MOD[i])%MOD[i];
    }
    return res;
}

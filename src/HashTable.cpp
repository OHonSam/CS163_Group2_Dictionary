#include <HashTable.hpp>

std::string HashTable::searchDef(const std::string &word)
{
    numWords=hash(word);
    for (int i=0;i<buckets[numWords].size();i++)
        if (buckets[numWords][i].first==word) 
            return buckets[numWords][i].second;
    return "";
}

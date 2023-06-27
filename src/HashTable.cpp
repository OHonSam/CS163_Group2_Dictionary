#include <fstream>
#include <vector>
#include <string.h>
#include <HashTable.hpp>

HashTable::string searchDef(const string& word) {
    HashTable::numWords = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[HashTable::numWords].size(); i++)
    {
        if (buckets[HashTable::numWords][i].first == word) return buckets[HashTable::numWords][i].second;
    }
    return "";
}

HashTable::insert(const string& word, const string& def) {
    
}
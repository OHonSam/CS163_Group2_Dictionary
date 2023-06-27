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
    return 0;
}

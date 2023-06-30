#include <fstream>
#include <vector>
#include <string.h>
#include <HashTable.hpp>

std::string HashTable::searchDef(const std::string& word) {
    int key = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i].first == word) return HashTable::buckets[key][i].second;
    }
    return "";
}

int HashTable::insert(const std::string& word, const std::string& def) {
    int key = HashTable::hash(word);
    HashTable::buckets[key].push_back({word, def});
    return HashTable::buckets[key].size();
}

void HashTable::remove(const std::string &word)
{
    int h=hash(word);
    for(int i=0; i<buckets[h].size(); i++)
        if(buckets[h][i].first==word)
        {
            buckets[h].erase(buckets[h].begin()+i);
            return;
        }
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

HashTable::HashTable()
{
    buckets.resize(MOD[NMOD-1]);
}

void HashTable::updateDef(const std::string& word, const std::string& newDef) {
    int key = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i].first == word) {
            std::vector<std::pair<std::string, std::string>>::iterator it;
            it = HashTable::buckets[key].begin() + i;
            HashTable::buckets[key].erase(it);
            HashTable::buckets[key].push_back({word, newDef});
            return;
        }
    }
    return;
}

bool HashTable::import(const std::string& path) {

}				

bool HashTable::save(const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    out.open(path);
}

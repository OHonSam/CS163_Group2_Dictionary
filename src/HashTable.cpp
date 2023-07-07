#include <Libraries.hpp>
#include <HashTable.hpp>

Word* HashTable::searchDef(const std::string& word) {
    int key = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i] -> word == word) {
            return HashTable::buckets[key][i];
        }
    }
    // remember to check if a word exist on Trie
    Word* trash;
    return trash;
}

std::vector<Word*> HashTable::getRandom(int k)
{
    srand(time(NULL));
    std::vector<std::pair<std::string, std::string>> res;
    while(res.size()<k)
    {
        int num=rand()%numWords;
        int key=bit.lower_bound(num)-1;
        int pos=num-bit.get(key+1);
        if(pos<0 || pos>=buckets[key].size()) continue;
        bool flag=true;
        for(auto i: res)
            if(i.first==buckets[key][pos].first)
            {
                flag=false;
                break;
            }
        if(flag) res.push_back(buckets[key][pos]);
    }
    return res;
}

int HashTable::insert(Word* word) {
    numWords++;
    int key = HashTable::hash(word -> word);
    bit.add(key+1,1);
    HashTable::buckets[key].push_back(word);
    return key;
}

void HashTable::remove(const std::string &word)
{
    numWords--;
    int h=hash(word);
    for(int i=0; i<buckets[h].size(); i++)
        if(buckets[h][i].first==word)
        {
            delete buckets[h][i];
            buckets[h].erase(buckets[h].begin()+i);
            return;
        }
    return;
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

HashTable::HashTable():bit(MOD[NMOD-1])
{
    buckets.resize(MOD[NMOD-1]);
}

Word* HashTable::randomWordOfDay() {
    srand(time(NULL));
    int key=rand()%buckets.size();//random a bucket
    int pos=rand()%buckets[key].size();//randoma an index in that bucket
    return buckets[key][pos];
}
void HashTable::updateDef(const std::string& word, unsigned int type, const std::string& oldDef, const std::string& newDef) {
    int key = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i] -> word == word) {
            for(int i = 0; i < POS::Count; i++) {
                if(type & (1 << i)) {
                    for (int j = 0; j < buckets[key][i]->def[i].size(); j++) if (buckets[key][i]->def[i][j] == oldDef) buckets[key][i]->def[i][j] = newDef;
                }
                return;
            }
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

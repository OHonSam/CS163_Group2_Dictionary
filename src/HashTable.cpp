#include <Libraries.hpp>
#include <HashTable.hpp>

std::string HashTable::searchDef(const std::string& word) {
    int key = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i].first == word) return HashTable::buckets[key][i].second;
    }
    return "";
}

std::vector<std::pair<std::string, std::string>> HashTable::getRandom(int k)
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

int HashTable::insert(const std::string& word, const std::string& def) {
    numWords++;
    int key = HashTable::hash(word);
    bit.add(key+1,1);
    HashTable::buckets[key].push_back({word, def});
    return key;
}

void HashTable::remove(const std::string &word)
{
    numWords--;
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

HashTable::HashTable():bit(MOD[NMOD-1])
{
    buckets.resize(MOD[NMOD-1]);
}

std::pair<std::string, std::string> HashTable::randomWordOfDay() {
    srand(time(NULL));
    int key=rand()%buckets.size();//random a bucket
    int value=rand()%buckets[key].size();//randoma a pair in that bucket
    return buckets[key][value];
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

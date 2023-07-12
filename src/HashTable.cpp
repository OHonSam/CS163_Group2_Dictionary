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
    //srand(time(NULL));
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
    // if a word is already in the dictionary, do not insert it again
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

void initSeedForRandom(){
    srand(time(NULL));
}

std::pair<std::string, std::string> HashTable::randomWordOfDay() {
    //srand(time(NULL));
    int key=rand()%buckets.size();//random a bucket
    int pos=rand()%buckets[key].size();//randoma an index in that bucket
    return buckets[key][pos];
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
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in.is_open()) return false;
    int temp;
    int tempora;
    std::string w, d;
    in.read((char*)& temp, sizeof (int));
    buckets.resize(temp);
    for (int i = 0; i < buckets.size(); i++)
    {
        int tempo;
        in.read((char*)& tempo, sizeof (int));
        buckets[i].resize(tempo);
        for (int j = 0; j < tempo; j++)
        {
            int tempor;
            in.read((char*)& tempor, sizeof (int));
                size_t size;
                in.read((char*)&size, sizeof(size));
                w.resize(size);
                in.read(&w[0], size);
                in.read((char*)&size, sizeof(size));
                d.resize(size);
                in.read(&d[0], size);
                buckets[i][j] = {w, d};
        }
    }
    in.close();
    return true;
}				

bool HashTable::save(const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    int x = buckets.size();
    int tempo;
    out.write((char*)& x, sizeof (int));
    for (int i = 0; i < buckets.size(); i++)
    {
        int temp = buckets[i].size();
        out.write((char*)& temp, sizeof (int));
        for (int j = 0; j < temp; j++)
        {
            out.write((char*)& j, sizeof (int));
                size_t size = buckets[i][j].first.size();
                out.write((char*) &size,sizeof(size));
                out.write(&buckets[i][j].first[0],size);
                size = buckets[i][j].second.size();
                out.write((char*) &size,sizeof(size));
                out.write(&buckets[i][j].second[0],size);
        }
    }
    out.close();
    return true;
}
// please do not delete test code
// int main()
// {
//     HashTable hash;
//     hash.insert("father", "cha");
//     hash.insert("mother", "me");
//     hash.import("E:/HCMUS/cs163/CS163_Group2_Dictionary/src/txt.bin");
//     std::cout << hash.searchDef("father") << std::endl;
//     return 0;
// }

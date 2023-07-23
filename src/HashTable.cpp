#include <Libraries.hpp>
#include <HashTable.hpp>

Word* HashTable::searchDef(const std::string& word) {
    int key = HashTable::hash(word);
    Word* res=nullptr;
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i] -> word == word) {
            res = HashTable::buckets[key][i];
            break;
        }
    }
    // remember to check if a word exist on Trie
    return res;
}

std::vector<Word*> HashTable::getRandom(int k)
{
    srand(time(NULL));
    std::vector<Word*> res;
    while(res.size()<k)
    {
        int num=rand()%numWords;
        int key=bit.lower_bound(num)-1;
        int pos=num-bit.get(key+1);
        if(pos<0 || pos>=buckets[key].size()) continue;
        bool flag=true;
        for(auto i: res)
            if(i->word==buckets[key][pos]->word)
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
    // check if this word already exist
    int key = HashTable::hash(word->word);
    bit.add(key+1,1);
    HashTable::buckets[key].push_back(word);
    return key;
}

void HashTable::remove(const std::string &word)
{
    numWords--;
    int h=hash(word);
    for(int i=0; i<buckets[h].size(); i++)
<<<<<<<<< Temporary merge branch 1
        if(buckets[h][i]->word==word)
=========
        if(buckets[h][i].first==word)
>>>>>>>>> Temporary merge branch 2
        {
            delete buckets[h][i];
            buckets[h].erase(buckets[h].begin()+i);
            break;
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

HashTable::~HashTable()
{
    clear();
}

void HashTable::clear()
{
    for(int i = 0; i < buckets.size(); i++)
        for(int j = 0; j < buckets[i].size(); j++)
            delete buckets[i][j];
    buckets.clear();
    buckets.resize(MOD[NMOD-1]);
    bit.clear();
    numWords = 0;
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
            for(int j = 0; j < POS::Count; j++) {
                if (type & (1 << j)) {
                    for (int k = 0; k < buckets[key][i] -> def[j].size(); k++) if (buckets[key][i] -> def[j][k] == oldDef) {
                        buckets[key][i] -> def[j][k] = newDef;
                        break;
                    }
                }
                break;
            }
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

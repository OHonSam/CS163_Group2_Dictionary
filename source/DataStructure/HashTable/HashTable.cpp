#include <Libraries.hpp>
#include <HashTable.hpp>
#include<Word.hpp>

Word* HashTable::Merge(Word* &w1, Word* &w2) {
    if (w1 -> word == "") {
        w1 -> word += w2 -> word;
        w1 -> type += w2 -> type;
        // std::cout << w1 -> word;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < w2 -> def[i].size(); j++) {
                std::string s = w2 -> def[i][j];
                w1 -> def[i]. push_back(s);
            }
        }
    }
    else {
        for (int i = 0; i < 9; i++) {
            if (w2 -> def[i].size()) {
                if (w1 -> def[i].size()) {
                    for (int j = 0; j < w2 -> def[i].size(); j++) w1 -> def[i].push_back(w2 -> def[i][j]);
                }
                else {
                    w1 -> type += 1 << i;
                    for (int j = 0; j < w2 -> def[i].size(); j++) w1 -> def[i].push_back(w2 -> def[i][j]);
                }
            }
        }
    }
    return w1;
}

Word* HashTable::searchDef(const std::string& word) {
    int key = HashTable::hash(word);
    Word* res = new Word();
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        // std::cout << HashTable::buckets[key][i] -> word << '\n';
        if (HashTable::buckets[key][i] -> word == word) {
            res = Merge(res, HashTable::buckets[key][i]);
            delete buckets[key][i];
            buckets[key].erase(buckets[key].begin() + i);
            i--;
            // break;
        }
    }
    buckets[key].push_back(res);
    // remember to check if a word exist on Trie
    if (!res -> word.size()) return nullptr;
    return res;
}

std::vector<Word*> HashTable::getRandom(int k)
{
    //srand(time(NULL));
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
    int h = hash(word);
    for(int i = 0; i < buckets[h].size(); i++)
        if(buckets[h][i] -> word == word)
        {
            delete buckets[h][i];
            buckets[h].erase(buckets[h].begin()+i);
            i--;
            // break;
        }
    return;
}

int HashTable::hash(const std::string& word) {
    int res=0;
    std::string s = word;
    for(int i=0; i<NMOD; i++)
    {
        int tot=0;
        int a = word.size();
        for(int x = 0; x < word.size(); x++) {
            char c = word[x];
            tot=(1LL*tot*BASE%MOD[i]+c)%MOD[i];
        }
        res=(res+1LL*i*tot%MOD[i])%MOD[i];
    }
    return res;
}

HashTable::HashTable():bit(MOD[NMOD-1])
{
    srand(time(NULL));
    numWords=0;
    buckets.resize(MOD[NMOD-1]);
}

void HashTable::initSeedForRandom(){
    srand(time(NULL));
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
    int HTSize=buckets.size();//size of the hash table
    if(HTSize==0)
        return nullptr;

    int key=rand()%HTSize;//random a bucket
    int entrySize=buckets[key].size();//size of that bucket
    while(entrySize==0){
        key=rand()%HTSize;
        entrySize=buckets[key].size();
    }
    int pos=rand()%entrySize;//random an index in that bucket
    return buckets[key][pos];
}



Word* HashTable::updateDef(const std::string& word, unsigned int type, const std::string& oldDef, const std::string& newDef) {
    int key = HashTable::hash(word);
    for (int i = 0; i < HashTable::buckets[key].size(); i++)
    {
        if (HashTable::buckets[key][i] -> word == word) {
            for(int j = 0; j < POS::Count; j++) {
                // type is the type of oldDef 
                if (type & (1 << j)) {
                    for (int k = 0; k < buckets[key][i] -> def[j].size(); k++) if (buckets[key][i] -> def[j][k] == oldDef) {
                        buckets[key][i] -> def[j][k] = newDef;
                        return buckets[key][i];
                    }
                }
            }
        }
    }
    return nullptr;
}

bool HashTable::import(const std::string& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in.good() || !in.is_open()) return false;
    int temp;
    int tempora;
    std::string w;
    int numW;
    in.read((char*)& numW, sizeof (int));
    HashTable::numWords = numW;
    in.read((char*)& temp, sizeof (int));
    buckets.resize(temp);
    for (int i = 0; i < buckets.size(); i++)
    {
        int tempo;
        in.read((char*)& tempo, sizeof (int));
        buckets[i].resize(tempo);
        bit.add(i+1, tempo);
        for (int j = 0; j < tempo; j++)
        {
            int tempor;
            in.read((char*)& tempor, sizeof (int));
                size_t size;
                in.read((char*)&size, sizeof(size));
                w.resize(size);
                in.read(&w[0], size);
                unsigned int type;
                in.read((char*) &type, sizeof (unsigned int));
                Word* word = new Word(w, type);
                for(int k = 0; k < POS::Count; k++) {
                    if ((int) (word -> type) & (1 << k)) {
                        in.read((char*) &tempora, sizeof (int));
                        int temporar;
                        in.read((char*) &temporar, sizeof (int));
                        word -> def[k].resize(temporar);
                        for (int l = 0; l < temporar; l++) {
                            in.read((char*)&size, sizeof(size));
                            word -> def[k][l].resize(size);
                            in.read(&word -> def[k][l][0], size);
                        }
                    }
                }
                buckets[i][j] = word;
        }
    }
    in.close();
    return true;
}				

bool HashTable::save(const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    int numW = HashTable::numWords;
    out.write((char*)& numW, sizeof (int));
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
                size_t size = buckets[i][j] -> word.size();
                out.write((char*) &size,sizeof(size));
                out.write(&buckets[i][j] -> word[0],size);
                out.write((char*) &buckets[i][j] -> type, sizeof (unsigned int));
                for(int k = 0; k < POS::Count; k++) {
                    if ((buckets[i][j] -> type) & (1 << k)) {
                        out.write((char*) &k, sizeof (int));
                        int sizedef = buckets[i][j] -> def[k].size();
                        out.write((char*) &sizedef, sizeof (int));
                        for (int l = 0; l < sizedef; l++) {
                            size = buckets[i][j] -> def[k][l].size();
                            out.write((char*) &size,sizeof(size));
                            out.write(&buckets[i][j] -> def[k][l][0], size);
                        }
                    }
                }
        }
    }
    out.close();
    // HashTable::clear();
    return true;
}
// please do not delete test code
// int main()
// {
//     HashTable hash;
    // Word* w1 = new Word("father", 1, "cha");
    // hash.insert(w1);
    // Word* w2 = new Word("mother", 13, "me");
    // hash.insert(w2);
    // hash.save("D:/cs163/CS163_Group2_Dictionary/ASSETS/DataStructure/default/HashTable.bin");
//     hash.import("D:/cs163/CS163_Group2_Dictionary/ASSETS/DataStructure/default/HashTable.bin");
//     Word* w = hash.searchDef("father");
//     std::cout << w -> type <<  w -> def[0][0] << '\n';
//     w = hash.searchDef("mother");
//     std::cout << w -> def[3][0] << '\n';
//     return 0;
// }

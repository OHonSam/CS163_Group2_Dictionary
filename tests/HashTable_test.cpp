#include <gtest/gtest.h>
#include "HashTable.hpp"
using namespace std;

const int N=8;
const string word[N]{
    "hello",
    "world",
    "fantastic",
    "dramatically",
    "I",
    "in",
    "the",
    "a"
};
const int type[N]{
    POS::Verb,
    POS::Noun,
    POS::Adjective,
    POS::Adverb,
    POS::Pronoun,
    POS::Preposition,
    POS::Conjunction,
    POS::Interjection
};
const string def[N]{
    "xin chao",
    "the gioi",
    "tuyet voi",
    "mot cach nhanh chong",
    "toi",
    "trong",
    "the",
    "mot"
};
const string newDef[N]
{
    "xin chao moi nguoi",
    "the gioi cua chung ta",
    "tuyet voi qua",
    "mot cach nhanh chong va hieu qua",
    "toi la ai",
    "trong nha",
    "the nao",
    "mot con meo"
};

void input(HashTable& ht)
{
    for(int i=0; i<N; i++)
        ht.insert(new Word(word[i], type[i], def[i]));
}

TEST(HashTable_test, searchDef)
{
    HashTable ht;
    input(ht);

    Word* w=0;
    for(int i=0; i<N; i++)
    {
        w = ht.searchDef(word[i]);
        ASSERT_TRUE(w != 0);
        EXPECT_EQ(w->def[POS::getIndex(type[i])][0], def[i]);
    }
}

TEST(HashTable_test, remove)
{
    HashTable ht;
    input(ht);

    for(int i=0; i<N; i++)
    {
        ht.remove(word[i]);
        EXPECT_EQ(ht.searchDef(word[i]), (Word*)0);
    }
}

TEST(HashTable_test, randomWordOfDay)
{
    HashTable ht;
    input(ht);

    Word* w=ht.randomWordOfDay();
    ASSERT_TRUE(w != 0);
    for(int i=0; i<N; i++)
        if(
            w->word == word[i] && 
            w->type == type[i] && 
            w->def[POS::getIndex(type[i])][0] == def[i]
        ) return;
    FAIL();
}

TEST(HashTable_test, updateDef)
{
    HashTable ht;
    input(ht);

    for(int i=0; i<N; i++)
    {
        ht.updateDef(word[i], type[i], def[i], newDef[i]);
        Word* w=ht.searchDef(word[i]);
        ASSERT_TRUE(w != 0);
        EXPECT_EQ(w->def[POS::getIndex(type[i])][0], newDef[i]);
    }
}

TEST(HashTable_test, getRandom)
{
    HashTable ht;
    input(ht);

    int n=rand()%N+1;
    vector<Word*> v=ht.getRandom(n);
    ASSERT_EQ(v.size(), n);
    for(int i=0; i<n; i++)
    {
        ASSERT_TRUE(v[i] != 0);
        bool ok=false;
        for(int j=0; j<N; j++)
            if(
                v[i]->word == word[j] && 
                v[i]->type == type[j] && 
                v[i]->def[POS::getIndex(type[j])][0] == def[j]
            ){ok=true; break;}
        EXPECT_TRUE(ok);
    }
}

TEST(HashTable_test, ImportAndSave)
{
    HashTable ht;
    input(ht);

    ASSERT_TRUE(ht.save("HashTable.bin"));
    ht.clear();
    EXPECT_EQ(ht.searchDef(word[0]), (Word*)0);

    ASSERT_TRUE(ht.import("HashTable.bin"));
    Word* w=0;
    for(int i=0; i<N; i++)
    {
        w = ht.searchDef(word[i]);
        ASSERT_TRUE(w != 0);
        EXPECT_EQ(w->def[POS::getIndex(type[i])][0], def[i]);
    }
}
#include <gtest/gtest.h>
#include <Dict.hpp>
using namespace std;

const vector<string> words={
    "aback",
    "abator",
    "mort",
    "mortify",
    "pew"
};

const vector<unsigned int> type={
    POS::Adverb,
    POS::Noun,
    POS::Noun,
    POS::Verb,
    POS::Noun
};

const vector<string> def={
    "Toward the back or rear; backward.",
    "One who abates a nuisance.",
    "A great quantity or number.",
    "To destroy the organic texture and vital functions of; to produce gangrene in.",
    "One of the compartments in a church which are separated by low partitions  and have long seats upon which several persons may sit; -- sometimes called slip. Pews were originally made square but are now usually long and narrow."
};

TEST(Dict_test, ReadCsvAndSearch)
{
    Dict dict;

    for(int i=0;i<words.size();++i)
    {
        Word* w=dict.searchDef(words[i]);
        ASSERT_TRUE(w!=nullptr);
        EXPECT_TRUE(w->word==words[i]);
        ASSERT_FALSE(w->def[POS::getIndex(type[i])].empty());
        EXPECT_TRUE(w->def[POS::getIndex(type[i])][0]==def[i]);
    }
}

TEST(Dict_test, addWord)
{
    Dict dict;
    Word* w=new Word("abc",POS::Noun,"abc_def");
    EXPECT_TRUE(dict.searchDef("abc")==nullptr);
    dict.addWord(w);
    Word* res=dict.searchDef("abc");
    ASSERT_TRUE(res!=nullptr);
    EXPECT_TRUE(res->word=="abc");
    ASSERT_FALSE(res->def[POS::getIndex(POS::Noun)].empty());
    EXPECT_TRUE(res->def[POS::getIndex(POS::Noun)][0]=="abc_def");
    delete w;
}
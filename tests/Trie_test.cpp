#include <gtest/gtest.h>
#include "Trie.hpp"
using namespace std;

const int N=8;
const string word[N]{
    "hello",
    "world",
    "fantastic",
    "dramatically",
    "wonderful",
    "in",
    "the",
    "a"
};

void input(Trie& trie)
{
    for(int i=0; i<N; i++)
        trie.insert(word[i]);
}

TEST(Trie_test, insert)
{
    Trie trie;
    input(trie);

    for(int i=0; i<N; i++)
        EXPECT_TRUE(trie.checkExist(word[i]));
}

TEST(Trie_test, remove)
{
    Trie trie;
    input(trie);

    for(int i=0; i<N; i++)
    {
        trie.remove(word[i]);
        EXPECT_FALSE(trie.checkExist(word[i]));
    }
}

TEST(Trie_test, searchPrefix)
{
    Trie trie;
    input(trie);

    vector<string> prefix=trie.searchPrefix("a");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "a");

    prefix=trie.searchPrefix("dra");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "dramatically");

    prefix=trie.searchPrefix("he");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "hello");

    prefix=trie.searchPrefix("w");
    EXPECT_EQ(prefix.size(), 2);
    EXPECT_EQ(prefix[0], "wonderful");
    EXPECT_EQ(prefix[1], "world");

    prefix=trie.searchPrefix("fa");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "fantastic");

    prefix=trie.searchPrefix("i");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "in");

    prefix=trie.searchPrefix("t");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "the");

    prefix=trie.searchPrefix("z");
    EXPECT_EQ(prefix.size(), 0);

    prefix=trie.searchPrefix("");
    EXPECT_EQ(prefix.size(), N);
}

TEST(Trie_test, ImportAndSave)
{
    Trie trie;
    input(trie);

    ASSERT_TRUE(trie.save("trie.bin"));
    trie.clear();
    EXPECT_FALSE(trie.checkExist(word[0]));

    ASSERT_TRUE(trie.import("trie.bin"));
    for(int i=0; i<N; i++)
        EXPECT_TRUE(trie.checkExist(word[i]));
}
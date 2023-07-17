#include <gtest/gtest.h>
#include "TST.hpp"
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

void input(TST& tst)
{
    for(int i=0; i<N; ++i)
        tst.insert(word[i]);
}

TEST(TST_test, insert)
{
    TST tst;
    input(tst);

    for(int i=0; i<N; ++i)
        EXPECT_TRUE(tst.wordExists(word[i]));
}

TEST(TST_test, remove)
{
    TST tst;
    input(tst);

    for(int i=0; i<N; ++i)
    {
        tst.remove(word[i]);
        EXPECT_FALSE(tst.wordExists(word[i]));
    }
}

TEST(TST_test, searchPrefix)
{
    TST tst;
    input(tst);

    vector<string> prefix=tst.searchPrefix("a");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "a");

    prefix=tst.searchPrefix("dra");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "dramatically");

    prefix=tst.searchPrefix("he");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "hello");

    prefix=tst.searchPrefix("w");
    EXPECT_EQ(prefix.size(), 2);
    EXPECT_EQ(prefix[0], "wonderful");
    EXPECT_EQ(prefix[1], "world");

    prefix=tst.searchPrefix("fa");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "fantastic");

    prefix=tst.searchPrefix("i");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "in");

    prefix=tst.searchPrefix("t");
    EXPECT_EQ(prefix.size(), 1);
    EXPECT_EQ(prefix[0], "the");

    prefix=tst.searchPrefix("z");
    EXPECT_EQ(prefix.size(), 0);

    prefix=tst.searchPrefix("");
    EXPECT_EQ(prefix.size(), N);
}

// TEST(TST_test, ImportAndSave)
// {
//     TST tst;
//     input(tst);

//     ASSERT_TRUE(tst.save("tst.bin"));
//     tst.clear();
//     EXPECT_FALSE(tst.wordExists(word[0]));

//     ASSERT_TRUE(tst.import("tst.bin"));
//     for(int i=0; i<N; ++i)
//         EXPECT_TRUE(tst.wordExists(word[i]));
// }
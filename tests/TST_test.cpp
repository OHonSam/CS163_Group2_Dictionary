#include <gtest/gtest.h>
#include "TST.hpp"
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

TEST(TST_test, push)
{
    TST tst;
    for(int i=0; i<N; i++)
        tst.insert(word[i]);
    for(int i=0; i<N; i++)
        EXPECT_TRUE(tst.wordExists(word[i]));
}

TEST(TST_test, pop)
{
    TST tst;
    for(int i=0; i<N; i++)
    {
        tst.insert(word[i]);
        EXPECT_TRUE(tst.wordExists(word[i]));
    }

    for(int i=0; i<N; i++)
    {
        tst.deletion(word[i]);
        EXPECT_FALSE(tst.wordExists(word[i]));
    }
}

TEST(TST_test, ImportAndSave)
{
    TST tst;
    for(int i=0; i<N; i++)
        tst.insert(word[i]);

    ASSERT_TRUE(tst.save("TST.bin"));

    // for(int i=0; i<N; i++)
    //     EXPECT_FALSE(tst.wordExists(word[i]));

    ASSERT_TRUE(tst.import("TST.bin"));
    for(int i=0; i<N; i++)
        EXPECT_TRUE(tst.wordExists(word[i]));
}
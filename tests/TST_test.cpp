#include <gtest/gtest.h>
#include "TST.hpp"
using namespace std;

const int N = 10;
const string word[N]{
    "a",
    "hello",
    "fantastic",
    "dramatically",
    "I",
    "in",
    "the",
    "world",
    "wonderful",
    "wow"};

void input(TST &tst)
{
    for (int i = 0; i < N; ++i)
        tst.insert(word[i]);
}

TEST(TST_test, push)
{
    TST tst;
    input(tst);
    for(int i=0; i<N; ++i)
        EXPECT_TRUE(tst.wordExists(word[i]));
}

TEST(TST_test, pop)
{
    TST tst;
    for(int i=0; i<N; ++i)
    {
        tst.insert(word[i]);
        EXPECT_TRUE(tst.wordExists(word[i]));
    }

    for(int i=0; i<N; ++i)
    {
        tst.remove(word[i]);
        EXPECT_FALSE(tst.wordExists(word[i]));
    }
}

TEST(TST_test, getList)
{
    TST tst;
    input(tst);
    vector<string> v=tst.traverse();
    EXPECT_EQ(v.size(), N);
    for(const string& s: v)
    {
        bool flag=false;
        for(int i=0; i<N; ++i)
            if(s==word[i])
            {
                flag=true;
                break;
            }
        EXPECT_TRUE(flag);
    }
}

namespace testing
{

    // Returns an AssertionResult object to indicate that an assertion has
    // succeeded.
    AssertionResult AssertionSuccess();

    // Returns an AssertionResult object to indicate that an assertion has
    // failed.
    AssertionResult AssertionFailure();

}

testing::AssertionResult sameSiz(int n, int n2)
{
    if (n == n2)
        return testing::AssertionSuccess();
    else
        return testing::AssertionFailure() << n;
}

TEST(TST_test, startWith)
{
    TST tst;
    input(tst);
    vector<string> prefix;

    prefix=tst.startWith("a");
    // EXPECT_EQ(prefix.size(), 1);
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "a");

    prefix=tst.startWith("dra");
    // EXPECT_EQ(prefix.size(), 1);
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "dramatically");

    prefix=tst.startWith("he");
    // EXPECT_EQ(prefix.size(), 1);
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "hello");

    prefix=tst.startWith("fa");
    // EXPECT_EQ(prefix.size(), 1);
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "fantastic");

    prefix = tst.startWith("i");
    // EXPECT_EQ(prefix.size(), 2);
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "in");

prefix = tst.startWith("I");
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "I");


    prefix = tst.startWith("w");
    // ASSERT_EQ(prefix.size(), 2);
    EXPECT_TRUE(sameSiz(prefix.size(), 3));
    EXPECT_EQ(prefix[0], "wonderful");
    EXPECT_EQ(prefix[1], "world");
    EXPECT_EQ(prefix[2], "wow");

    prefix=tst.startWith("t");
    // EXPECT_EQ(prefix.size(), 1);
    EXPECT_TRUE(sameSiz(prefix.size(), 1));
    EXPECT_EQ(prefix[0], "the");

    prefix=tst.startWith("z");
    // EXPECT_EQ(prefix.size(), 0);
    EXPECT_TRUE(sameSiz(prefix.size(), 0));

    prefix = tst.traverse();
    EXPECT_EQ(prefix.size(), N);
}

TEST(TST_test, ImportAndSave)
{
    TST tst;
    input(tst);

    ASSERT_TRUE(tst.save("TST.bin"));

    tst.clear();

    for(int i=0; i<N; ++i)
        EXPECT_FALSE(tst.wordExists(word[i]));

    ASSERT_TRUE(tst.import("TST.bin"));
    for(int i=0; i<N; ++i)
        EXPECT_TRUE(tst.wordExists(word[i]));
}
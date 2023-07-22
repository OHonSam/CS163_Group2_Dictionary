// #include <gtest/gtest.h>
// #include "SLL.hpp"
// using namespace std;

// const int N=8;
// const string word[N]{
//     "hello",
//     "world",
//     "fantastic",
//     "dramatically",
//     "I",
//     "in",
//     "the",
//     "a"
// };

// // TEST(SLL_test, push)
// // {
// //     SLL<string> sll;
// //     for(int i=0; i<N; i++)
// //         sll.push(word[i]);
// //     for(int i=0; i<N; i++)
// //         EXPECT_TRUE(sll.find(word[i]));
// // }

// TEST(SLL_test, pop)
// {
//     SLL<string> sll;
//     for(int i=0; i<N; i++)
//         sll.push(word[i]);
//     for(int i=0; i<N; i++)
//         sll.pop(word[i]);
//     for(int i=0; i<N; i++)
//         EXPECT_FALSE(sll.find(word[i]));
// }

// TEST(SLL_test, clearSLL)
// {
//     SLL<string> sll;
//     for(int i=0; i<N; i++)
//         sll.push(word[i]);
//     sll.clearSLL();
//     for(int i=0; i<N; i++)
//         EXPECT_FALSE(sll.find(word[i]));
// }

// TEST(SLL_test, ImportAndSave)
// {
//     SLL<string> sll;
//     for(int i=0; i<N; i++)
//         sll.push(word[i]);
//     ASSERT_TRUE(sll.saveSLLStr("SLL.bin"));
//     sll.clearSLL();
//     EXPECT_FALSE(sll.find(word[0]));

    
//     ASSERT_TRUE(sll.importSLLStr("SLL.bin"));
//     for(int i=0; i<N; i++)
//         EXPECT_TRUE(sll.find(word[i]));
//     ASSERT_TRUE(sll.clearHistory("SLL.bin"));
// }
// const int M=14;
// const string word2[M]{
//     "privilege",
//     "mitigate",
//     "love",
//     "hate",
//     "anticipate",
//     "majestic",
//     "breathtaking",
//     "wonderful",
//     "picturesque",
//     "champion",
//     "legendary",
//     "meditation",
//     "examination",
//     "exaggeration"
// };
// TEST(SLL_test, SLLintoVector){
//     SLL<string> sll;
//     for(int i=0; i<N; i++)
//         sll.push(word[i]);
//     for(int i=0;i<M;i++)
//         sll.push(word2[i]);
//     EXPECT_EQ(sll.SLLintoVector().size(),20);
// }

// #include <App.hpp>
// using namespace std;

// int main()
// {
//     App app;
//     app.run();
// //    Dict dict;
//     return 0;
// }

#include "../source/DataStructure/TST/TST.hpp"
#include "../Libraries.hpp"
// #include "../source/DataStructure/Trie/Trie.hpp"

int main()
{
    TST tst;
    tst.insert("hello");

    tst.save("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/tst/tst.txt");
    std::cerr << "nice\n";

    std::vector<std::string> v=tst.traverse();
    for(const std::string& s: v)
        std::cout<<s<<'\n';

    // tst.import("test.bin");
    tst.clear();
    std::cerr << "Tree: " << tst.treeExists() << '\n';
    // std::cerr << "abcxyz\n";
    tst.import("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/TST/tst.txt");
    // std::cerr << "out import\n";
    // std::vector<std::string> v = tst.traverse();
    std::cerr << "after import: " << tst.treeExists() << '\n';

    // tst.test();
    v = tst.traverse();
    for (const std::string &s : v)
    {
        std::cerr << "in traverse\n";
        std::cout << s << std::endl;
    }

    std::cerr << "end\n";

    return 0;
}


// int main()
// {
//     Trie trie;
//     trie.insert("hello");

//     trie.save("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/trie/trie.txt");
//     std::cerr << "nice\n";

//     // trie.import("test.bin");
//     trie.clear();
//     trie.import("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/trie/trie.txt");
//     // std::cerr << "out import\n";
//     // std::vector<std::string> v = trie.traverse();
//     // std::cerr << "after import: " << trie.treeExists() << '\n';

//     std::cerr << "end\n";

//     return 0;
// }
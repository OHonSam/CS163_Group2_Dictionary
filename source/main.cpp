// #include <App.hpp>
// using namespace std;

// int main()
// {
//     App app;
//     app.run();
//     return 0;
// }

// #include "../source/DataStructure/trie/trie.hpp"
#include "../Libraries.hpp"
#include "../source/DataStructure/Trie/Trie.hpp"

// int main()
// {
//     trie trie;
//     trie.insert("hello");

//     trie.saveTXT("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/trie/trie.txt");
//     std::cerr << "nice\n";

//     std::vector<std::string> v=trie.traverse();
//     for(const std::string& s: v)
//         std::cout<<s<<'\n';

//     // trie.import("test.bin");
//     trie.clear();
//     std::cerr << "Tree: " << trie.treeExists();
//     trie.importTXT("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/trie/trie.txt");
//     // std::cerr << "out import\n";
//     // std::vector<std::string> v = trie.traverse();
//     std::cerr << "after import: " << trie.treeExists() << '\n';
//     v = trie.traverse();
//     for (const std::string &s : v)
//     {
//         std::cout << s << std::endl;
//     }

//     std::cerr << "end\n";

//     return 0;
// }


int main()
{
    Trie trie;
    trie.insert("hello");

    trie.save("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/trie/trie.txt");
    std::cerr << "nice\n";

    // trie.import("test.bin");
    trie.clear();
    trie.import("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/trie/trie.txt");
    // std::cerr << "out import\n";
    // std::vector<std::string> v = trie.traverse();
    // std::cerr << "after import: " << trie.treeExists() << '\n';

    std::cerr << "end\n";

    return 0;
}
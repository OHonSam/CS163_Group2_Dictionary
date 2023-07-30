// #include <App.hpp>
// using namespace std;

// int main()
// {
//     App app;
//     app.run();
//     return 0;
// }

#include "../source/DataStructure/TST/TST.hpp"
#include "../Libraries.hpp"

int main()
{
    TST tst;
    tst.insert("he");

    tst.save("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/TST/TST.bin");
    std::cerr << "nice\n";

    // std::vector<std::string> v=tst.traverse();
    // for(const std::string& s: v)
    //     std::cout<<s<<std::endl;

    // tst.import("test.bin");
    tst.clear();
    std::cerr << "Tree: " << tst.treeExists();
    tst.import("C:/Users/huynh/OneDrive - VNU-HCMUS/KHTN (do not delete)/Year 1/Semester 3/CS163 Data structure/lab project cs163/CS163_Group2_Dictionary/source/DataStructure/TST/TST.bin");

    std::vector<std::string> v=tst.traverse();
    for(const std::string& s: v)
        std::cout<<s<<std::endl;

    return 0;
}
#include<Libraries.hpp>
#include<SLL.hpp>
#include<Trie.hpp>
std::ifstream fin;
std::ofstream fout;
int main()
{
    SLL<std::string> history;
    history.push("Hello");
    history.push("Hi");
    history.push("Bonjour");
    history.push("Konichiwa");
    history.push("Nihao");
    history.push("Ola");
    history.push("Sawasdee");
    history.push("Marhaba");
    history.push("Aloha");
    history.push("a");
    history.push("b");
    history.push("c");
    history.push("d");
    history.push("e");
    history.push("f");
    history.push("g");
    history.push("h");
    history.push("i");
    history.push("k");
    history.push("l");
    history.push("m");
    history.push("n");

    history.display();
    std::cout<<std::endl;

    history.pop("Bonjour");

   
    history.display();
     std::cout << std::endl;

    history.saveSLLStr("HistorySLL.bin",fout);
    SLL<std::string> historyFFile;
    historyFFile.importSLLStr("HistorySLL.bin",fin);
    std::cout << std::endl;
    historyFFile.display();

    history.clearHistory();
    history.display();
}
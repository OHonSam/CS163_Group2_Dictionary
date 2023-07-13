#include<Libraries.hpp>
//#include<DefTrie.hpp>
#include<Trie.hpp>
#include<HashTable.hpp>
#include<Word.hpp>
using namespace std;
int main(){
    Word* word = new Word();
    std::cout << POS::getType("Noun") << std::endl;
    std::cout << POS::getType("Adjective") << std::endl;
    std::cout << POS::getType("Interjection") << std::endl;
    std::cout << POS::getTypeString(0) << std::endl;
    std::cout << POS::getTypeString(1) << std::endl;
    std::cout << POS::getTypeString(7) << std::endl;
    word->word = "hello";
    word->def[0].push_back("xin chao");
    word->def[1].push_back("chao");
    word->def[7].push_back("thu hut");
    HashTable h;
    h.insert(word);
    h.displayDef(word->word);
    //HashTable h.insert()

}

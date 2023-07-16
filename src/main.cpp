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

    word->word = "hello";
    word->def[0].push_back("xin chao");
    word->def[0].push_back("loi chao");
    word->def[0].push_back("loi chao hoi");
    word->def[1].push_back("chao");
    word->def[1].push_back("chao hoi");
    word->def[7].push_back("thu hut");
    std::cout<<POS::getTypeString(POS::getType(word->def[0][0]));
    HashTable h;
    h.insert(word);
    h.displayDef(word->word);
    //HashTable h.insert()

}

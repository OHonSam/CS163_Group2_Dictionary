#include <App.hpp>
using namespace std;

int main()
{
    Dict* dict;
    // Dict* dict = new Dict();
    Word* word = new Word();
    word->word = "hello";
    word->def[0].push_back("xin chao ban rat dep");
    word->def[1].push_back("chao");
    word->def[7].push_back("thu hut");
    word->type = 131;
    Word* word1 = new Word();
    word1->word = "hellu";
    word1->def[0].push_back("chao chao");
    word1->def[1].push_back("xin dep");
    word1->def[7].push_back("i love you");
    word1->type = 131;
    // dict -> defTrie -> insert(word);
    // dict -> defTrie -> insert(word1);
    // dict -> wordDef.insert(word);
    // dict -> wordDef.insert(word1);
    // std::vector <std::string> test;
    // test = dict -> defTrie -> searchKeyWord("thu hut");
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // Word* testword = dict -> wordDef.searchDef("hello");
    // for (int i = 0; i < 9; i++) {
    //     if (!(testword -> def[i].empty())) std::cout << testword -> def[i][0] << '\n';
    // }
    // std::cout << "no add wword";
    dict ->addWord(word);
    dict ->addWord(word1);
    std::cout << "add word 1 success";
    // Dict* dict = new Dict();
    Word* word2 = dict -> searchForDef("hello");
    if (!word2) {
        std::cout << "no word";
    //     dict -> ~Dict();
        return 0;
    }
    for (int i = 0; i < 9; i++) {
        if (!(word2 -> def[i].empty())) std::cout << word2 -> def[i][0] << '\n';
    }
    // dict -> ~Dict();
    // App* app = new App();
    // app -> run();
    return 0;
}
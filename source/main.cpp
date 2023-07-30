#include <App.hpp>
using namespace std;

int main()
{
    Dict* dict = new Dict();
    Word* word = dict -> searchForDef("hello");
    if (!word) {
        std::cout << "no word";
        dict -> ~Dict();
        return 0;
    }
    for (int i = 0; i < 9; i++) {
        if (!(word -> def[i].empty())) std::cout << word -> def[i][0] << '\n';
    }
    dict -> ~Dict();
    // App* app = new App();
    // app -> run();
    return 0;
}
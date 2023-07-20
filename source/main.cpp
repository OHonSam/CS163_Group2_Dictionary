#include <App.hpp>

int main()
{
    Dict dict;
    Word* w=dict.searchDef("aback");
    std::cout<<w->word<<std::endl;
    return 0;
}
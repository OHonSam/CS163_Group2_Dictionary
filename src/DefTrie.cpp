#include <Libraries.hpp>
#include <DefTrie.hpp>

int DefTrie::getIndex(char c)
{
    return c - 'a';
}

char DefTrie::rGetIndex(int index)
{
    return index + 'a';
}
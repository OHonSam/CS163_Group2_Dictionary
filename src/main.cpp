#include "HashTable.hpp"
#include <iostream>
using namespace std;

int main()
{
    HashTable ht;
    ht.insert("hello", "xin chao");
    ht.insert("world", "the gioi");
    ht.insert("goodbye", "tam biet");
    ht.insert("goodnight", "chuc ngu ngon");
    ht.insert("goodmorning", "chao buoi sang");
    ht.insert("goodafternoon", "chao buoi chieu");
    ht.insert("goodevening", "chao buoi toi");

    vector<pair<string, string>> res = ht.getRandom(3);
    for (auto i : res)
    {
        cout << i.first << " " << i.second << endl;
    }
    return 0;
}
#include "HashTable.hpp"
#include <iostream>
using namespace std;

int main()
{
    // BIT bit(1000000);
    // bit.add(233039, 1);
    // bit.add(298729, 1);
    // bit.add(322780, 1);
    // bit.add(359267, 1);

    // cout<<bit.lower_bound(4)<<endl;

    HashTable ht;
    cout << ht.insert("hello", "xin chao") << endl;
    cout << ht.insert("world", "the gioi") << endl;
    cout << ht.insert("goodbye", "tam biet") << endl;
    cout << ht.insert("goodnight", "chuc ngu ngon") << endl;
    cout << ht.insert("goodmorning", "chao buoi sang") << endl;
    cout << ht.insert("goodafternoon", "chao buoi chieu") << endl;
    cout << ht.insert("goodevening", "chao buoi toi") << endl;

    vector<pair<string, string>> res = ht.getRandom(3);
    for (auto i : res)
    {
        cout << i.first << " " << i.second << endl;
    }
    return 0;
}

// 233038
// 298728
// 322780
// 359266
// 515414
// 532094
// 993559
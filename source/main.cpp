#include <App.hpp>
using namespace std;

int main()
{
    // App app;
    // app.run();
    Dict dict;
    vector<string> v=dict.searchForWord("The act of abacinating.");
    cout << v.size() << '\n';
    for (int i=0;i<v.size();i++)
        cout<<v[i]<<endl;
    return 0;
}
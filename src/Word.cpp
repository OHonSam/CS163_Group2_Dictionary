#include "Word.hpp"

Word::Word()
{
    word = "";
    type = 0;
}

Word::Word(const std::string &word)
{
    this->word = word;
    type = 0;
}

Word::Word(const std::string &word, unsigned int type)
{
    this->word = word;
    this->type = type;
}

Word::Word(const std::string &word, unsigned int type, const std::string &def)
{
    this->word = word;
    this->type = type;
    for(int i=0; i<POS::Count; i++)
        if(type&(1<<i))
            this->def[i].push_back(def);
}

unsigned int POS::getType(const std::string &str)
{
    int res=0;
    for(int i=0; i<Count; i++)
    {
        bool flag=false;
        for(int j=0; j+TypeShort[i].size()-1<str.size(); j++)
            if(str.substr(j,TypeShort[i].size())==TypeShort[i])
            {
                flag=true;
                break;
            }
        if(flag) res|=1<<i;
    }
    if(!res) res=Other;
    return res;
}

std::string POS::getTypeString(unsigned int type)
{
    std::string str = "";
    for(int i=0; i<Count; i++)
        if(type&(1<<i))
        {
            str += TypeString[i];
            str += ", ";
        }
    if(!str.empty())
    {
        str.pop_back();
        str.pop_back();
    }
    return str;
}

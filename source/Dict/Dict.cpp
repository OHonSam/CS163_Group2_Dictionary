#include <Dict.hpp>

bool Dict::reset(){
    words.clear();
    wordDef.clear();
    favList.clear();
    history.clearSLL();
    if(
        !words.import(DEFAULT::WORDS) ||
        !wordDef.import(DEFAULT::WORDDEF) ||
        !favList.import(DEFAULT::FAVLIST) ||
        !history.importSLLStr(DEFAULT::HISTORY)
    )
        return false;
    return true;
}

Dict::Dict(bool firstInit)
{
    if(firstInit)
        importEECsv(RAW_DATA::EE);
    else
    {
        words.import(MAIN::WORDS);
        wordDef.import(MAIN::WORDDEF);
        favList.import(MAIN::FAVLIST);
        history.importSLLStr(MAIN::HISTORY);
    }
}

Dict::~Dict()
{
    words.save(MAIN::WORDS);
    wordDef.save(MAIN::WORDDEF);
    favList.save(MAIN::FAVLIST);
    history.saveSLLStr(MAIN::HISTORY);
}

bool Dict::importEECsv(const std::string &path)
{
    std::ifstream in(path);
    std::string line;
    std::getline(in,line);

    while(!in.eof())
    {
        std::string word, len, POS, def;
        std::getline(in,word,',');
        std::getline(in,len,',');
        std::getline(in,POS,',');
        std::getline(in,def,'\n');

        // put word lowercase all
        for(char &c:word)
            if(c>='A' && c<='Z')
                c=c-'A'+'a';

        POS=POS.substr(3,POS.size()-6);
        def=def.substr(3,def.size()-6);

        unsigned int type=POS::getType(POS);
        
        Word* w=new Word(word,type,def);

        // Insert new word to necessary data structures
        words.insert(word); // Add to trie
        wordDef.insert(w);  // Add to hash table
    }
    in.close();
    return true;
}

void Dict::getMultileChoices(std::string &ques, std::vector<std::string> &choices, int numChoices, bool isWord)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::vector<Word*> list=wordDef.getRandom(numChoices);
    if(isWord)
    {
        ques=list[0]->word;
        for(int i=0;i<numChoices;++i)
            choices.push_back(list[i]->word);
    }
    else
    {
        for(int i=0; i<POS::Count; i++)
            if(!list[0]->def[i].empty())
            {
                ques=list[0]->def[i][0];
                break;
            }
        for(int i=0;i<numChoices;++i)
            choices.push_back(list[i]->word);
    }

    std::shuffle(choices.begin(),choices.end(),std::default_random_engine(seed));
}

void Dict::addHistory(const std::string& word){
    history.push(word);
}
void Dict::removeHistory(const std::string& word){
    history.pop(word);
}
std::vector<std::string> Dict::getHistory(){
    return history.SLLintoVector();
}


void Dict::removeWord(const std::string& word){
    removeHistory(word);
    //waiting for others
}
#include <Dict.hpp>

bool Dict::reset(){
    words.clear();
    wordDef.clear();
    favList.clear();
    history.clearSLL();
    return setup();
}

bool Dict::switchDataSet(DataSet::Type type)
{
    if(curDataSet==type) return true;
    curDataSet=type;
    return reset();
}

void Dict::updateDef(const std::string &word, unsigned int type, const std::string &oldDef, const std::string &newDef)
{
    wordDef.updateDef(word,type,oldDef,newDef);
}

void Dict::addWord(Word *word)
{
    words.insert(word->word);
    wordDef.insert(word);
}

void Dict::addFav(const std::string &word)
{
    favList.insert(word);
}

bool Dict::lowerStrEng(std::string &str)
{
    for (char &c : str) c=std::tolower(c);
    for (char c: str)
        if (c < 'a' || c > 'z')
            return false;
    return true;
}

Dict::Dict(): curDataSet(DataSet::EE)
{
    setup();
}

Dict::~Dict()
{
    switch(curDataSet){
        case DataSet::EE:
            words.save(MAIN::EE::WORDS);
            wordDef.save(MAIN::EE::WORDDEF);
            favList.save(MAIN::EE::FAVLIST);
            history.saveSLLStr(MAIN::EE::HISTORY);
            break;
        case DataSet::EV:
            words.save(MAIN::EV::WORDS);
            wordDef.save(MAIN::EV::WORDDEF);
            favList.save(MAIN::EV::FAVLIST);
            history.saveSLLStr(MAIN::EV::HISTORY);
            break;
        case DataSet::VE:
            words.save(MAIN::VE::WORDS);
            wordDef.save(MAIN::VE::WORDDEF);
            favList.save(MAIN::VE::FAVLIST);
            history.saveSLLStr(MAIN::VE::HISTORY);
            break;
    }
}

bool Dict::loadFromPrev()
{
    switch(curDataSet){
        case DataSet::EE:
            return 
                words.import(MAIN::EE::WORDS) &&
                wordDef.import(MAIN::EE::WORDDEF) &&
                favList.import(MAIN::EE::FAVLIST) &&
                history.importSLLStr(MAIN::EE::HISTORY)
            ;
        case DataSet::EV:
            return 
                words.import(MAIN::EV::WORDS) &&
                wordDef.import(MAIN::EV::WORDDEF) &&
                favList.import(MAIN::EV::FAVLIST) &&
                history.importSLLStr(MAIN::EV::HISTORY)
            ;
        case DataSet::VE:
            return 
                words.import(MAIN::VE::WORDS) &&
                wordDef.import(MAIN::VE::WORDDEF) &&
                favList.import(MAIN::VE::FAVLIST) &&
                history.importSLLStr(MAIN::VE::HISTORY)
            ;
    }
    return false;
}

bool Dict::importEECsv(const std::string &path)
{
    std::ifstream in(path);
    if(!in.is_open()) return false;

    std::string line;
    std::getline(in,line);

    int cnt=0;
    Word* w=nullptr;
    while(!in.eof() && cnt<LIM_WORDS)
    {
        std::string word, len, POS, def;
        std::getline(in,word,',');
        std::getline(in,len,',');
        std::getline(in,POS,',');
        std::getline(in,def,'\n');

        if(!lowerStrEng(word)) continue;
        if(POS.size()<6 || def.size()<6) continue;

        POS=POS.substr(3,POS.size()-6);
        def=def.substr(3,def.size()-6);

        unsigned int type=POS::getType(POS);
        
        if(w==nullptr || w->word!=word)
        {
            cnt++;
            if(w!=nullptr) addWord(w);
            w=new Word(word,type,def);
        }
        else
            for(int i=0;i<POS::Count;++i)
                if(type&(1<<i))
                    w->def[i].push_back(def);
    }
    if(w!=nullptr) addWord(w);
    in.close();
    return true;
}

bool Dict::importEVTxt(const std::string &path)
{
    std::ifstream in(path);
    if(!in.good() || !in.is_open()) return false;

    int cnt=0;
    std::string line;
    while(getline(in,line) && cnt<LIM_WORDS)
    {
        if(line.empty() || line[0]!='@' || line[1]=='0') continue;

        std::string word;
        {
            int p=line.find('/');
            word=line.substr(1,p-2);
        }

        if(!lowerStrEng(word)) continue;

        Word* w=new Word(word);

        bool flag=false;
        while(1){
            if(!flag){
                getline(in,line);
                if(line.empty() || line[0]!='*') break;
            }

            std::string POS;
            {
                int p=line.find(',');
                if(p==std::string::npos)
                    POS=line.substr(3);
                else
                    POS=line.substr(3,p-3);
            }

            unsigned int ind=POS::getTypeViet(POS);
            w->type|=ind;

            flag=false;
            while(getline(in,line)){
                if(line.empty()) break;
                if(line[0]=='*'){
                    flag=true;
                    break;
                }
                if(line[0]!='-') continue;

                w->def[POS::getIndex(ind)].push_back(line.substr(2));
            }
        }

        addWord(w);
        cnt++;
    }

    return true;
}

bool Dict::importVETxt(const std::string &path)
{
    std::ifstream in(path);
    if(!in.good() || !in.is_open()) return false;

    int cnt=0;
    std::string line;
    while(getline(in,line) && cnt<LIM_WORDS)
    {
        if(line.empty() || line[0]!='@' || line[1]=='0') continue;

        std::string word;
        {
            int p=line.find('/');
            word=line.substr(1,p-2);
        }

        if(!lowerStrEng(word)) continue;

        Word* w=new Word(word);

        bool flag=false;
        while(1){
            if(!flag){
                getline(in,line);
                if(line.empty() || line[0]!='*') break;
            }

            std::string POS;
            {
                int p=line.find(',');
                if(p==std::string::npos)
                    POS=line.substr(3);
                else
                    POS=line.substr(3,p-3);
            }

            unsigned int ind=POS::getTypeVE(POS);
            w->type|=ind;

            flag=false;
            while(getline(in,line)){
                if(line.empty()) break;
                if(line[0]=='*'){
                    flag=true;
                    break;
                }
                if(line[0]!='-') continue;

                w->def[POS::getIndex(ind)].push_back(line.substr(2));
            }
        }

        addWord(w);
        cnt++;
    }

    return true;
}

bool Dict::setup()
{
    if(!loadFromPrev())
        switch(curDataSet){
            case DataSet::EE:
                return 
                    importEECsv(RAW_DATA::EE) &&
                    words.save(DEFAULT::EE::WORDS) &&
                    wordDef.save(DEFAULT::EE::WORDDEF) &&
                    favList.save(DEFAULT::EE::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::EE::HISTORY);
            case DataSet::EV:
                return 
                    importEVTxt(RAW_DATA::EV) &&
                    words.save(DEFAULT::EV::WORDS) &&
                    wordDef.save(DEFAULT::EV::WORDDEF) &&
                    favList.save(DEFAULT::EV::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::EV::HISTORY);
            case DataSet::VE:
                return 
                    importVETxt(RAW_DATA::VE) &&
                    words.save(DEFAULT::VE::WORDS) &&
                    wordDef.save(DEFAULT::VE::WORDDEF) &&
                    favList.save(DEFAULT::VE::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::VE::HISTORY);
        }
    return false;
}

void Dict::addHistory(const std::string& word){
    history.push(word);
}
void Dict::removeHistory(const std::string& word){
    history.pop(word);
}
bool Dict::clearAllHistory(const std::string& path){
    return history.clearHistory(path);
}
std::vector<std::string> Dict::getHistory(){
    return history.SLLintoVector();
}

std::vector<std::string> Dict::getFav()
{
    return favList.traverse();
}

Word *Dict::searchDef(const std::string &word)
{
    return wordDef.searchDef(word);
}

std::vector<std::string> Dict::searchPrefix(const std::string &prefix)
{
    return words.searchPrefix(prefix);
}

std::vector<std::string> Dict::searchPrefixFavlist(const std::string &prefix)
{
    return favList.startWith(prefix);
}

std::vector<Word *> Dict::getMultiChoices(int k)
{
    return wordDef.getRandom(k);
}

void Dict::removeWord(const std::string& word){
    removeHistory(word);
    removeFav(word);
    wordDef.remove(word);
    words.remove(word);
}

void Dict::removeFav(const std::string &word)
{
    favList.remove(word);
}

bool Dict::uppercase2Lowercase(std::string &str)
{
    // int len = str.size();
    // for (int i = 0; i < len; ++i)
    // {
    //     if (str[i] >= 'A' && str[i] <= 'Z')
    //     {
    //         str[i] = str[i] - 'A' + 'a';
    //     }
    // }
    return lowerStrEng(str);
}
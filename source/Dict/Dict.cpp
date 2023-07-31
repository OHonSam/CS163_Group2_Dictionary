#include <Dict.hpp>

bool Dict::reset(){
    words.clear();
    wordDef.clear();
    defTrie.clear();
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

DataSet::Type Dict::getCurDataSet() const
{
    return curDataSet;
}

void Dict::updateDef(const std::string &word, unsigned int type, const std::string &oldDef, const std::string &newDef)
{
    wordDef.updateDef(word,type,oldDef,newDef);
    // defTrie.updateDef(word,type,oldDef,newDef);
}

void Dict::addWord(Word *word)
{
    words.insert(word->word);
    wordDef.insert(word);
    // defTrie.insert(word);
}

bool Dict::isValidPOS(const std::string & str, int& pos){
    int length = str.size();
	if (length > 10 || length == 0)
		return false;

	for (int j = 0; j < length; ++j)
		if (str[j] < '0' || str[j] > '9')
			return false;

	if (length == 10 && str > std::to_string(INT_MAX))
		return false;

	pos = stoi(str);
    if(pos<1 || pos>POS::Count) 
        return false;
	return true;
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

bool Dict::lowerStrViet(std::string &str)
{
    for (char &c : str) c=std::tolower(c);
    for (char c: str)
        if (!(('a'<=c && c<='z') || c==' ' || c=='-'))
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
            defTrie.save(MAIN::EE::DEFTRIE);
            favList.save(MAIN::EE::FAVLIST);
            history.saveSLLStr(MAIN::EE::HISTORY);
            break;
        case DataSet::EV:
            words.save(MAIN::EV::WORDS);
            wordDef.save(MAIN::EV::WORDDEF);
            defTrie.save(MAIN::EV::DEFTRIE);
            favList.save(MAIN::EV::FAVLIST);
            history.saveSLLStr(MAIN::EV::HISTORY);
            break;
        case DataSet::VE:
            words.save(MAIN::VE::WORDS);
            wordDef.save(MAIN::VE::WORDDEF);
            defTrie.save(MAIN::VE::DEFTRIE);
            favList.save(MAIN::VE::FAVLIST);
            history.saveSLLStr(MAIN::VE::HISTORY);
            break;
        case DataSet::Slang:
            words.save(MAIN::Slang::WORDS);
            wordDef.save(MAIN::Slang::WORDDEF);
            defTrie.save(MAIN::Slang::DEFTRIE);
            favList.save(MAIN::Slang::FAVLIST);
            history.saveSLLStr(MAIN::Slang::HISTORY);
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
                defTrie.import(MAIN::EE::DEFTRIE) &&
                favList.import(MAIN::EE::FAVLIST) &&
                history.importSLLStr(MAIN::EE::HISTORY)
            ;
        case DataSet::EV:
            return 
                words.import(MAIN::EV::WORDS) &&
                wordDef.import(MAIN::EV::WORDDEF) &&
                defTrie.import(MAIN::EV::DEFTRIE) &&
                favList.import(MAIN::EV::FAVLIST) &&
                history.importSLLStr(MAIN::EV::HISTORY)
            ;
        case DataSet::VE:
            return 
                words.import(MAIN::VE::WORDS) &&
                wordDef.import(MAIN::VE::WORDDEF) &&
                defTrie.import(MAIN::VE::DEFTRIE) &&
                favList.import(MAIN::VE::FAVLIST) &&
                history.importSLLStr(MAIN::VE::HISTORY)
            ;
        case DataSet::Slang:
            return 
                words.import(MAIN::Slang::WORDS) &&
                wordDef.import(MAIN::Slang::WORDDEF) &&
                defTrie.import(MAIN::Slang::DEFTRIE) &&
                favList.import(MAIN::Slang::FAVLIST) &&
                history.importSLLStr(MAIN::Slang::HISTORY)
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


Word* Dict::getDailyWord()
{
    wordDef.initSeedForRandom();
    return wordDef.randomWordOfDay();
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

        std::string word=line.substr(1);

        if(!lowerStrViet(word)) continue;

        Word* w=new Word(word);

        bool flag=false;
        while(1){
            if(line.empty()) break;
            if(!flag){
                getline(in,line);
                if(line.empty() || line[0]!='*') break;
            }

            std::string POS;
            {
                int p=line.find(',');
                if(p==std::string::npos)
                    POS=line.substr(2);
                else
                    POS=line.substr(2,p-3);
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

bool Dict::isInDict(const std::string& word){
    return words.checkExist(word);
}
bool Dict::isInHistory(const std::string& word){
    return history.find(word);
}

bool Dict::isInFavList(const std::string& word){
    return favList.isStartedWith(word);
}

bool Dict::importSlangCsv(const std::string &path)
{
    std::ifstream in(path);
    if(!in.is_open()) return false;

    std::string line;
    std::getline(in,line);

    int cnt=0;
    while(!in.eof() && cnt<LIM_WORDS)
    {
        std::string ign, word, def;
        std::getline(in,ign,',');
        std::getline(in,word,',');
        for(int i=0; i<3; i++) std::getline(in,ign,',');
        std::getline(in,def,'\n');

        if(!lowerStrEng(word)) continue;

        addWord(new Word(word,POS::Other,def));
        cnt++;
    }
    in.close();
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
                    defTrie.save(DEFAULT::EE::DEFTRIE) &&
                    favList.save(DEFAULT::EE::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::EE::HISTORY);
            case DataSet::EV:
                return 
                    importEVTxt(RAW_DATA::EV) &&
                    words.save(DEFAULT::EV::WORDS) &&
                    wordDef.save(DEFAULT::EV::WORDDEF) &&
                    defTrie.save(DEFAULT::EV::DEFTRIE) &&
                    favList.save(DEFAULT::EV::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::EV::HISTORY);
            case DataSet::VE:
                return 
                    importVETxt(RAW_DATA::VE) &&
                    words.save(DEFAULT::VE::WORDS) &&
                    wordDef.save(DEFAULT::VE::WORDDEF) &&
                    defTrie.save(DEFAULT::VE::DEFTRIE) &&
                    favList.save(DEFAULT::VE::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::VE::HISTORY);
            case DataSet::Slang:
                return 
                    importSlangCsv(RAW_DATA::Slang) &&
                    words.save(DEFAULT::Slang::WORDS) &&
                    wordDef.save(DEFAULT::Slang::WORDDEF) &&
                    defTrie.save(DEFAULT::Slang::DEFTRIE) &&
                    favList.save(DEFAULT::Slang::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::Slang::HISTORY);
        }
    return false;
}

void Dict::addHistory(const std::string& word){
    history.insert(word);
}
void Dict::removeHistory(const std::string& word){
    history.pop(word);
}
bool Dict::clearAllHistory(){
    switch (curDataSet)
    {
    case DataSet::EE:
        return history.clearHistory(MAIN::EE::HISTORY);
    case DataSet::EV:
        return history.clearHistory(MAIN::EV::HISTORY);
    case DataSet::VE:  
        return history.clearHistory(MAIN::VE::HISTORY);
    case DataSet::Slang:
        return history.clearHistory(MAIN::Slang::HISTORY);
    default:
        return false;
    }  
}

bool Dict::clearFavList(){
    switch (curDataSet)
    {
    case DataSet::EE:
        return favList.clearFavList(MAIN::EE::FAVLIST);
    case DataSet::EV:
        return favList.clearFavList(MAIN::EV::FAVLIST);
    case DataSet::VE:  
        return favList.clearFavList(MAIN::VE::FAVLIST);
    case DataSet::Slang:
        return favList.clearFavList(MAIN::Slang::FAVLIST);
    default:
        return false;
    }  
}

std::vector<std::string> Dict::getHistory(){
    return history.SLLintoVector();
}

std::vector<std::string> Dict::getFav()
{
    return favList.traverse();
}

Word *Dict::searchForDef(const std::string &word)
{
    return wordDef.searchDef(word);
}

std::vector<std::string> Dict::searchForWord(const std::string &def)
{
    // return defTrie.searchKeyWord(def);
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
#include <Dict.hpp>
// #include "Dict.hpp"
// #include <iostream>
// #include <sstream>

std::string Dict::Purify(std::string s) {
    if (s[0] < 97 || s[0] > 122) {
        if (s[0] >= 65 && s[0] <= 90) s[0] += 32;
        else {
            std::string temp = s.substr(1, s.size() - 1);
            s = temp;
        }
    } 
    if (s[s.size() - 1] < 97 || s[s.size() - 1] > 122) {
        if (s[s.size() - 1] >= 65 && s[s.size() - 1] <= 90) s[s.size() - 1] += 32;
        else {
            std::string temp = s.substr(0, s.size() - 1);
            s = temp;
        }
    } 
    return s;
}

std::vector<std::string> Dict::stringCut(const std::string ls) {
	// long string
    std::stringstream s(ls);
    std::string word;
    std::vector <std::string> res;
    while (s >> word) res.push_back(word);
    return res;
}

std::string Dict::CorrectDef(const std::string &def) {
    std::vector<std::string> res = searchForWord(def);
	if (res.size()) {
		return def;
	}
	std::vector<std::string> p;
	p = stringCut(def);
	std::string correct = "";
	for (int i = 0; i < p.size(); i++) {
		res = searchForWord(correct + " " + p[i]);
		if (!res.size()) {
			res = searchPrefixDefTrie(p[i]);
			int temp = p[i].length();
			std::vector <std::string> character(temp, "");
			character[0] += p[i][0];
			for (int j = 1; j < p[i].length(); j++) {
				character[j] = character[j - 1] + p[i][j];
			}
			int idx = temp - 1;
			while (!res.size() && idx >= 0) {
				res = searchPrefixDefTrie(character[idx]);
				idx--;
			}
			if (idx == -1) return "No further corrections could be made!";
			for (int j = 0; j < res.size(); j++) {
				if ((searchForWord(correct + " " + res[j])).size()) {
					correct += " " + res[j];
					break;
				}
			}
			// break;
		} 
		else {
			correct += " " + p[i];
		}
	}
    if (correct.size()) return correct;
    return "No further corrections could be made!";
}

bool Dict::reset(){
    numWords=0;
    for(int i=0; i<UNIQUE_CHARS; i++) 
        numWordsStartsWith[i]=0;
    words.clear();
    wordDef.clear();
    defTrie.clear();
    favList.clear();
    history.clearSLL();
    switch(curDataSet){
        case DataSet::EE:
            words.import(DEFAULT::EE::WORDS);
            wordDef.import(DEFAULT::EE::WORDDEF);
            defTrie.import(DEFAULT::EE::DEFTRIE);
            favList.import(DEFAULT::EE::FAVLIST);
            history.importSLLStr(DEFAULT::EE::HISTORY);
            break;
        case DataSet::EV:
            words.import(DEFAULT::EV::WORDS);
            wordDef.import(DEFAULT::EV::WORDDEF);
            defTrie.import(DEFAULT::EV::DEFTRIE);
            favList.import(DEFAULT::EV::FAVLIST);
            history.importSLLStr(DEFAULT::EV::HISTORY);
            break;
        case DataSet::VE:
            words.import(DEFAULT::VE::WORDS);
            wordDef.import(DEFAULT::VE::WORDDEF);
            defTrie.import(DEFAULT::VE::DEFTRIE);
            favList.import(DEFAULT::VE::FAVLIST);
            history.importSLLStr(DEFAULT::VE::HISTORY);
            break;
        case DataSet::Slang:
            words.import(DEFAULT::Slang::WORDS);
            wordDef.import(DEFAULT::Slang::WORDDEF);
            defTrie.import(DEFAULT::Slang::DEFTRIE);
            favList.import(DEFAULT::Slang::FAVLIST);
            history.importSLLStr(DEFAULT::Slang::HISTORY);
            break;
    }
    return true;
    // return setup();
}

bool Dict::switchDataSet(DataSet::Type type)
{
    if(curDataSet==type) return true;
    // return reset();
    // return setup();
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
        case DataSet::Emoji:
            words.save(MAIN::Emoji::WORDS);
            wordDef.save(MAIN::Emoji::WORDDEF);
            defTrie.save(MAIN::Emoji::DEFTRIE);
            favList.save(MAIN::Emoji::FAVLIST);
            history.saveSLLStr(MAIN::Emoji::HISTORY);
            break;
    }
    words.clear();
    wordDef.clear();
    defTrie.clear();
    favList.clear();
    history.clearSLL();
    curDataSet=type;
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
            case DataSet::Emoji:
                return 
                    importEmojiTxt(RAW_DATA::Emoji) &&
                    words.save(DEFAULT::Emoji::WORDS) &&
                    wordDef.save(DEFAULT::Emoji::WORDDEF) &&
                    defTrie.save(DEFAULT::Emoji::DEFTRIE) &&
                    favList.save(DEFAULT::Emoji::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::Emoji::HISTORY);
        }
    return true;
}

DataSet::Type Dict::getCurDataSet() const
{
    return curDataSet;
}

void Dict::updateDef(const std::string &word, unsigned int type, const std::string &oldDef, const std::string &newDef)
{
    Word* oldWord = wordDef.searchDef(word);
    Word* newWord = wordDef.updateDef(word,type,oldDef,newDef);
    if (newWord && oldWord) defTrie.updateDef(oldWord, newWord);
    return;
}

void Dict::addWord(Word *word, bool fromUser)
{
    if(!fromUser) {
        if(curDataSet!=DataSet::Emoji){
            int i=word->word[0]-'a';
            if(numWordsStartsWith[i]>=LIM_EACH_CHAR) 
                return;
            numWordsStartsWith[i]++;
        }
    }
    numWords++;
    words.insert(word->word);
    wordDef.insert(word);
    defTrie.insert(word);
    return;
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
    // if (!searchForDef(word)) return;
    // do you want to add it?
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
    numWords=0;
    for(int i=0; i<UNIQUE_CHARS; i++) 
        numWordsStartsWith[i]=0;
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
        case DataSet::Emoji:
            words.save(MAIN::Emoji::WORDS);
            wordDef.save(MAIN::Emoji::WORDDEF);
            defTrie.save(MAIN::Emoji::DEFTRIE);
            favList.save(MAIN::Emoji::FAVLIST);
            history.saveSLLStr(MAIN::Emoji::HISTORY);
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
        case DataSet::Emoji:
            return 
                words.import(MAIN::Emoji::WORDS) &&
                wordDef.import(MAIN::Emoji::WORDDEF) &&
                defTrie.import(MAIN::Emoji::DEFTRIE) &&
                favList.import(MAIN::Emoji::FAVLIST) &&
                history.importSLLStr(MAIN::Emoji::HISTORY)
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

    numWords=0;
    Word* w=nullptr;
    while(!in.eof() && numWords<LIM_WORDS)
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
            if(w!=nullptr) addWord(w,false);
            w=new Word(word,type,def);
        }
        else
            for(int i=0;i<POS::Count;++i)
                if(type&(1<<i))
                    w->def[i].push_back(def);
    }
    if(w!=nullptr) addWord(w,false);
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

    numWords=0;
    std::string line;
    while(getline(in,line) && numWords<LIM_WORDS)
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

        addWord(w, false);
    }

    return true;
}

bool Dict::importVETxt(const std::string &path)
{
    std::ifstream in(path);
    if(!in.good() || !in.is_open()) return false;

    numWords=0;
    std::string line;
    while(getline(in,line) && numWords<LIM_WORDS)
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

        addWord(w, false);
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
    return favList.check(word);
}

bool Dict::importSlangCsv(const std::string &path)
{
    std::ifstream in(path);
    if(!in.is_open()) return false;

    std::string line;
    std::getline(in,line);

    numWords=0;
    while(!in.eof() && numWords<LIM_WORDS)
    {
        std::string ign, word, def;
        std::getline(in,ign,',');
        std::getline(in,word,',');
        for(int i=0; i<3; i++) std::getline(in,ign,',');
        std::getline(in,def,'\n');

        if(!lowerStrEng(word)) continue;

        addWord(new Word(word,POS::Other,def),false);
    }
    in.close();
    return true;
}

bool Dict::importEmojiTxt(const std::string &path)
{
    std::ifstream in(path);
    if(!in.is_open()) return false;

    std::string line;
    std::getline(in,line);

    numWords=0;
    while(!in.eof() && numWords<LIM_WORDS)
    {
        std::string emoji, meaning;
        std::getline(in,emoji,'`');
        std::getline(in,meaning,'\n');

        lowerStrEng(emoji);

        addWord(new Word(emoji,POS::Other,meaning),false);
    }

    in.close();
    return true;
}

bool Dict::setup()
{
    // switch(curDataSet){
    //     case DataSet::EE:
    //         words.save(MAIN::EE::WORDS);
    //         wordDef.save(MAIN::EE::WORDDEF);
    //         defTrie.save(MAIN::EE::DEFTRIE);
    //         favList.save(MAIN::EE::FAVLIST);
    //         history.saveSLLStr(MAIN::EE::HISTORY);
    //         break;
    //     case DataSet::EV:
    //         words.save(MAIN::EV::WORDS);
    //         wordDef.save(MAIN::EV::WORDDEF);
    //         defTrie.save(MAIN::EV::DEFTRIE);
    //         favList.save(MAIN::EV::FAVLIST);
    //         history.saveSLLStr(MAIN::EV::HISTORY);
    //         break;
    //     case DataSet::VE:
    //         words.save(MAIN::VE::WORDS);
    //         wordDef.save(MAIN::VE::WORDDEF);
    //         defTrie.save(MAIN::VE::DEFTRIE);
    //         favList.save(MAIN::VE::FAVLIST);
    //         history.saveSLLStr(MAIN::VE::HISTORY);
    //         break;
    //     case DataSet::Slang:
    //         words.save(MAIN::Slang::WORDS);
    //         wordDef.save(MAIN::Slang::WORDDEF);
    //         defTrie.save(MAIN::Slang::DEFTRIE);
    //         favList.save(MAIN::Slang::FAVLIST);
    //         history.saveSLLStr(MAIN::Slang::HISTORY);
    //         break;
    //     case DataSet::Emoji:
    //         words.save(MAIN::Emoji::WORDS);
    //         wordDef.save(MAIN::Emoji::WORDDEF);
    //         defTrie.save(MAIN::Emoji::DEFTRIE);
    //         favList.save(MAIN::Emoji::FAVLIST);
    //         history.saveSLLStr(MAIN::Emoji::HISTORY);
    //         break;
    // }
    // words.clear();
    // wordDef.clear();
    // defTrie.clear();
    // favList.clear();
    // history.clearSLL();
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
            case DataSet::Emoji:
                return 
                    importEmojiTxt(RAW_DATA::Emoji) &&
                    words.save(DEFAULT::Emoji::WORDS) &&
                    wordDef.save(DEFAULT::Emoji::WORDDEF) &&
                    defTrie.save(DEFAULT::Emoji::DEFTRIE) &&
                    favList.save(DEFAULT::Emoji::FAVLIST) &&
                    history.saveSLLStr(DEFAULT::Emoji::HISTORY);
        }
    return true;
}

void Dict::addHistory(const std::string& word){
    if (!isInHistory(word)) history.insert(word);
    return;
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
    case DataSet::Emoji:
        return history.clearHistory(MAIN::Emoji::HISTORY);
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
    case DataSet::Emoji:
        return favList.clearFavList(MAIN::Emoji::FAVLIST);
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
    // removeHistory(def);
    // addHistory(def);
    return defTrie.searchKeyWord(def);
}

std::vector<std::string> Dict::searchPrefix(const std::string &prefix)
{
    return words.searchPrefix(prefix);
}

std::vector<std::string> Dict::searchPrefixFavlist(const std::string &prefix)
{
    return favList.startWith(prefix);
}

std::vector<std::string> Dict::searchPrefixDefTrie(const std::string &prefix) {
    return defTrie.searchPrefix(prefix);
}
std::vector<Word *> Dict::getMultiChoices(int k)
{
    return wordDef.getRandom(k);
}

void Dict::removeWord(const std::string& word){
    removeHistory(word);
    removeFav(word);
    removeDefTrie(word);
    wordDef.remove(word);
    words.remove(word);
}

void Dict::removeDefTrie(const std::string &word) {
    Word* w = wordDef.searchDef(word);
    defTrie.remove(w);
    return;
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
// std::vector<std::string> stringCut(const std::string ls) {
// 	// long string
//     std::stringstream s(ls);
//     std::string word;
//     std::vector <std::string> res;
//     while (s >> word) res.push_back(word);
//     return res;
// }
// int main() {
//     Dict* dict = new Dict();
//     Word* word = new Word();
//     word->word = "hello";
//     word->def[0].push_back("xin chao ban rat dep");
//     word->def[1].push_back("chao");
//     word->def[7].push_back("thu hut");
//     word->type = 131;
//     Word* word1 = new Word();
//     word1->word = "hellu";
//     word1->def[0].push_back("chao chao");
//     word1->def[1].push_back("xin dep");
//     word1->def[7].push_back("i love you");
//     word1->type = 131;
//     dict ->addWord(word);
//     dict ->addWord(word1);
//     std::string def; std::cin >> def;
// 	std::vector<std::string> res = dict -> searchForWord(def);
// 	if (res.size()) {
// 		std::cout << "There's no need to correct!\n";
// 		return;
// 	}
// 	std::vector<std::string> p;
// 	p = stringCut(def);
// 	std::string correct = "";
// 	for (int i = 0; i < p.size(); i++) {
// 		res = dict -> searchForWord(correct + p[i]);
// 		if (!res.size()) {
// 			res = dict -> searchPrefixDefTrie(p[i]);
// 			int temp = p[i].length();
// 			std::vector <std::string> character(temp, "");
// 			character[0] += p[i][0];
// 			for (int j = 1; j < p[i].length(); j++) {
// 				character[j] = character[j - 1] + p[i][j];
// 			}
// 			int idx = temp - 1;
// 			while (!res.size()) {
// 				res = dict -> searchPrefixDefTrie(character[idx]);
// 				idx--;
// 			}
// 			for (int j = 0; j < res.size(); j++) {
// 				if ((dict -> searchForWord(correct + res[j])).size()) {
// 					correct += res[j];
// 					break;
// 				}
// 			}
// 			// break;
// 		} 
// 		else correct += p[i];
// 	}
// 	std::cout << "Did you mean " << correct << " ?\n";
//     return 0;
// }
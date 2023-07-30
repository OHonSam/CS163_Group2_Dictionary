#include <Dict.hpp>
// #include "Dict.hpp"
// #include <iostream>
// #include <sstream>
bool Dict::reset(){
    words.clear();
    wordDef.clear();
    defTrie -> clear();
    favList.clear();
    history.clearSLL();
    return 
        words.import(DEFAULT::WORDS) &&
        wordDef.import(DEFAULT::WORDDEF) &&
        defTrie -> import(DEFAULT::DEFTRIE) &&
        favList.import(DEFAULT::FAVLIST) &&
        history.importSLLStr(DEFAULT::HISTORY)
    ;
}

void Dict::updateDef(const std::string &word, unsigned int type, const std::string &oldDef, const std::string &newDef)
{
    // wordDef.updateDef(word,type,oldDef,newDef);
    defTrie -> updateDef(word, type, oldDef, newDef);
}

void Dict::addWord(Word *word)
{
    words.insert(word->word);
    wordDef.insert(word);
    defTrie -> insert(word);
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

Dict::Dict()
{
    defTrie = new DefTrie(wordDef);
    if(!loadFromPrev())
    {
        importEECsv(RAW_DATA::EE);

        words.save(DEFAULT::WORDS);
        wordDef.save(DEFAULT::WORDDEF);
        defTrie -> save(DEFAULT::DEFTRIE);
        favList.save(DEFAULT::FAVLIST);
        history.saveSLLStr(DEFAULT::HISTORY);
    }
}

Dict::~Dict()
{
    words.save(MAIN::WORDS);
    wordDef.save(MAIN::WORDDEF);
    defTrie -> save(MAIN::DEFTRIE);
    favList.save(MAIN::FAVLIST);
    history.saveSLLStr(MAIN::HISTORY);
}

bool Dict::loadFromPrev()
{
    return 
        words.import(MAIN::WORDS) &&
        wordDef.import(MAIN::WORDDEF) &&
        defTrie -> import(MAIN::DEFTRIE) &&
        favList.import(MAIN::FAVLIST) &&
        history.importSLLStr(MAIN::HISTORY)
    ;
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

bool Dict::isInDict(const std::string& word){
    return words.checkExist(word);
}
bool Dict::isInHistory(const std::string& word){
    return history.find(word);
}
void Dict::addHistory(const std::string& word){
    history.insert(word);
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

Word *Dict::searchForDef(const std::string &word)
{
    removeHistory(word);
    addHistory(word);
    return wordDef.searchDef(word);
}

std::vector<std::string> Dict::searchForWord(const std::string &def)
{
    // removeHistory(def);
    // addHistory(def);
    return defTrie -> searchKeyWord(def);
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
    return defTrie -> searchPrefix(prefix);
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
    defTrie -> remove(w);
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
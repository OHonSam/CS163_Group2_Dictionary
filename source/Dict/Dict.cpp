#include <Dict.hpp>

// bool Dict::importJson(const std::string &path)
// {
//     // Open the JSON file
//     std::ifstream inputFile(path);
//     if (!inputFile.is_open()) {
//         std::cerr << "Failed to open the input file." << std::endl;
//         return false;
//     }
bool Dict::reset(){
    if(!history.clearHistory("HistorySLL.bin"))
        return false;
    //waiting for others
    if(words.import("assets/default/words.bin"))
        return false;
    return true;
}

//     // Read the entire file into a std::string
//     std::string jsonString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

//     // Close the file
//     inputFile.close();

//     // Parse the JSON std::string
//     Json::Value root;
//     Json::Reader reader;

//     bool parsingSuccessful = reader.parse(jsonString, root);
//     if (!parsingSuccessful) {
//         std::cerr << "Failed to parse the JSON file: " << reader.getFormattedErrorMessages() << std::endl;
//         return false;
//     }

//     // Iterate over the words
//     for(const auto& key: root.getMemberNames()) {
//         // Get the word
//         std::string word = key;

//         // Get the definition
//         std::string definition = root[word].asString();

//         //Insert the word into the trie
//         words.insert(word);

//         //Insert the word and its definition into the hash table
//         wordDef.insert(word, definition);
//     }

//     return true;
// }

Dict::Dict(bool firstInit)
{
    if(firstInit)
        importCsv("assets/Datasets/EE.csv");
    else
    {
        words.import("assets/main/words.bin");
        wordDef.import("assets/main/wordDef.bin");
        history.importSLLStr("assets/main/HistorySLL.bin");
        favList.import("assets/main/favList.bin");
    }
}

bool Dict::importCsv(const std::string &path)
{
    std::ifstream in("assets/Datasets/EE.csv");
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
    words.remove(word);
    wordDef.remove(word);
}
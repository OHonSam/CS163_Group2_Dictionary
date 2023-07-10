#include <Dict.hpp>
#include <json/json.h>
#include<Libraries.hpp>

// bool Dict::importJson(const std::string &path)
// {
//     // Open the JSON file
//     std::ifstream inputFile(path);
//     if (!inputFile.is_open()) {
//         std::cerr << "Failed to open the input file." << std::endl;
//         return false;
//     }

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
}

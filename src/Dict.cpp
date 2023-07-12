#include <Dict.hpp>
#include <json/json.h>
#include<Libraries.hpp>

Dict::Dict() {
    wordDef.import("../CS163_Group2_Dictionary/ASSETS/DataStructure/default/HashTable.bin");
    // deftrie import
}


bool Dict::importJson(const std::string &path)
{
    // Open the JSON file
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return false;
    }

    // Read the entire file into a std::string
    std::string jsonString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    // Close the file
    inputFile.close();

    // Parse the JSON std::string
    Json::Value root;
    Json::Reader reader;

    bool parsingSuccessful = reader.parse(jsonString, root);
    if (!parsingSuccessful) {
        std::cerr << "Failed to parse the JSON file: " << reader.getFormattedErrorMessages() << std::endl;
        return false;
    }

    // Iterate over the words
    for(const auto& key: root.getMemberNames()) {
        // Get the word
        std::string word = key;

        // Get the definition
        std::string definition = root[word].asString();

        //Insert the word into the trie
        words.insert(word);

        //Insert the word and its definition into the hash table
        wordDef.insert(word, definition);
    }

    return true;
}

void removeWord(const std::string& word) {
    // remove in deftrie
    
    // remove in fav, history

    // remove in trie

    // remove in hash table

}
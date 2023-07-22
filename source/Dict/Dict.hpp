#ifndef DICT_HPP
#define DICT_HPP
// #include "TST.hpp"
#include "HashTable.hpp"
#include "SLL.hpp"
#include "Trie.hpp"
#include <Libraries.hpp>

class Dict
{
private:
	SLL <std::string> history;
	HashTable wordDef;
	Trie words;
	// BTree favList;

public:
	// Dict(const std::string& path, bool isJson);				

	// Save data structures before deleting
	// ~Dict();										

	// Load from json file
	// bool importJson(const std::string& path); 

	// Load from csv file
	bool importCsv(const std::string& path);				

	// Load from binary file
	// bool importBinary(const std::string& path); 				

	// Reset to the default dataset
	bool reset();									

	// Edit definition of existed word
	// void updateDef(const std::string& word, const std::string& newDef); 

	// Add a pair of word and definition
	// void addWord(const std::string& word, const std::string& def);		

	// Add a word to the favorite list
	// void addFav(const std::string& word);					

	// Add a word to the history
	void addHistory(const std::string& word);//			

	// Remove a word and corresponding definition
	void removeWord(const std::string& word);	
	// Remove all words in the history
	void clearHistory();	

 	// Remove a word from the favorite list
	// void removeFav(const std::string& word);				

 	// Remove a word from the history
	void removeHistory(const std::string& word);//				

	// Get the history in the vector
	std::vector<std::string> getHistory();						

	// Get the favorite list
	// std::vector<std::string> getFav();						

   	// Return a definition for a required word
    // std::string searchDef(const std::string& word); 			
	
	// Return the list of words which has an identical given prefix
	// std::vector<std::string> searchPrefix(const std::string& prefix);		

	// Get the list of multple choices
	void getMultileChoices(std::string& ques, std::vector<std::string>& choices, int numChoices, bool isWord);
};
#endif
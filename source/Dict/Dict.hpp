#ifndef DICT_HPP
#define DICT_HPP
#include "TST.hpp"
#include "HashTable.hpp"
#include "SLL.hpp"
#include "Trie.hpp"
#include <Libraries.hpp>

namespace RAW_DATA
{
	const std::string EE = "assets/RawData/EE.csv";
}

namespace MAIN
{
	const std::string WORDS = "assets/DS/main/words.bin";
	const std::string WORDDEF = "assets/DS/main/wordDef.bin";
	const std::string FAVLIST = "assets/DS/main/favList.bin";
	const std::string HISTORY = "assets/DS/main/history.bin";
}

namespace DEFAULT
{
	const std::string WORDS = "assets/DS/default/words.bin";
	const std::string WORDDEF = "assets/DS/default/wordDef.bin";
	const std::string FAVLIST = "assets/DS/default/favList.bin";
	const std::string HISTORY = "assets/DS/default/history.bin";
}

class Dict
{
private:
	const int LIM_WORDS = 100000;

	SLL<std::string> history;
	HashTable wordDef;
	Trie words;
	TST favList;

	

public:
	// If first time running, import the raw dataset
	// else load from the saved data structures in main folder
	Dict();

	// Save data structures before deleting
	~Dict();	
	// Check if a string is a valid English word (only contains letters from a to z) and convert uppercase letter to lowercase letter
	bool lowerStrEng(std::string& str);
	// Load from previous save data
	bool loadFromPrev();

	// Load from csv file
	bool importEECsv(const std::string &path);

	// Reset to the default dataset
	bool reset();

	// Edit definition of existed word
	void updateDef(const std::string &word, unsigned int type, const std::string &oldDef, const std::string &newDef);

	// Add a new word and corresponding definition
	void addWord(Word *word);

	// Add a word to the favorite list 
	void addFav(const std::string &word);

	// Add a word to the history
	void addHistory(const std::string &word); //

	// Remove a word and corresponding definition
	void removeWord(const std::string &word);
	// Remove all words in the history
	bool clearAllHistory(const std::string &path);

	// Remove a word from the favorite list
	void removeFav(const std::string &word);

	// Remove a word from the history
	void removeHistory(const std::string &word); //

	// Get the history in the vector
	std::vector<std::string> getHistory();

	// Get the favorite list
	std::vector<std::string> getFav();

	// Return a definition for a required word
	Word *searchDef(const std::string &word);

	// Return the list of words which has an identical given prefix
	std::vector<std::string> searchPrefix(const std::string &prefix);

	// Return the list of words which has an identical given prefix in favourite list
	std::vector<std::string> searchPrefixFavlist(const std::string &prefix);

	// Get the list of multple choices
	std::vector<Word*> getMultiChoices(int k);

	//Turn uppercase to lowercase
	bool uppercase2Lowercase(std::string &str);
};
#endif
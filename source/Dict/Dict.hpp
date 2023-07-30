#ifndef DICT_HPP
#define DICT_HPP
#include "TST.hpp"
#include "HashTable.hpp"
#include "SLL.hpp"
#include "Trie.hpp"
#include "DefTrie.hpp"
#include <Libraries.hpp>

namespace DataSet
{
	enum Type
	{
		EE,
		EV,
		VE,
		Slang,
		Count
	};
}

namespace RAW_DATA
{
	const std::string EE = "assets/RawData/EE.csv";
	const std::string EV = "assets/RawData/EV.txt";
	const std::string VE = "assets/RawData/VE.txt";
	const std::string Slang = "assets/RawData/Slang.csv";
}

namespace MAIN
{
	namespace EE
	{
		const std::string WORDS = "assets/DS/EE/main/words.bin";
		const std::string WORDDEF = "assets/DS/EE/main/wordDef.bin";
		const std::string FAVLIST = "assets/DS/EE/main/favList.bin";
		const std::string HISTORY = "assets/DS/EE/main/history.bin";
	}
	namespace EV
	{
		const std::string WORDS = "assets/DS/EV/main/words.bin";
		const std::string WORDDEF = "assets/DS/EV/main/wordDef.bin";
		const std::string FAVLIST = "assets/DS/EV/main/favList.bin";
		const std::string HISTORY = "assets/DS/EV/main/history.bin";
	}

	namespace VE
	{
		const std::string WORDS = "assets/DS/VE/main/words.bin";
		const std::string WORDDEF = "assets/DS/VE/main/wordDef.bin";
		const std::string FAVLIST = "assets/DS/VE/main/favList.bin";
		const std::string HISTORY = "assets/DS/VE/main/history.bin";
	}

	namespace Slang
	{
		const std::string WORDS = "assets/DS/Slang/main/words.bin";
		const std::string WORDDEF = "assets/DS/Slang/main/wordDef.bin";
		const std::string FAVLIST = "assets/DS/Slang/main/favList.bin";
		const std::string HISTORY = "assets/DS/Slang/main/history.bin";
	}
}

namespace DEFAULT
{
	namespace EE
	{
		const std::string WORDS = "assets/DS/EE/default/words.bin";
		const std::string WORDDEF = "assets/DS/EE/default/wordDef.bin";
		const std::string FAVLIST = "assets/DS/EE/default/favList.bin";
		const std::string HISTORY = "assets/DS/EE/default/history.bin";
	}
	namespace EV
	{
		const std::string WORDS = "assets/DS/EV/default/words.bin";
		const std::string WORDDEF = "assets/DS/EV/default/wordDef.bin";
		const std::string FAVLIST = "assets/DS/EV/default/favList.bin";
		const std::string HISTORY = "assets/DS/EV/default/history.bin";
	}

	namespace VE
	{
		const std::string WORDS = "assets/DS/VE/default/words.bin";
		const std::string WORDDEF = "assets/DS/VE/default/wordDef.bin";
		const std::string FAVLIST = "assets/DS/VE/default/favList.bin";
		const std::string HISTORY = "assets/DS/VE/default/history.bin";
	}

	namespace Slang
	{
		const std::string WORDS = "assets/DS/Slang/default/words.bin";
		const std::string WORDDEF = "assets/DS/Slang/default/wordDef.bin";
		const std::string FAVLIST = "assets/DS/Slang/default/favList.bin";
		const std::string HISTORY = "assets/DS/Slang/default/history.bin";
	}
}

class Dict
{
private:
	const int LIM_WORDS = 100000;

	SLL<std::string> history;
	HashTable wordDef;
	Trie words;
	TST favList;
	DefTrie defTrie;

	DataSet::Type curDataSet;

public:
	// If first time running, import the raw dataset
	// else load from the saved data structures in main folder
	Dict();

	// Save data structures before deleting
	~Dict();	

	// Check if a string is a valid English word (only contains letters from a to z) and convert uppercase letter to lowercase letter
	bool lowerStrEng(std::string& str);

	bool lowerStrViet(std::string& str);

	// Load from previous save data
	bool loadFromPrev();

	// Load from EE data
	bool importEECsv(const std::string &path);

	// Load from EV data
	bool importEVTxt(const std::string &path);

	// Load from VE data
	bool importVETxt(const std::string &path);

	// Load from Slang words data
	bool importSlangCsv(const std::string &path);

	bool setup();
	
	// Reset to the default dataset
	bool reset();

	bool switchDataSet(DataSet::Type type);

	// Get the current dataset
	DataSet::Type getCurDataSet() const;

	// Edit definition of existed word
	void updateDef(const std::string &word, unsigned int type, const std::string &oldDef, const std::string &newDef);

	// Add a new word and corresponding definition
	void addWord(Word *word);

	// Check if a string is a valid number representing part of speech
	bool isValidPOS(const std::string &str, int &pos);

	// Add a word to the favourite list
	void addFav(const std::string &word);

	// Add a word to the history
	void addHistory(const std::string &word); //

	// Check if a word is already in the History list
	bool isInHistory(const std::string &word);

	// Check if a word is already in the favourite list
	bool isInFavList(const std::string& word);

	// Check if a word is already in the Dictionary
	bool isInDict(const std::string &word);

	// Remove a word and corresponding definition
	void removeWord(const std::string &word);
	// Remove all words in the history
	bool clearAllHistory();
	
	// Remove all words in the favourite list
	bool clearFavList();

	// Remove a word from the favourite list
	void removeFav(const std::string &word);

	// Remove a word from the history
	void removeHistory(const std::string &word); //

	// Get the history in the vector
	std::vector<std::string> getHistory();

	// Get the favourite list
	std::vector<std::string> getFav();

	// Return a definition for a required word
	Word *searchForDef(const std::string &word);

	// Return the word has given definition
	std::vector<std::string> searchForWord(const std::string &def);

	// Return the list of words which has an identical given prefix
	std::vector<std::string> searchPrefix(const std::string &prefix);

	// Return the list of words which has an identical given prefix in favourite list
	std::vector<std::string> searchPrefixFavlist(const std::string &prefix);

	// Get a daily word
	Word *getDailyWord();

	// Get the list of multple choices
	std::vector<Word*> getMultiChoices(int k);

	// Turn uppercase to lowercase
	bool uppercase2Lowercase(std::string &str);
};
#endif
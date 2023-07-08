#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include<Libraries.hpp>
#include "BIT.hpp"

class HashTable
{
private:
	const int NMOD=3;
	const int BASE=311;
	const int MOD[3]={1000003, 1000033, 1000037};

	BIT bit;

	int numWords;
    
    // Buckets 2d std::vector itialized with size 1e6, approximately greater than the number of words
	std::vector<std::vector<std::pair<std::string, std::string>>> buckets;

	// Hash function
	int hash(const std::string& word);						

public:
	HashTable();				

	void clear();									

	// Load from binary file
	bool import(const std::string& path);					

	// Save as binary file
	bool save(const std::string& path);						

	// Insert a pair of word and definition
	int insert(const std::string& word, const std::string& def);		
	
	// Remove a pair that has a word given in it
	void remove(const std::string& word);					

	// Edit definition of existed word
	void updateDef(const std::string& word, const std::string& newDef);	

	// Find a definition for a required word	
	std::string searchDef(const std::string& word);

	//	Random a word and its definition
	void initSeedForRandom();//to avoid srand() in for loop 
	std::pair<std::string, std::string> randomWordOfDay();//call initSeedForRandom() before randomWordOfDay()

	// Get the list of random k word-definition pairs
	std::vector<std::pair<std::string, std::string>> getRandom(int k);			
};

#endif
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include<Libraries.hpp>
#include "BIT.hpp"
#include "Word.hpp"

class HashTable
{
private:
	const int NMOD=3;
	const int BASE=311;
	const int MOD[3]={1000003, 1000033, 1000037};

	BIT bit;

	int numWords;
    
    // Buckets 2d std::vector initialized with size 1e6, approximately greater than the number of words
	std::vector<std::vector<Word*>> buckets;

	// Hash function
	int hash(const std::string& word);						

public:
	HashTable();
	~HashTable();				

	void clear();									

	// Load from binary file
	bool import(const std::string& path);					

	// Save as binary file
	bool save(const std::string& path);						

	// Insert a whole struct word: When inserting, a new struct word would be created and then add to the hash table
	int insert(Word* word);		
	
	// Remove a pair that has a word given in it
	void remove(const std::string& word);					

	// Edit definition of existed word
	void updateDef(const std::string& word, unsigned int type, const std::string& oldDef, const std::string& newDef);	

	// Find a definition for a required word	
	Word* searchDef(const std::string& word);

	//Random a word and its definition
	Word* randomWordOfDay();//				

	// Get the list of random k word-definition pairs
	std::vector<Word*> getRandom(int k);			
};

#endif
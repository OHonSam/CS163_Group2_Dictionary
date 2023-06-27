// THIS IS THE TEMPLATE COPIED FROM GOOGLE DOCS ONLY, WITH FUNCTION PROTOTYPE SUGGESTION, FOR EASY WORK

#pragma once
class HashTable
{
private:
	int numWords;
    
    // Buckets 2d vector initialized with size 1e6, approximately greater than the number of words
	std::vector<std::vector<std::pair<std::string,std::string>>> buckets;

	// Hash function
	int hash(const std::string& word);						

public:
	HashTable(): buckets(1000000) {}				

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
};


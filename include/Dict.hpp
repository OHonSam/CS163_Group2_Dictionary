class Dict
{
private:
	SLL history;
	HashTable wordDef;
	Trie words;
	BTree favList;

public:
	Dict(const string& path, bool isJson);				

	// Save data structures before deleting
	~Dict();										

	// Load from json file
	bool importJson(const string& path); 				

	// Load from binary file
	bool importBinary(const string& path); 				

	// Reset to the default dataset
	void reset();									

	// Edit definition of existed word
	void updateDef(const string& word, const string& newDef); 

	// Add a pair of word and definition
	void addWord(const string& word, const string& def);		

	// Add a word to the favorite list
	void addFav(const string& word);					

	// Add a word to the history
	void addHistory(const string& word);			

	// Remove a word and corresponding definition
	void removeWord(const string& word);				

 	// Remove a word from the favorite list
	void removeFav(const string& word);				

 	// Remove a word from the history
	void removeHistory(const string& word);				

	// Get the history in the vector
	vector<string> getHistory();						

	// Get the favorite list
	vector<string> getFav();						

   	// Return a definition for a required word
    string searchDef(const string& word); 			
	
	// Return the list of words which has an identical given prefix
	vector<string> searchPrefix(const string& prefix);		
};

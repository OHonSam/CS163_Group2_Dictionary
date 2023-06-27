// THIS IS THE TEMPLATE COPIED FROM GOOGLE DOCS ONLY, WITH FUNCTION PROTOTYPE SUGGESTION, FOR EASY WORK


class HashTable
{
private:
	int numWords;
    
    // Buckets 2d vector itialized with size 1e6, approximately greater than the number of words
	vector<vector<pair<string,string>>> buckets(1000000);

	// Hash function
	int hash(const string& word);						

public:
	HashTable();								

	void clear();									

	// Load from binary file
	bool import(const string& path);					

	// Save as binary file
	bool save(const string& path);						

	// Insert a pair of word and definition
	int insert(const string& word, const string& def);		
	
	// Remove a pair that has a word given in it
	void remove(const string& word);					

	// Edit definition of existed word
	void updateDef(const string& word, const string& newDef);	

	// Find a definition for a required word
	string searchDef(const string& word);				
};


// THIS IS THE TEMPLATE COPIED FROM GOOGLE DOCS ONLY, WITH FUNCTION PROTOTYPE SUGGESTION, FOR EASY WORK

const int ALPHABET_SIZE=26;

class Trie
{
private:
	struct Node
	{
		int numWords;
		bool isEnd;
		Node* child[ALPHABET_SIZE];
  	};

	Node* root;

	int getIndex(char c);
	int rGetIndex(int index);
	
public:
	Trie();			

	// Deallocate all nodes
	void clear();									

	// Load from binary file
	bool import(const string& path);					

	// Save as binary file
	bool save(const string& path);						

	// Insert a word in the trie
	void insert(const string& word);					

	// Remove a word out of trie
	void remove(const string& word);					
	
	// Check whether a word is in the trie
	bool check(const string& word);					

	// Returns a list of strings which have identical prefix
	vector<string> searchPrefix(const string& prefix);		

	// Get all the words that was embedded in the trie
	vector<string> getList();							
};


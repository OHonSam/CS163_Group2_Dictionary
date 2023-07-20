#ifndef TRIE_HPP
#define TRIE_HPP

#include <Libraries.hpp>

const int ALPHABET_SIZE = 26;
class Trie
{
private:
	const char TERMINATOR = '\0';

	struct Node
	{
		int numWords; // Number of words that have this prefix
		bool isEnd;
		Node *child[ALPHABET_SIZE];

		char c; // character contained in Node
		Node() : numWords(0), isEnd(false), c(' ')
		{
			for (int i = 0; i < ALPHABET_SIZE; ++i)
				child[i] = nullptr;
		}

		Node(char _c) : numWords(0), isEnd(false), c(_c)
		{
			for (int i = 0; i < ALPHABET_SIZE; ++i)
				child[i] = nullptr;
		}

		~Node()
		{
			for (int i = 0; i < ALPHABET_SIZE; ++i)
				if (child[i] != nullptr)
				{
					delete child[i];
				};
		}
	};

	Node *root;

	// Get the index from the given character in the alphabet
	int getIndex(char c); //
	// Get the character in the alphabet from the given index
	char rGetIndex(int index);

	void insert(Node *&root, const std::string &word, int index);
	void remove(Node *&root, const std::string &word, int index);

	void import(Node* &root, std::ifstream& file);
	void save(Node* root, std::ofstream& file);
	
public:
	Trie()
	{
		root = nullptr;
	}
	~Trie()
	{
		clear();
	}

	// Deallocate all nodes
	void clear();

	// Load from binary file
	bool import(const std::string &path);

	// Save as binary file
	bool save(const std::string &path);

	// Insert a word in the trie
	void insert(const std::string &word);

	// Remove a word out of trie
	void remove(const std::string &word);

	// Check whether a word is in the trie
	bool checkExist(const std::string &key); //

	// Returns a list of std::strings which have identical prefix
	std::vector<std::string> searchPrefix(const std::string &prefix); //
	void recursiveFind(std::vector<std::string> &res, std::string prefix, Trie::Node *cur, int &cnt);

	// Get all the words that was embedded in the trie
	// std::vector<std::string> getList();
};
#endif

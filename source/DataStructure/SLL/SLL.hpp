
#ifndef SLL_HPP
#define SLL_HPP
// SLL is Singly Linked List
#include "Word.hpp"
#include <Libraries.hpp>

template<class T>
class SLL
{
private:
	struct Node
	{
		T data;//SLL history is a list of nodes, each node contains a keyword (data)
		Node* next;
		Node(){
			next=nullptr;
		}
		Node(const T& val){
			data=val;
			next=nullptr;
		}
	};
	
	Node *head, *tail;

public:
	SLL();									
	~SLL();										
	// Deallocate all nodes
	void clearSLL();//
	// Delete history
	bool clearHistory(const std::string& path);

	// Load from a binary file
	bool importSLLStr(const std::string& path);				

	// Save to a binary file
	bool saveSLLStr(const std::string& path);						

	// Insert a value->limit to 20 history nodes 
	void push(const T& key);//	
	int countNodes(Node* head);			

	// Find a value
	bool find(const T& key);			

	// Remove a value
	void pop(const T& key);//		

	// Transform history SLL into history vector
	std::vector<T> SLLintoVector();

	// Check the existence of a word in the history SLL
	bool find(const T& key);

	// Display the history SLL in UI
	void display();	
};

#include <SLL.inl>

//convert characters from string str to array of char arr
// void StrToCharArr(char*& arr, const std::string& str, int len); 
#endif
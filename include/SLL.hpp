
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
		T data;//SLL history is a list of nodes, each node contains a keyword
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
	void clearHistory();//									

	// Load from a binary file
	bool import(const std::string& path);				

	// Save to a binary file
	bool save(const std::string& path);						

	// Insert a value->limit to 20 history nodes 
	void push(const T& key);//	
	int countNodes(Node* head);						

	// Remove a value
	void pop(const T& key);//						

	// Get the list of favorite words
	std::vector<T> getList();							
};
#include "..\include\SLL.inl"
#endif
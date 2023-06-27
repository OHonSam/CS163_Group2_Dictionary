// SLL is Singly Linked List
#pragma once

#include <string>
#include <vector>

template<class T>
class SLL
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node();
		Node(const T& val);
	};

	Node *head, *tail;

public:
	SLL();									
	~SLL();										

	void clear();									

	// Load from a binary file
	bool import(const std::string& path);				

	// Save to a binary file
	bool save(const std::string& path);						

	// Insert a value
	void push(const T& val);							

	// Remove a value
	void pop(const T& val);							

	// Remove a value
	std::vector<T> getList();							
};



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
	void clearSLL();//
	// Delete history
	bool clearHistory(const std::string& path);

	// Load from a binary file
	bool importSLLStr(const std::string& path, std::ifstream& fin);				

	// Save to a binary file
	bool saveSLLStr(const std::string& path, std::ofstream& fout);						

	// Insert a value->limit to 20 history nodes 
	void push(const T& key);//	
	int countNodes(Node* head);						

	// Remove a value
	void pop(const T& key);//						

	// Get the list of favorite words
	//std::vector<T> getList();

	void display() {
        Node* cur = head;
        while (cur != nullptr) {
            std::cout << cur->data << " ";
            cur = cur->next;
        }
    }							
};
//convert characters from string str to array of char arr
void StrToCharArr(char*& arr, const std::string& str, int len); 
#include <SLL.inl>
#endif
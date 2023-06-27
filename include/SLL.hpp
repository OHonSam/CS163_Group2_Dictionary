// SLL is Singly Linked List

template<class T>
class SLL
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

	Node *head, *tail;

public:
	SLL();									
	~SLL();										

	void clear();									

	// Load from a binary file
	bool import(const string& path);				

	// Save to a binary file
	bool save(const string& path);						

	// Insert a value
	void push(const T& val);							

	// Remove a value
	void pop(const T& val);							

	// Remove a value
	vector<T> getList();							
};


#ifndef BTREE_HPP
#define BTREE_HPP

class TreeNode
{
	int *keys;
	int minimum_degree;
	TreeNode **Children;
	int order;
	bool leaf;

public:
	TreeNode(int temp, bool bool_leaf);

	void insertNonFull(int k);
	void splitChild(int i, TreeNode *y);
	void traverse();

	TreeNode *search(int k);

	friend class BTree;
};

class BTree
{
	TreeNode *root;
	int minimum_degree;

public:
	BTree(int temp);

	void traverse();

	TreeNode *search(int k);
	void insert(int k);

	~BTree();
};
#endif

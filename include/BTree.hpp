#ifndef BTREE_HPP
#define BTREE_HPP
#include "Word.hpp"
#include "Libraries.hpp"

class TreeNode
{
	int minDeg;
	bool leaf;
	int *keys;
	TreeNode **Children;
	int numNode;

	void insertNonFull(int k);
	void splitChild(int i, TreeNode *y);
	void traverse();

	TreeNode *search(int k);

	void deletion(int k);
	int findKey(int k);
	void removeFromLeaf(int idx);
	void removeFromNonLeaf(int idx);
	int getPredecessor(int idx);
	int getSuccessor(int idx);
	void fill(int idx);
	void borrowFromPrev(int idx);
	void borrowFromNext(int idx);
	void merge(int idx);

public:
	TreeNode(int temp, bool bool_leaf);
	~TreeNode();

	friend class BTree;
};

class BTree
{
	TreeNode *root;
	int minDeg;

public:
	BTree(int minDeg1);
	~BTree();

	void traverse();

	TreeNode *search(int k);
	void insert(int k);

	void deletion(int k);
};
#endif
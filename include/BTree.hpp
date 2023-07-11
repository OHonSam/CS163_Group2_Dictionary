#ifndef BTREE_HPP
#define BTREE_HPP

class TreeNode
{
	int *keys;
	int minDeg;
	TreeNode **Children;
	int deg;
	bool leaf;

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

#include "Word.hpp"
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
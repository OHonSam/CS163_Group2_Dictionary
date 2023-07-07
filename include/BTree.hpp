#ifndef BTREE_HPP
#define BTREE_HPP
class BTree
{
	BTree** root;
	int* children;


public:
	BTree();
	~BTree();
};
#endif
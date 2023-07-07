#include "Libraries.hpp"
#include "BTree.hpp"

BTree::BTree(int temp)
{
  root = NULL;
  minimum_degree = temp;
}


BTree::~BTree()
{
  int i;
  for (i = 0; i < order; i++)
  {
    if (leaf == false)
      Children[i]->traverse();
    delete keys[i];
  }

  if (leaf == false)
    Children[i]->traverse();
}

TreeNode *BTree::search(int k)
{
  return (root == NULL) ? NULL : root->search(k);
}

void BTree::traverse()

{
  if (root != NULL)
    root->traverse();
}

TreeNode::TreeNode(int t1, bool leaf1)
{
  minimum_degree = t1;
  leaf = leaf1;

  keys = new int[2 * minimum_degree - 1];
  Children = new TreeNode *[2 * minimum_degree];

  order = 0;
}

void TreeNode::traverse()
{
  int i;
  for (i = 0; i < order; i++)
  {
    if (leaf == false)
      Children[i]->traverse();
    std::cout << " " << keys[i];
  }

  if (leaf == false)
    Children[i]->traverse();
}

TreeNode *TreeNode::search(int k)
{
  int i = 0;
  while (i < order && k > keys[i])
    i++;

  if (keys[i] == k)
    return this;

  if (leaf == true)
    return NULL;

  return Children[i]->search(k);
}

void BTree::insert(int k)
{
  if (root == NULL)
  {
    root = new TreeNode(minimum_degree, true);
    root->keys[0] = k;
    root->order = 1;
  }
  else
  {
    if (root->order == 2 * minimum_degree - 1)
    {
      TreeNode *s = new TreeNode(minimum_degree, false);

      s->Children[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->Children[i]->insertNonFull(k);

      root = s;
    }
    else
      root->insertNonFull(k);
  }
}

void TreeNode::insertNonFull(int k)
{
  int i = order - 1;

  if (leaf == true)
  {
    while (i >= 0 && keys[i] > k)
    {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    order = order + 1;
  }
  else
  {
    while (i >= 0 && keys[i] > k)
      i--;

    if (Children[i + 1]->order == 2 * minimum_degree - 1)
    {
      splitChild(i + 1, Children[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    Children[i + 1]->insertNonFull(k);
  }
}

void TreeNode::splitChild(int i, TreeNode *y)
{
  TreeNode *z = new TreeNode(y->minimum_degree, y->leaf);
  z->order = minimum_degree - 1;

  for (int j = 0; j < minimum_degree - 1; j++)
    z->keys[j] = y->keys[j + minimum_degree];

  if (y->leaf == false)
  {
    for (int j = 0; j < minimum_degree; j++)
      z->Children[j] = y->Children[j + minimum_degree];
  }

  y->order = minimum_degree - 1;
  for (int j = order; j >= i + 1; j--)
    Children[j + 1] = Children[j];

  Children[i + 1] = z;

  for (int j = order - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[minimum_degree - 1];
  order = order + 1;
}
#include "Libraries.hpp"
#include "BTree.hpp"

TreeNode::TreeNode(int minDeg1, bool leaf1)
{
  minDeg = minDeg1;
  leaf = leaf1;

  keys = new int[2 * minDeg - 1];
  Children = new TreeNode *[2 * minDeg];

  numNode = 0;
}

BTree::BTree(int minDeg1)
{
  root = nullptr;
  minDeg = minDeg1;
}

BTree::~BTree()
{
  if (root != nullptr)
  {
    delete root;
    root = nullptr;
  }
}

TreeNode::~TreeNode()
{
    delete []keys;
    keys = nullptr;

    if (Children != nullptr) {
      for (int i = 0; i <= numNode; ++i)
      {
        if (Children[i] != nullptr) {
          delete Children[i];
        }
      }

      delete []Children;
      Children = nullptr;
    }
}

TreeNode *BTree::search(int k)
{
  return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::traverse()
{
  if (root != nullptr)
    root->traverse();
}

void TreeNode::traverse()
{
  int i;
  for (i = 0; i < numNode; i++)
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
  while (i < numNode && k > keys[i])
    i++;

  if (keys[i] == k)
    return this;

  if (leaf == true)
    return nullptr;

  return Children[i]->search(k);
}

void BTree::insert(int k)
{
  if (root == nullptr)
  {
    root = new TreeNode(minDeg, true);
    root->keys[0] = k;
    root->numNode = 1;
  }
  else
  {
    if (root->numNode == 2 * minDeg - 1)
    {
      TreeNode *s = new TreeNode(minDeg, false);

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
  int i = numNode - 1;

  if (leaf == true)
  {
    while (i >= 0 && keys[i] > k)
    {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    numNode = numNode + 1;
  }
  else
  {
    while (i >= 0 && keys[i] > k)
      i--;

    if (Children[i + 1]->numNode == 2 * minDeg - 1)
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
  TreeNode *z = new TreeNode(y->minDeg, y->leaf);
  z->numNode = minDeg - 1;

  for (int j = 0; j < minDeg - 1; j++)
    z->keys[j] = y->keys[j + minDeg];

  if (y->leaf == false)
  {
    for (int j = 0; j < minDeg; j++)
      z->Children[j] = y->Children[j + minDeg];
  }

  y->numNode = minDeg - 1;
  for (int j = numNode; j >= i + 1; j--)
    Children[j + 1] = Children[j];

  Children[i + 1] = z;

  for (int j = numNode - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[minDeg - 1];
  numNode = numNode + 1;
}

void BTree::deletion(int k)
{
  if (!root)
  {
    std::cout << "The tree is empty\n";
    return;
  }

  root->deletion(k);

  if (root->numNode == 0)
  {
    TreeNode *tmp = root;
    if (root->leaf)
      root = NULL;
    else
      root = root->Children[0];
    delete tmp;
  }
  return;
}

int TreeNode::findKey(int k)
{
  int idx = 0;
  while (idx < numNode && keys[idx] < k)
    ++idx;
  return idx;
}

void TreeNode::deletion(int k)
{
  int idx = findKey(k);

  if (idx < numNode && keys[idx] == k)
  {
    if (leaf)
      removeFromLeaf(idx);
    else
      removeFromNonLeaf(idx);
  }
  else
  {
    if (leaf)
    {
      std::cout << "The key " << k << " does not exist in the tree\n";
      return;
    }

    bool flag = ((idx == numNode) ? true : false);

    if (Children[idx]->numNode < minDeg)
      fill(idx);

    if (flag && idx > numNode)
      Children[idx - 1]->deletion(k);
    else
      Children[idx]->deletion(k);
  }
  return;
}

void TreeNode::removeFromLeaf(int idx)
{
  for (int i = idx + 1; i < numNode; ++i)
    keys[i - 1] = keys[i];

  numNode--;

  return;
}

// Delete from non leaf node
void TreeNode::removeFromNonLeaf(int idx)
{
  int k = keys[idx];

  if (Children[idx]->numNode >= minDeg)
  {
    int pred = getPredecessor(idx);
    keys[idx] = pred;
    Children[idx]->deletion(pred);
  }

  else if (Children[idx + 1]->numNode >= minDeg)
  {
    int succ = getSuccessor(idx);
    keys[idx] = succ;
    Children[idx + 1]->deletion(succ);
  }

  else
  {
    merge(idx);
    Children[idx]->deletion(k);
  }
  return;
}

int TreeNode::getPredecessor(int idx)
{
  TreeNode *cur = Children[idx];
  while (!cur->leaf)
    cur = cur->Children[cur->numNode];

  return cur->keys[cur->numNode - 1];
}

int TreeNode::getSuccessor(int idx)
{
  TreeNode *cur = Children[idx + 1];
  while (!cur->leaf)
    cur = cur->Children[0];

  return cur->keys[0];
}

void TreeNode::fill(int idx)
{
  if (idx != 0 && Children[idx - 1]->numNode >= minDeg)
    borrowFromPrev(idx);

  else if (idx != numNode && Children[idx + 1]->numNode >= minDeg)
    borrowFromNext(idx);

  else
  {
    if (idx != numNode)
      merge(idx);
    else
      merge(idx - 1);
  }
  return;
}

void TreeNode::borrowFromPrev(int idx)
{
  TreeNode *child = Children[idx];
  TreeNode *sibling = Children[idx - 1];

  for (int i = child->numNode - 1; i >= 0; --i)
    child->keys[i + 1] = child->keys[i];

  if (!child->leaf)
  {
    for (int i = child->numNode; i >= 0; --i)
      child->Children[i + 1] = child->Children[i];
  }

  child->keys[0] = keys[idx - 1];

  if (!child->leaf)
    child->Children[0] = sibling->Children[sibling->numNode];

  keys[idx - 1] = sibling->keys[sibling->numNode - 1];

  child->numNode += 1;
  sibling->numNode -= 1;

  return;
}

void TreeNode::borrowFromNext(int idx)
{
  TreeNode *child = Children[idx];
  TreeNode *sibling = Children[idx + 1];

  child->keys[(child->numNode)] = keys[idx];

  if (!(child->leaf))
    child->Children[(child->numNode) + 1] = sibling->Children[0];

  keys[idx] = sibling->keys[0];

  for (int i = 1; i < sibling->numNode; ++i)
    sibling->keys[i - 1] = sibling->keys[i];

  if (!sibling->leaf)
  {
    for (int i = 1; i <= sibling->numNode; ++i)
      sibling->Children[i - 1] = sibling->Children[i];
  }

  child->numNode += 1;
  sibling->numNode -= 1;

  return;
}

void TreeNode::merge(int idx)
{
  TreeNode *child = Children[idx];
  TreeNode *sibling = Children[idx + 1];

  child->keys[minDeg - 1] = keys[idx];

  for (int i = 0; i < sibling->numNode; ++i)
    child->keys[i + minDeg] = sibling->keys[i];

  if (!child->leaf)
  {
    for (int i = 0; i <= sibling->numNode; ++i)
      child->Children[i + minDeg] = sibling->Children[i];
  }

  for (int i = idx + 1; i < numNode; ++i)
    keys[i - 1] = keys[i];

  for (int i = idx + 2; i <= numNode; ++i)
    Children[i - 1] = Children[i];

  child->numNode += sibling->numNode + 1;
  numNode--;

  delete (sibling);
  return;
}
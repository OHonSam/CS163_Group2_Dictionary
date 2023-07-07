#include "Libraries.hpp"
#include "BTree.hpp"

BTree::BTree(int temp)
{
  root = nullptr;
  minDeg = temp;
}

TreeNode::~TreeNode()
{
  int i;
  for (i = 0; i < deg; i++)
  {
    if (leaf == false)
      Children[i]->traverse();

    if (keys == nullptr)
    {
      continue;
    }

    delete[] keys;
    keys = nullptr;
  }

  if (leaf == false)
    Children[i]->traverse();
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

TreeNode::TreeNode(int minDeg1, bool leaf1)
{
  minDeg = minDeg1;
  leaf = leaf1;

  keys = new int[2 * minDeg - 1];
  Children = new TreeNode *[2 * minDeg];

  deg = 0;
}

void TreeNode::traverse()
{
  int i;
  for (i = 0; i < deg; i++)
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
  while (i < deg && k > keys[i])
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
    root->deg = 1;
  }
  else
  {
    if (root->deg == 2 * minDeg - 1)
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
  int i = deg - 1;

  if (leaf == true)
  {
    while (i >= 0 && keys[i] > k)
    {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    deg = deg + 1;
  }
  else
  {
    while (i >= 0 && keys[i] > k)
      i--;

    if (Children[i + 1]->deg == 2 * minDeg - 1)
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
  z->deg = minDeg - 1;

  for (int j = 0; j < minDeg - 1; j++)
    z->keys[j] = y->keys[j + minDeg];

  if (y->leaf == false)
  {
    for (int j = 0; j < minDeg; j++)
      z->Children[j] = y->Children[j + minDeg];
  }

  y->deg = minDeg - 1;
  for (int j = deg; j >= i + 1; j--)
    Children[j + 1] = Children[j];

  Children[i + 1] = z;

  for (int j = deg - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[minDeg - 1];
  deg = deg + 1;
}

void BTree::deletion(int k) {
  if (!root) {
    std::cout << "The tree is empty\n";
    return;
  }

  root->deletion(k);

  if (root->deg == 0) {
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
  while (idx < deg && keys[idx] < k)
    ++idx;
  return idx;
}

void TreeNode::deletion(int k)
{
  int idx = findKey(k);

  if (idx < deg && keys[idx] == k)
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

    bool flag = ((idx == deg) ? true : false);

    if (Children[idx]->deg < minDeg)
      fill(idx);

    if (flag && idx > deg)
      Children[idx - 1]->deletion(k);
    else
      Children[idx]->deletion(k);
  }
  return;
}

void TreeNode::removeFromLeaf(int idx)
{
  for (int i = idx + 1; i < deg; ++i)
    keys[i - 1] = keys[i];

  deg--;

  return;
}

// Delete from non leaf node
void TreeNode::removeFromNonLeaf(int idx)
{
  int k = keys[idx];

  if (Children[idx]->deg >= minDeg)
  {
    int pred = getPredecessor(idx);
    keys[idx] = pred;
    Children[idx]->deletion(pred);
  }

  else if (Children[idx + 1]->deg >= minDeg)
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
    cur = cur->Children[cur->deg];

  return cur->keys[cur->deg - 1];
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
  if (idx != 0 && Children[idx - 1]->deg >= minDeg)
    borrowFromPrev(idx);

  else if (idx != deg && Children[idx + 1]->deg >= minDeg)
    borrowFromNext(idx);

  else
  {
    if (idx != deg)
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

  for (int i = child->deg - 1; i >= 0; --i)
    child->keys[i + 1] = child->keys[i];

  if (!child->leaf)
  {
    for (int i = child->deg; i >= 0; --i)
      child->Children[i + 1] = child->Children[i];
  }

  child->keys[0] = keys[idx - 1];

  if (!child->leaf)
    child->Children[0] = sibling->Children[sibling->deg];

  keys[idx - 1] = sibling->keys[sibling->deg - 1];

  child->deg += 1;
  sibling->deg -= 1;

  return;
}

void TreeNode::borrowFromNext(int idx)
{
  TreeNode *child = Children[idx];
  TreeNode *sibling = Children[idx + 1];

  child->keys[(child->deg)] = keys[idx];

  if (!(child->leaf))
    child->Children[(child->deg) + 1] = sibling->Children[0];

  keys[idx] = sibling->keys[0];

  for (int i = 1; i < sibling->deg; ++i)
    sibling->keys[i - 1] = sibling->keys[i];

  if (!sibling->leaf)
  {
    for (int i = 1; i <= sibling->deg; ++i)
      sibling->Children[i - 1] = sibling->Children[i];
  }

  child->deg += 1;
  sibling->deg -= 1;

  return;
}

void TreeNode::merge(int idx)
{
  TreeNode *child = Children[idx];
  TreeNode *sibling = Children[idx + 1];

  child->keys[minDeg - 1] = keys[idx];

  for (int i = 0; i < sibling->deg; ++i)
    child->keys[i + minDeg] = sibling->keys[i];

  if (!child->leaf)
  {
    for (int i = 0; i <= sibling->deg; ++i)
      child->Children[i + minDeg] = sibling->Children[i];
  }

  for (int i = idx + 1; i < deg; ++i)
    keys[i - 1] = keys[i];

  for (int i = idx + 2; i <= deg; ++i)
    Children[i - 1] = Children[i];

  child->deg += sibling->deg + 1;
  deg--;

  delete (sibling);
  return;
}
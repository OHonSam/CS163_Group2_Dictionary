#include "Libraries.hpp"
#include "TST.hpp"

TSTNode *TSTNode::put(TSTNode *node, const std::string &str, int index)
{
    if (!node)
    {
        node = new TSTNode(str[index]);
    }

    if (node->c > str[index])
        node->left = put(node->left, str, index);
    else if (node->c < str[index])
        node->right = put(node->right, str, index);
    else if (index < str.size() - 1)
    {
        node->mid = put(node->mid, str, index + 1);
    }
    else
        node->is_end = true;

    return node;
}

TSTNode *TSTNode::get(TSTNode *node, const std::string &str, int index)
{
    if (node == NULL)
        return NULL;

    if (node->c > str[index])
        return get(node->left, str, index);
    if (node->c < str[index])
        return get(node->right, str, index);
    if (index < str.size() - 1)
        return get(node->mid, str, index + 1);
    return node;
}

void TST::deletion(const std::string &word)
{
    TSTNode *p = root->get(root, word, 0);
    root->is_end = false;
}

void TST::insert(const std::string &word)
{
    root = root->put(root, word, 0);
}

bool TST::search(const std::string &word)
{
    TSTNode *p = root->get(root, word, 0);

    return p && p->is_end;
}

bool TST::startsWith(const std::string &prefix)
{
    TSTNode *p = root->get(root, prefix, 0);

    return p != NULL;
}
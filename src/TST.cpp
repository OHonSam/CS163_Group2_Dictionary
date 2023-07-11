#include "TST.hpp"

TSTNode *TSTNode::insert(TSTNode *node, const std::string &str, int index)
{
    if (!node)
    {
        node = new TSTNode(str[index]);
    }
    else
    {
        if (node->c > str[index])
        {
            node->left = insert(node->left, str, index);
        }
        else if (node->c < str[index])
        {
            node->right = insert(node->right, str, index);
        }
        else if (index < str.size() - 1)
        {
            node->mid = insert(node->mid, str, index + 1);
        }
        else
            node->isEnd = true;
    }

    return node;
}

void TST::deletion(const std::string &word)
{
    TSTNode *p = root->get(root, word, 0);
    root->isEnd = false;
}

void TST::insert(const std::string &word)
{
    root = root->insert(root, word, 0);
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

bool TST::search(const std::string &word)
{
    TSTNode *p = root->get(root, word, 0);

    return p && p->isEnd;
}

bool TST::startsWith(const std::string &prefix)
{
    TSTNode *p = root->get(root, prefix, 0);

    return p != NULL;
}

bool TST::import(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
        return false;
    import(root, file);
    file.close();
    return true;
}

bool TST::save(const std::string &path)
{
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open())
        return false;
    save(root, file);
    file.close();
    return true;
}

void TST::import(TSTNode *&root, std::ifstream &file)
{
    if (root == nullptr)
        root = new TSTNode;
    file.read((char *)&root->numWords, sizeof(int));
    file.read((char *)&root->isEnd, sizeof(bool));
    int _c; // character read in binary file
    while (true)
    {
        file.read((char *)&_c, sizeof(char));
        if (_c == TERMINATOR)
            break;
        if (_c < root->c)
        {
            import(root->left, file);
        }
        else if (_c > root->c)
        {
            import(root->right, file);
        }
        else
        {
            import(root->mid, file);
        }
    }
}

void TST::save(TSTNode *root, std::ofstream &file)
{
    if (root == nullptr)
        return;
    file.write((char *)&root->numWords, sizeof(int));
    file.write((char *)&root->isEnd, sizeof(bool));
    char _c = root->c; // temporary storage of character contained in a TSTNode

    file.write((char *)&_c, sizeof(char));
    save(root->left, file);

    save(root->mid, file);

    save(root->right, file);

    char marker = TERMINATOR;
    file.write((char *)&marker, sizeof(char));
}

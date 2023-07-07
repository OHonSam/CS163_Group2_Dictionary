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
        node->isEnd = true;

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
    root->isEnd = false;
}

void TST::insert(const std::string &word)
{
    root = root->put(root, word, 0);
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

void TST::import(TSTNode *&node, std::ifstream &file)
{
    if (root == nullptr)
        root = new TSTNode;
    file.read((char *)&root->numWords, sizeof(int));
    file.read((char *)&root->isEnd, sizeof(bool));
    int _c;
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

void TST::save(TSTNode *node, std::ofstream &file)
{
    if (root == nullptr)
        return;
    file.write((char *)&root->numWords, sizeof(int));
    file.write((char *)&root->isEnd, sizeof(bool));
    char _c = root->c;

    file.write((char *)&_c, sizeof(char));
    if (_c < root->c)
    {
        save(root->left, file);
    }
    else if (_c > root->c)
    {
        save(root->right, file);
    }
    else
    {
        save(root->mid, file);
    }

    char marker = TERMINATOR;
    file.write((char *)&marker, sizeof(char));
}

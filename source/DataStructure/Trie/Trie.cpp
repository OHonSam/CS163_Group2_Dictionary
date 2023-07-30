#include <fstream>
#include <Trie.hpp>
int Trie::getIndex(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c == ' ')
        return ALPHABET_SIZE - 1;
    if (c == '-')
        return ALPHABET_SIZE - 2;
    return -1;
}
char Trie::rGetIndex(int index)
{
    if (index < 0 || index >= ALPHABET_SIZE)
        return '\0';
    if (index < 26)
        return index + 'a';
    if (index == ALPHABET_SIZE - 1)
        return ' ';
    if (index == ALPHABET_SIZE - 2)
        return '-';
    return '\0';
}

bool Trie::checkExist(const std::string &key)
{
    if (root == nullptr)
        return false;
    Trie::Node *cur = root;
    int n = key.size();
    for (int i = 0; i < n; ++i)
    {
        int index = getIndex(key[i]);
        if (cur->child[index] == nullptr)
            return false;
        cur = cur->child[index];
    }
    return (cur->isEnd);
}

void Trie::recursiveFind(std::vector<std::string> &res, std::string prefix, Trie::Node *cur, int &cnt)
{
    if (cnt == 20)
        return;
    if (cur->isEnd == true)
    {
        res.push_back(prefix);
        ++cnt;
        char c = prefix[prefix.size() - 1];
        if (cur->child[getIndex(c)] == nullptr)
            return;
        else
            recursiveFind(res, prefix + c, cur->child[getIndex(c)], cnt);
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (cur->child[i] != nullptr)
        {
            char c = rGetIndex(i);
            recursiveFind(res, prefix + c, cur->child[i], cnt);
        }
    }
}

std::vector<std::string> Trie::searchPrefix(const std::string &prefix)
{
    std::vector<std::string> res;
    Trie::Node *cur = root;
    int n = prefix.size();
    for (int i = 0; i < n; ++i)
    {
        int index = getIndex(prefix[i]);
        if (cur->child[index] == nullptr)
            return {};
        cur = cur->child[index];
    }
    // if(cur->isEnd) res.push_back(prefix);
    // cur is at the last character of prefix string
    int cnt = 0;
    recursiveFind(res, prefix, cur, cnt);

    return res;
}

void Trie::import(Node *&root, std::ifstream &file)
{
    if (root == nullptr)
        root = new Node;
    file >> root->numWords;
    file >> root->isEnd;
    char c;
    while (1)
    {
        file>>c;
        if (c == ';')
            break;
        int pos = getIndex(c);
        import(root->child[pos], file);
    }
}

void Trie::save(Node *root, std::ofstream &file)
{
    if (root == nullptr)
        return;
    file << root->numWords;
    file << root->isEnd;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->child[i] != nullptr)
        {
            char c = rGetIndex(i);
            file << c;
            save(root->child[i], file);
        }
    char marker = ';';
    file << marker;
}

void Trie::clear()
{
    if (root != nullptr)
    {
        delete root;
        root = nullptr;
    }
}

bool Trie::import(const std::string &path)
{
    std::ifstream file(path);
    if (!file.good() || !file.is_open())
        return false;
    import(root, file);
    file.close();
    return true;
}

bool Trie::save(const std::string &path)
{
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open())
        return false;
    save(root, file);
    file.close();
    return true;
}

void Trie::insert(Node *&root, const std::string &word, int index)
{

    if (root == NULL)
    {
        root = new Node(word[index - 1]);
    }

    root->numWords++;

    if (index == word.length())
    {
        root->isEnd = true;
        return;
    }
    else
    {
        int i = getIndex(word[index]);
        insert(root->child[i], word, index + 1);
    }
}

void Trie::remove(Node *&root, const std::string &word, int index)
{
    if (root == NULL)
        return;
    root->numWords--;

    if (index == word.length())
        root->isEnd = false;
    else
    {
        int i = getIndex(word[index]);
        remove(root->child[i], word, index + 1);
    }

    if (root->numWords == 0)
    {
        delete root;
        root = NULL;
    }
}

void Trie::remove(const std::string &word)
{
    remove(root, word, 0);
}

void Trie::insert(const std::string &word)
{
    insert(root, word, 0);
}
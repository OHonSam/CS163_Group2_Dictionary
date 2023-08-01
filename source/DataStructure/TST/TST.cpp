#include "TST.hpp"

void TST::clear()
{
    delete root;
    root = nullptr;
}

bool TST::clearFavList(const std::string& path){
    clear();
    std::ofstream fout;
    fout.open(path,std::ios::binary|std::ios::trunc);
    if(!fout.is_open())
        return false;
    fout.close();
    if(fout.bad())
        return false;
    return true;
}

void TST::insert(const std::string &word)
{
    recursiveInsert(root, word, 0);
}

void TST::recursiveInsert(TSTNode *&node, const std::string &str, int index)
{
    if (!node)
    {
        node = new TSTNode(str[index]);
    }

    if (node->c > str[index])
    {
        recursiveInsert(node->left, str, index);
    }
    else if (node->c < str[index])
    {
        recursiveInsert(node->right, str, index);
    }
    else
    {
        node->numWords++;
        if (index < str.size() - 1)
        {
            recursiveInsert(node->mid, str, index + 1);
        }
        else
        {
            node->isEnd = true;
        }
    }
}

void TST::remove(const std::string &word)
{
    remove(root, word, 0);
}

void TST::remove(TSTNode *&node, const std::string &str, int index)
{
    if (!node)
    {
        return;
    }

    if (node->c > str[index])
    {
        remove(node->left, str, index);
    }
    else if (node->c < str[index])
    {
        remove(node->right, str, index);
    }
    else
    {
        node->numWords--;
        if (index < str.size() - 1)
        {
            remove(node->mid, str, index + 1);
        }
        else
        {
            node->isEnd = false;
        }
    }
}

std::vector<std::string> TST::startWith(const std::string &prefix)
{
    std::vector<std::string> res;

    if (isStartedWith(prefix) == false)
    {
        return {};
    }

    TSTNode *start = getNodeLastChar(root, prefix, 0);

    int cnt = 0;

    if (start->mid == nullptr)
    {
        return {prefix};
    }
    traverse(res, start->mid, prefix, cnt);
    return res;
}

TSTNode *TST::getNodeLastChar(TSTNode *node, const std::string &str, int index)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->c > str[index])
    {
        return getNodeLastChar(node->left, str, index);
    }
    if (node->c < str[index])
    {
        return getNodeLastChar(node->right, str, index);
    }
    if (index < str.size() - 1)
    {
        return getNodeLastChar(node->mid, str, index + 1);
    }

    return node;
}

bool TST::wordExists(const std::string &word)
{
    if (root == nullptr)
    {
        return false;
    }

    TSTNode *p = getNodeLastChar(root, word, 0);

    return p && p->isEnd;
}

bool TST::isStartedWith(const std::string &prefix)
{
    TSTNode *p = getNodeLastChar(root, prefix, 0);

    return p != NULL;
}

bool TST::import(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file.good() || !file.is_open()) return false;
    if (file.peek() == std::ifstream::traits_type::eof()) 
        return true;
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
    char _c;
    file.read((char *)&_c, sizeof(char));

    if(_c == TERMINATOR) return;

    root = new TSTNode(_c);
    file.read((char *)&root->numWords, sizeof(int));
    file.read((char *)&root->isEnd, sizeof(bool));

    import(root->left, file);
    import(root->right, file);
    import(root->mid, file);
}

void TST::save(TSTNode *root, std::ofstream &file)
{
    if (!root) {
        file.write((char *)&TERMINATOR, sizeof(char));
        return;
    }

    file.write((char *)&(root->c), sizeof(char));
    file.write((char *)&root->numWords, sizeof(int));
    file.write((char *)&root->isEnd, sizeof(bool));
    // char _c = root->c; // temporary storage of character contained in a TSTNode

    save(root->left, file);
    save(root->right, file);
    save(root->mid, file);
}

std::vector<std::string> TST::traverse()
{
    std::vector<std::string> res;
    int cnt = 0;
    traverse(res, root, "", cnt);

    return res;
}

void TST::traverse(std::vector<std::string> &res, TSTNode *root, std::string str, int &cnt)
{
    if (cnt == LIMIT_NUM_OF_RESULTS_PREFIX_FAVLIST)
        return;

    if (root == nullptr)
        return;
    traverse(res, root->left, str, cnt);

    str = str + root->c;

    if (root->isEnd == true)
    {
        res.push_back(str);
    }

    traverse(res, root->mid, str, cnt);

    str = str.substr(0, str.length() - 1);

    traverse(res, root->right, str, cnt);
}

void TST::type2RemoveWord()
{
    std::string word;

    std::cout << "Please type in the word you want to remove: ";

    std::getline(std::cin, word, '\n');

    uppercase2Lowercase(word);

    remove(word);

    std::cout << "Removed successfully!\n";
}

void TST::type2InsertWord()
{
    std::string word;

    std::cout << "\nPlease type in the word you want to insert: ";

    std::getline(std::cin, word, '\n');

    uppercase2Lowercase(word);

    insert(word);

    std::cout << "\nInserted successfully!\n";
}

void TST::searchPrefix()
{
    std::string word;
    std::vector<std::string> res;
    int cnt = 0;

    std::cout << "Please type in the word you want to search: ";

    std::getline(std::cin, word, '\n');

    uppercase2Lowercase(word);

    res = startWith(word);

    std::cout << "The words that start with " << word << " are: \n";

    for (auto i : res)
    {
        std::cout << ++cnt << ". " << i << '\n';
    }

    std::cout << "\nThere are " << cnt << " words that start with " << word << '\n';
}

bool TST::treeExists()
{
    return !(root == nullptr);
}

void TST::uppercase2Lowercase(std::string &str)
{
    int len = str.size();
    for (int i = 0; i < len; ++i)
    {
        // if (str[i] >= 'A' && str[i] <= 'Z')
        // {
        //     str[i] -= 'A';
        //     str[i] += 'a';
        // }
        str[i] = std::tolower(str[i]);
    }
}
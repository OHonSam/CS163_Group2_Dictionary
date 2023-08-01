// #include "D:\cs163\CS163_Group2_Dictionary\include\SmallTrie.hpp"
#include <SmallTrie.hpp>

int SmallTrie::getIndex(char c)
{
    return c;
}

char SmallTrie::rGetIndex(int index)
{
    return char(index);
}

void SmallTrie::insert(const std::string& word) {
    Node* cur = SmallTrie::root;
    ++(cur -> numWords);
    for (int i = 0; i < word.size(); ++i) {
        int index = getIndex(word[i]);
        if (!cur -> child[index]) {
            cur -> child[index] = new Node();
            cur -> childNum.push_back(index);
        }
        ++(cur -> child[index] -> numWords);
        cur = cur -> child[index];
    }
    cur -> isEnd = true;
    return;
}

void SmallTrie::remove(const std::string& word) {
    remove(SmallTrie::root, word, 0);
    return;
}

void SmallTrie::remove(Node* &root, const std::string& word, int index) {
    // index initialized with 0, word's length = max index including root
    if (!root) return;
    --root -> numWords;
        
    if (index == word.length()) root -> isEnd = false;
    else
    {
        int i = getIndex(word[index]);
        remove(root -> child[i], word, index + 1);
    }
    
    if (root -> numWords == 0 && root != SmallTrie::root)
    {
        delete root;
        root = nullptr;
    }
    return;
}

bool SmallTrie::search(const std::string& word) {
    Node* cur = SmallTrie::root;
    for (int i = 0; i < word.size(); ++i) {
        int index = getIndex(word[i]);
        if (!cur -> child[index]) return false;
        cur = cur -> child[index];
    }
    return true;
}

std::vector<std::string> SmallTrie::keywords() {
    std::vector<std::string> res;
    get(res, SmallTrie::root, "");
    return res;
}

void SmallTrie::get(std::vector<std::string> &res, Node* root, std::string word) {
    if (root -> isEnd) res.push_back(word);
    for (int i = 0; i < root -> childNum.size(); i++) if (root -> child[root -> childNum[i]]) get(res, root -> child[root -> childNum[i]], word + rGetIndex(root -> childNum[i]));
    return;
}

void SmallTrie::deallocate(Node* &root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) deallocate(root -> child[i]);
    delete root;
    root = nullptr;
    return;
}

int SmallTrie::save(Node* root, std::ofstream &out) {
    out.write((char*) &root -> isEnd, sizeof (bool));
    out.write((char*) &root -> numWords, sizeof (int));
    std::vector <int> temp;
    for (int i = 0; i < root -> childNum.size(); i++) {
        if (root -> child[root -> childNum[i]]) temp.push_back(root -> childNum[i]);
    }
    int size = temp.size();
    out.write((char*) &size, sizeof (int));
    for (int i = 0; i < temp.size(); i++) out.write((char*) &temp[i], sizeof (int));
    int res = sizeof (bool) + 4*(size + 2);
    for (int i = 0; i < temp.size(); i++) res += save(root -> child[temp[i]], out);
    return res;
}

bool SmallTrie::import(Node* &root, std::ifstream &in, int read_space) {
    // if (!read_space) return false;
    if (!root) root = new Node();
    in.read((char*) &root -> isEnd, sizeof (bool));
    in.read((char*) &root -> numWords, sizeof (int));
    int size;
    in.read((char*) &size, sizeof (int));
    for (int i = 0; i < size; i++) {
        int temp;
        in.read((char*) &temp, sizeof (int));
        root -> childNum.push_back(temp);
    }
    // std::cout << read_space << '\n';
    for (int i = 0; i < root -> childNum.size(); i++) {
        // read_space = read_space - sizeof(bool) - sizeof(int) * (size + 2);
        import(root -> child[root -> childNum[i]], in, read_space);
    }
    return true;
}

void SmallTrie::clear() {
    deallocate(root);
}
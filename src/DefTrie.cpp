// #include <Libraries.hpp>
// #include <DefTrie.hpp>
// #include<Trie.hpp>

#include "D:\cs163\CS163_Group2_Dictionary\include\DefTrie.hpp"

int DefTrie::getIndex(char c)
{
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return -1;
}

char DefTrie::rGetIndex(int index)
{
    if (index < 0 || index >= ALPHABET_SIZE) return '\0';
    return index + 'a';
}

void DefTrie::remove(Node *&root, const std::string &word, const std::string &keyword, int index)
{
    // index initialized with 0, word's length = max index including root
    if (root == NULL) return;
    root->numWords--;
        
    if (index == word.length()) {
        for (int i = 0; i < root -> keywords.size(); i++)
        {
            if (root -> keywords[i] == keyword) root -> keywords.erase(root -> keywords.begin() + i); break;
        }
        if (!root -> keywords.size()) root -> isEnd = false;
    }
    else
    {
        int i = getIndex(word[index]);
        remove(root -> child[i], word, keyword, index + 1);
    }
    
    if (root -> numWords == 0)
    {
        if (root == DefTrie::root) return;
        delete root;
        root = nullptr;
    }
    return;
}

std::vector<std::string> DefTrie::defWord(const std::string def) {
    std::stringstream s(def);
    std::string word;
    std::vector <std::string> res;
    while (s >> word) res.push_back(word);
    return res;
}

void DefTrie::insert(const std::string& word, const std::string& def){
    Node* cur = DefTrie::root;
    for (int i = 0; i < def.size(); ++i) {
        int index = getIndex(def[i]);
        if (!cur -> child[index]) cur -> child[index] = new Node();
        ++cur -> child[index] -> numWords;
        cur = cur -> child[index];
    }
    cur -> isEnd = true;
    cur -> keywords.push_back(word);
    return;
}

void DefTrie::insert(Word* word) {
    for (int i = 0; i < POS::Count; i++) {
        if (word -> type & (1 << i)) {
            for (int j = 0; j < word -> def[i].size(); j++) {
                std::vector <std::string> defW;
                defW = defWord(word -> def[i][j]);
                for (int k = 0; k < defW.size(); k++) {
                    Node* cur = search(defW[k]);
                    bool flag = true;
                    if (cur) {
                        std::vector<std::string> defWk = getKeyWords(cur);
                        for (int l = 0; l < defWk.size() + 1; l++) {
                            if (defWk[l] == word -> word)  {
                                // hash keyword, but may cause space problem
                                // map word - keyword
                                flag = false; break;
                                }
                        }
                    }
                    if (flag) insert(word -> word, defW[k]);
                }
            }
        }
    }
    return;
}

void DefTrie::remove(Word* word) {
    for (int i = 0; i < POS::Count; i++) {
        if (word -> type & (1 << i)) {
            for (int j = 0; j < word -> def[i].size(); j++) {
                std::vector <std::string> defW;
                defW = defWord(word -> def[i][j]);
                for (int k = 0; k < defW.size(); k++) remove(DefTrie::root, defW[k], word -> word, 0);
            }
        }
    }
    return;
}

void DefTrie::deallocate(Node* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) deallocate(root -> child[i]);
    delete root;
    root = nullptr;
    return;
}

void DefTrie::clear() {
    deallocate(DefTrie::root);
    root = nullptr;
    return;
}

std::vector<std::string> DefTrie::searchPrefix(const std::string& prefix) {
    // buffer will have many of the prefixes, this function work on a fixed prefix
    std::vector<std::string> res;
    Node* cur = DefTrie::root;
    for (int i = 0; i < prefix.size(); ++i) {
        int index = getIndex(prefix[i]);
        if (!cur -> child[index]) return res;
        cur = cur -> child[index];
    }
    int cnt = 0;
    recursiveFind(res, prefix, cur, cnt);
    return res;
}

void DefTrie::recursiveFind(std::vector<std::string>& res, std::string prefix, DefTrie::Node* cur, int& cnt) {
    if (cnt == 20) return;
    if (cur -> isEnd == true) {
        res.push_back(prefix);
        cnt++;
    }
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if (cur -> child[i]) {
            char c = rGetIndex(i);
            recursiveFind(res, prefix + c, cur -> child[i], cnt);
        }
    }
    return;
}

std::vector<std::string> DefTrie::searchKeyWord(const std::string def) {
    std::vector<std::string> defW = defWord(def);
    std::vector<std::string> res;
    for (int i = 0; i < defW.size(); i++) {
        if (search(defW[i])) break; // not done
    }
    return res;
}

DefTrie::Node* DefTrie::search(const std::string defword) {
    Node* cur = DefTrie::root;
    if (!cur) return nullptr;
    for (int i = 0; i < defword.size(); ++i) {
        int index = getIndex(defword[i]);
        if (!cur -> child[index]) return nullptr;
        cur = cur -> child[index];
    }
    return cur;
}

std::vector<std::string> DefTrie::getKeyWords(DefTrie::Node* cur) {
    if (!cur) return {};
    return cur -> keywords;
}

void DefTrie::updateDef(const std::string& word, unsigned int type, const std::string& oldDef, const std::string& newDef) {
    Word* oldWord = new Word(word, 1, oldDef);
    remove(oldWord);
    Word* newWord = new Word(word, 1, newDef);
    insert(newWord);
    return;
}

// int main() {
//     DefTrie* d = new DefTrie();
//     Word* word = new Word();
//     word->word = "hello";
//     word->def[0].push_back("xin chao");
//     word->def[1].push_back("chao");
//     word->def[7].push_back("thu hut");
//     word->type = 131;
//     d -> insert(word);
//     std::vector<std::string> x = d -> getKeyWords(d -> search("chao"));
//     for (int i = 0; i < x.size(); i++) std::cout << x[i] << '\n';
//     x.clear();
//     if (x.size()) std::cout << "x is not clear";
//     x = d -> getKeyWords(d -> search("hut"));
//     for (int i = 0; i < x.size(); i++) std::cout << x[i] << '\n';
//     x.clear();
//     d -> remove(word);
//     d -> clear();
//     if (d -> root) std::cout << "not clear";
//     if (d -> search("hut")) {x = d -> getKeyWords(d -> search("hut")); std::cout <<"ye";}
//     for (int i = 0; i < x.size(); i++) std::cout << x[i] << 'x';
//     return 0;
// }
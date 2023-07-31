#include <Libraries.hpp>
#include <DefTrie.hpp>
#include <sstream>
// #include<Trie.hpp>

// #include "D:\cs163\CS163_Group2_Dictionary\include\DefTrie.hpp"

int DefTrie::getIndex(char c)
{
    return c;
}

char DefTrie::rGetIndex(int index)
{
    return char(index);
}

void DefTrie::remove(Node *&root, const std::string &word, const std::string &keyword, int index)
{
    // index initialized with 0, word's length = max index including root
    if (root == NULL) return;
    root -> numWords--;
        
    if (index == word.length()) {
        root -> st -> SmallTrie::remove(keyword);
        if (root -> st -> root -> numWords == 0) root -> isEnd = false;
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
    ++(cur -> numWords);
    for (int i = 0; i < def.size(); ++i) {
        int index = getIndex(def[i]);
        if (!cur -> child[index]) cur -> child[index] = new Node();
        ++(cur -> child[index] -> numWords);
        cur = cur -> child[index];
    }
    cur -> isEnd = true;
    cur -> st -> insert(word);
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
                    if (!cur || !cur -> st -> search(word -> word)) insert(word -> word, defW[k]);
                }
            }
        }
    }
    return;
}

void DefTrie::remove(Word* word) {
    SmallTrie* smalltrie = new SmallTrie();
    for (int i = 0; i < POS::Count; i++) {
        if (word -> type & (1 << i)) {
            for (int j = 0; j < word -> def[i].size(); j++) {
                std::vector <std::string> defW;
                defW = defWord(word -> def[i][j]);
                for (int k = 0; k < defW.size(); k++) {
                    if (!smalltrie -> search(defW[k])) {
                        remove(DefTrie::root, defW[k], word -> word, 0);
                        smalltrie -> insert(defW[k]);
                    }
                }
            }
        }
    }
    return;
}

void DefTrie::deallocate(Node* &root) {
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
    // std::vector<SmallTrie*> p;
    // SmallTrie* res;
    std::vector<std::string> res;
    Node* cur;
    cur = search(defW[0]);
    if (!cur) return {};
    res = cur -> st -> keywords();
    for (int i = 1; i < defW.size(); i++) {
        std::vector<std::string> temp;
        for (int j = 0; j < res.size(); j++) {
            cur = search(defW[i]);
            if (!cur) res = {};
            else {
                if (cur -> st -> search(res[j])) temp.push_back(res[j]);
            }
        }
        res.clear();
        res = temp;
        temp.clear();
        // if (cur) p.push_back(cur -> st);
        // if (p.size() == 2) {
        //     res = merge(p[0], p[1]);
        //     p.pop_back(); 
        //     p.pop_back();
        // }
    }
    return res; // -> keywords();
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
    return (cur -> st -> keywords());
}

void DefTrie::updateDef(Word* oldWord, Word* newWord) {
    remove(oldWord);
    insert(newWord);
    return;
}

SmallTrie* DefTrie::merge(SmallTrie* st1, SmallTrie* st2) {
    SmallTrie* res;
    res = new SmallTrie();
    merge(res, st1 -> root, st2 -> root, "");
    return res;
}

void DefTrie::merge(SmallTrie* &res, SmallTrie::Node* p1, SmallTrie::Node* p2, std::string keyword) {
    if (!p1 -> isRoot) if (p1 -> isEnd && !p2 -> isEnd) res -> insert(keyword);
    for (int i = 0; i < ALPHABET_SIZE; i++) if (p1 -> child[i] && p2 -> child[i]) merge(res, p1 -> child[i], p2 -> child[i], keyword + rGetIndex(i));
    return;
}

bool DefTrie::save(const std::string& path) {
    std::ofstream out(path, std::ios::out | std::ios::binary);
    if (!out.is_open()) return false;
    DefTrie::save(root, out);
    out.close();
    return true;
}

void DefTrie::save(Node* root, std::ofstream& out) {
    if (!root) return;
    out.write((char*) &root -> isEnd, sizeof (bool));
    out.write((char*) &root -> numWords, sizeof (int));
    out.seekp(4, std::ios::cur);
    int trans = SmallTrie::save(root -> st -> root, out);
    out.seekp(0 - 4 - trans, std::ios::cur);
    out.write((char*) &trans, sizeof (int));
    out.seekp(trans, std::ios::cur);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bool flag = true;
        if (root -> child[i]) {
            out.write((char*) &flag, sizeof (bool));
            save(root -> child[i], out);
        }
        else {
            flag = false;
            out.write((char*) &flag, sizeof (bool));
        }
    }
    return;
}

DefTrie::Node* DefTrie::import(const std::string& path) {
    // delete root;
    // root = nullptr;
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in.good() || !in.is_open()) return nullptr;
    if (in.peek() == std::ifstream::traits_type::eof()) 
        return root = new Node();
    import(root, in);
    return root;
}

void DefTrie::import(Node* &root, std::ifstream& in) {
    if (!root) root = new Node();
    in.read((char*) &root -> isEnd, sizeof (bool));
    in.read((char*) &root -> numWords, sizeof (int));
    int read_space;
    in.read((char*) &read_space, sizeof (int));
    SmallTrie::import(root -> st -> root, in, read_space);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bool flag;
        in.read((char*) &flag, sizeof (bool));
        if (flag) import(root -> child[i], in);
    }
    return;
}

// int main() {
//     DefTrie* d = new DefTrie();
//     Word* word = new Word();
//     word->word = "hello";
//     word->def[0].push_back("xin chao ban rat dep");
//     word->def[1].push_back("chao");
//     word->def[7].push_back("thu hut");
//     word->type = 131;
//     Word* word1 = new Word();
//     word1->word = "hellu";
//     word1->def[0].push_back("chao chao");
//     word1->def[1].push_back("xin dep");
//     word1->def[7].push_back("i love you");
//     word1->type = 131;
    // d -> insert(word);
    // d -> insert(word1);
    // d -> save("D:/cs163/CS163_Group2_Dictionary/ASSETS/DataStructure/default/DefTrie.bin");
//     d -> import("D:/cs163/CS163_Group2_Dictionary/ASSETS/DataStructure/default/DefTrie.bin");
//     d -> remove(word);
//     std::vector <std::string> test;
//     test = d -> searchKeyWord("thu hut");
//     for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
//     test = d -> searchPrefix("c");
//     for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
//     test = d -> searchKeyWord("chao");
//     for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
//     return 0;
// }
// int main() {
//     DefTrie* d = new DefTrie();
//     Word* word = new Word();
//     word->word = "hello";
//     word->def[0].push_back("xin chao ban rat dep");
//     word->def[1].push_back("chao");
//     word->def[7].push_back("thu hut");
//     word->type = 131;
//     Word* word1 = new Word();
//     word1->word = "hellu";
//     word1->def[0].push_back("chao chao");
//     word1->def[1].push_back("xin dep");
//     word1->def[7].push_back("i love you");
//     word1->type = 131;
//     d -> insert(word);
//     d -> insert(word1);
//     d -> remove(word);
//     std::vector <std::string> test;
    // test = d -> searchKeyWord("thu hut");
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // test = d -> searchPrefix("c");
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // test = d -> searchKeyWord("chao");
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // test = d -> searchKeyWord("chao");
    // std::cout << '\n';
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // test = d -> searchKeyWord("love");
    // std::cout << '\n';
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // test = d -> searchKeyWord("dep");
    // std::cout << '\n';
    // for (int i = 0; i < test.size(); i++) std::cout << test[i] << ' ';
    // std::vector<std::string> x = d -> getKeyWords(d -> search("chao"));
    // for (int i = 0; i < x.size(); i++) std::cout << x[i] << '\n';
    // x.clear();
    // if (x.size()) std::cout << "x is not clear";
    // x = d -> getKeyWords(d -> search("hut"));
    // for (int i = 0; i < x.size(); i++) std::cout << x[i] << '\n';
    // x.clear();
    // d -> remove(word);
    // d -> clear();
    // if (d -> root) std::cout << "not clear";
    // if (d -> search("hut")) {x = d -> getKeyWords(d -> search("hut")); std::cout <<"ye";}
    // for (int i = 0; i < x.size(); i++) std::cout << x[i] << 'x';
    // return 0;
// }
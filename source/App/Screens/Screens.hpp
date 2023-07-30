#ifndef SCREENS_HPP
#define SCREENS_HPP

#include "Dict.hpp"

// Screen
class Screen
{
private:
    bool checkStrOption(const std::string &str, int &choice);
    bool checkStrEng(std::string str);

protected:
    Dict *dict;

    void clearScr();

    int inputOption(
        int maxOption,
        const std::string &mess = "Your choice: ");
    std::string inputEngString(
        const std::string &mess = "Enter English word:");

public:
    Screen(Dict *dict) : dict(dict) {}
    virtual Screen *render() = 0;
};
//

// Home
class Home : public Screen
{
private:
    const std::vector<std::string> options = {
        "Searching",
        "Editing",
        "Viewing",
        "Daily word",
        "Reset to default",
        "Random",
        "Switch between dictionaries (English-Vietnamese, Vietnamese-English, English-English)",
        "Exit"};

public:
    Home(Dict *dict) : Screen(dict) {}
    Screen *render();
};
//-------------------------Parent: Home-------------------------------
class SearchScreen: public Screen
{
private:
    const std::vector<std::string> options = {
        "Search for (a) definiton(s)",
        "Search for (a) keyword(s)",
        "Back"
    };
public:
    SearchScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
class EditScreen: public Screen
{   
private: 
    const std::vector<std::string> options = {
        "Add a new word",
        "Edit a word",
        "Delete a word",
        "Add a word to your favorite list",
        "Remove a word from your favorite list",
        "Clear your favorite list",
        "Remove a word from your search history",
        "Delete all words in your search history",
        "Back"
    };
public:
    EditScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class ViewScreen: public Screen
{   
private:
    const std::vector<std::string> options = {
        "View your search history",
        "View your favourite list",
        "View word(s) starting with a prefix in your favourite list",
        "Back"
    };
public:
    ViewScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class DailyWordScreen: public Screen
{
private:
    const std::vector<std::string> options = {
        "Look for another word",
        "Back"
    };
public:
    DailyWordScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
//-------------------------End Parent: Home---------------------------

//-------------------------Parent: SearchScreen--------------------------------
class SearchForDefScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Search for definition(s) of the initial word",
        "Search for definition(s) of a word from the given list of prefixes",
        "Search for definition(s) of all words with the same prefix",
        "Back"
    };

public:
    SearchForDefScreen(Dict* dict) : Screen(dict){}
    Screen* render();
    bool displayPrefix(std::vector<std::string> &prefixes);
};

//-------------------------End Parent: SearchScreen---------------------------


//-------------------------Parent: SearchForDefScreen--------------------------------
class DisplayExactModeScreen: public Screen{
private:
    std::string word;//word user typed in
    const std::vector<std::string> options = {
        "Edit this word",
        "Remove this word",
        "Add this word to your favorite list",
        "Back"
    };
public:
    DisplayExactModeScreen(Dict* dict,const std::string& word) : Screen(dict) , word(word) {}
    Screen* render();
};
class Display1PrefixModeScreen: public Screen{
private:
    std::vector<std::string> prefixes;//word user typed in
    const std::vector<std::string> options = {
        "Edit this word",
        "Remove this word",
        "Add this word to your favorite list",
        "Back"
    };
public:
    Display1PrefixModeScreen(Dict* dict,const std::vector<std::string>& prefixes) : Screen(dict) , prefixes(prefixes) {}
    Screen* render();
};
class DisplayPrefixesModeScreen: public Screen{
private:
    std::vector<std::string> prefixes;//word user typed in
    const std::vector<std::string> options = {
        "Back"
    };
public:
    DisplayPrefixesModeScreen(Dict* dict,std::vector<std::string>& prefixes) : Screen(dict) , prefixes(prefixes){}
    Screen* render();
};
//-------------------------End Parent: SearchForDefScreen---------------------------

//-------------------------Parent: ViewScreen--------------------------------
class ViewHistoryScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Search for definition(s) of a word in your search history",
        "Remove a word in your search history",
        "Delete all words in your search history",
        "Back"
    };
public:
    ViewHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class ViewFavListScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Search for definition(s) of a word in your favourite list",
        "Remove a word from your favourite list",
        "Clear your search history",
        "Back"
    };
public:
    ViewFavListScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class SearchPrefixFavList : public Screen
{
    private:
    const std::vector<std::string> options = {
        "Back"
    };
public:
    SearchPrefixFavList(Dict *dict) : Screen(dict) {}
    Screen *render();
};


//-------------------------End Parent: ViewScreen---------------------------


//-------------------------Parent: ViewHistoryScreen--------------------------------
class Search1WordHistoryScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back"
    };
public:
    Search1WordHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

//-------------------------End Parent: ViewHistoryScreen---------------------------

//-------------------------Parent: ViewFavListScreen--------------------------------

class Search1WordFavListScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back"
    };
public:
    Search1WordFavListScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
//-------------------------End Parent: ViewFavListScreen---------------------------

//-------------------------Parent: EditScreen--------------------------------
class AddWordScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back"
    };
public:
    AddWordScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class EditWordScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back"
    };
public:
    EditWordScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
class EditSearchWordScreen: public Screen{
private:
    std::string word;//word user typed in
    const std::vector<std::string> options = {
        "Back to Search Screen",
        "Back to Edit Screen"
    };
public:
    EditSearchWordScreen(Dict* dict, const std::string& word) : Screen(dict), word(word) {}
    Screen* render();
};

class DeleteSearchWordScreen: public Screen{
private:
    std::string word;//word user typed in
    const std::vector<std::string> options = {
        "Back to Search Screen",
        "Back to Edit Screen"
    };
public:
    DeleteSearchWordScreen(Dict* dict, const std::string& word) : Screen(dict), word(word) {}
    Screen* render();
};

class DeleteWordScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back"
    };
public:
    DeleteWordScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
class Remove1WordHistoryScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back to View History Screen",
        "Back to Edit Screen"
    };
public:
    Remove1WordHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
class DeleteAllHistoryScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back to View History Screen",
        "Back to Edit Screen"
    };
public:
    DeleteAllHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class ClearFavListScreen: public Screen{
private:
    const std::vector<std::string> options = {
        // "Back to View History Screen",
        // "Back to Edit Screen"
    };
public:
    ClearFavListScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class Remove1WordFavListScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back to View Favourite List Screen",
        "Back to Edit Screen"
    };
public:
    Remove1WordFavListScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class Add1WordFavListScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Back to View Favourite List Screen",
        "Back to Edit Screen"
    };
public:
    Add1WordFavListScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class AddGivenWordFavListScreen: public Screen{
private:
    std::string word;
    std::vector<std::string> prefixes;
    const std::vector<std::string> options = {
        "Back to View Favourite List Screen",
        "Back to Edit Screen"
    };
public:
    AddGivenWordFavListScreen(Dict* dict, const std::string& w) : Screen(dict), word(w) {}
    AddGivenWordFavListScreen(Dict* dict, const std::vector<std::string>& prefix) : Screen(dict), prefixes(prefix) {}

    Screen* render();
};
//-------------------------End Parent: Edit---------------------------

#endif // SCREENS_HPP
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
        "Remove a word in your search history",
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
        "View your favorite words",
        "Back"
    };
public:
    ViewScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class FavListChoiceScreen : public Screen
{
private:
    const std::vector<std::string> options = {
        "Type in a word to insert it to your favorite list",
        "Type in a word to remove it from your favorite list",
        "Search prefix of words in your favorite list",
        "Go back to previous page"
    };

    const std::vector<std::string> options2 = {
        "Type in a word to insert it to your favorite list",
        "Go back to previous page"
    };

public:
    FavListChoiceScreen(Dict *dict) : Screen(dict) {}
    Screen *render();
};
//-------------------------End Parent: Home---------------------------

//-------------------------Parent: SearchScreen--------------------------------
class SearchForDefScreen: public Screen{
private:
    const std::vector<std::string> options = {
        "Search for definition(s) of the exact word",
        "Search for definition(s) of all words with the same prefix",
        "Back"
    };

public:
    SearchForDefScreen(Dict* dict) : Screen(dict){}
    Screen* render();
    bool displayPrefix(const std::string& word);
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
class DisplayPrefixModeScreen: public Screen{
private:
    std::string word;//word user typed in
    const std::vector<std::string> options = {
        "Back"
    };
public:
    DisplayPrefixModeScreen(Dict* dict,const std::string& word) : Screen(dict) , word(word){}
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
//-------------------------End Parent: Edit---------------------------


//----------------------Parent: FavListChoiceScreen--------------------------------------
class Type2RemoveWordFavListScreen : public Screen
{
public:
    Type2RemoveWordFavListScreen(Dict *dict) : Screen(dict) {}
    Screen *render();
};


class Type2InsertWordFavListScreen : public Screen
{
public:
    Type2InsertWordFavListScreen(Dict *dict) : Screen(dict) {}
    Screen *render();
};

class SearchPrefixFavList : public Screen
{
public:
    SearchPrefixFavList(Dict *dict) : Screen(dict) {}
    Screen *render();
};
//----------------------End Parent: FavListChoiceScreen--------------------------------------

#endif // SCREENS_HPP
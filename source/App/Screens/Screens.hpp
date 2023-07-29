#ifndef SCREENS_HPP
#define SCREENS_HPP

#include "Dict.hpp"

// Screen
class Screen
{
private:
    bool checkStrOption(const std::string &str, int &choice);
    bool checkStrEng(std::string& str);
    bool checkStrViet(std::string& str);

protected:
    Dict *dict;

    void clearScr();

    int inputOption(
        int maxOption,
        const std::string &mess = "Your choice: ");

    std::string inputEngString(
        const std::string &mess = "Enter English word:");

    std::string inputVietString(
        const std::string &mess = "Enter Vietnamese word:");

public:
    Screen(Dict *dict) : dict(dict) {}
    virtual Screen *render() = 0;
};
//

// HomeScreen
class HomeScreen : public Screen
{
private:
    const std::vector<std::string> options = {
        "Search",
        "View",
        "Edit",
        "Daily word",
        "Multile choices quiz",
        "Reset to default",
        "Switch datasets",
        "Exit"
    };

public:
    HomeScreen(Dict *dict) : Screen(dict) {}
    Screen *render();
};
//-------------------------Parent: HomeScreen-------------------------------
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
        "View definitions of a word user types in",
        "View possible keywords of a definition user types in",
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
        "Go back to previous page",
    };

    const std::vector<std::string> options2 = {
        "Type in a word to insert it to your favorite list",
        "Go back to previous page",
    };

public:
    FavListChoiceScreen(Dict *dict) : Screen(dict) {}
    Screen *render();
};

class MultiChoicesScreen: public Screen
{
private:
    const std::string ques="Options:";
    const std::vector<std::string> options={
        "1 word and 4 definitions",
        "1 definition and 4 words",
        "Back"
    };

public:
    MultiChoicesScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class SwitchDataSetScreen: public Screen
{
private:
    const std::vector<std::string> options = {
        "English - English",
        "English - Vietnamese",
        "Vietnamese - English",
        "Slang words",
        "Back"
    };

public:
    SwitchDataSetScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

//-------------------------End Parent: HomeScreen---------------------------

//-------------------------Parent: SearchScreen--------------------------------
class SearchForDefScreen: public Screen{
public:
    SearchForDefScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
    void displayPrefixMode(const std::string& word);
    void displayExactMode(const std::string& word);
};

//-------------------------End Parent: SearchScreen---------------------------


//-------------------------Parent: ViewScreen--------------------------------
class ViewHistoryScreen: public Screen{
public:
    ViewHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};


//-------------------------End Parent: ViewScreen---------------------------

//-------------------------Parent: EditScreen--------------------------------
class Remove1WordHistoryScreen: public Screen{
public:
    Remove1WordHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
class DeleteAllHistoryScreen: public Screen{
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

//-------------------------Parent: MultipleChoices--------------------------------

class OneWord4DefScreen: public Screen
{
public:
    OneWord4DefScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class OneDef4WordScreen: public Screen
{
public:
    OneDef4WordScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};

//-------------------------End Parent: MultipleChoices---------------------------


#endif // SCREENS_HPP
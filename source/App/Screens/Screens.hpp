#ifndef SCREENS_HPP
#define SCREENS_HPP

#include <Dict.hpp>

// Screen
class Screen
{
private:
    bool checkStrOption(const std::string& str, int& choice);
    bool checkStrEng(std::string str);

protected:
    Dict* dict;

    void clearScr();

    int inputOption(
        int maxOption,
        const std::string& mess="Your choice: "
    );
    std::string inputEngString(
        const std::string& mess="Enter English word:"
    );

public:
    Screen(Dict* dict) : dict(dict) {}
    virtual Screen* render() = 0;
};
//

// Home
class Home: public Screen
{
private:
    const std::vector<std::string> options = {
        "Searching",
        "Editing",
        "Viewing",
        "Reset to default",
        "Random",
        "Switch between dictionaries (English-Vietnamese, Vietnamese-English, English-English)",
        "Exit"
    };

public:
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
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
        "View definitions of a word user types in",
        "View possible keywords of a definition user types in",
        "Back"
    };
public:
    ViewScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};
//-------------------------End Parent: Home---------------------------

//-------------------------Parent: SearchScreen--------------------------------
class SearchForDefScreen: public Screen{
public:
    SearchForDefScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
    void displayPrefixMode(const std::string& word);
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


//-------------------------End Parent: EditScreen---------------------------

#endif // SCREENS_HPP
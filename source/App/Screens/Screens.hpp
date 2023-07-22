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
class Edit: public Screen
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
    Edit(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class View: public Screen
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
    View(Dict* dict) : Screen(dict) {}
    Screen* render();
};
//-------------------------End Parent: Home---------------------------


//-------------------------Parent: View--------------------------------
class ViewHistoryScreen: public Screen{
public:
    ViewHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};


//-------------------------End Parent: View---------------------------

//-------------------------Parent: Edit--------------------------------
class Remove1WordHistoryScreen: public Screen{
public:
    Remove1WordHistoryScreen(Dict* dict) : Screen(dict) {}
    Screen* render();
};


//-------------------------End Parent: Edit---------------------------

#endif // SCREENS_HPP
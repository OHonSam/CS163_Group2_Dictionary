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

    void clear();

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
//


//----------------------Parent: Home--------------------------------------
class FavListChoiceScreen: public Screen
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
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
};
//----------------------Parent: Home-------------end-------------------------


//----------------------Parent: FavListChoiceScreen--------------------------------------
class Type2RemoveWordFavListScreen: public Screen
{
public:
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class Type2InsertWordFavListScreen: public Screen
{
public:
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class SearchPrefixFavList: public Screen
{
public:
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class InsertWordFavListScreen: public Screen
{
public:
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
};

class RemoveWordFavListScreen: public Screen
{
public:
    Home(Dict* dict) : Screen(dict) {}
    Screen* render();
};

//----------------------Parent: FavListChoiceScreen-------------end-------------------------


#endif // SCREENS_HPP
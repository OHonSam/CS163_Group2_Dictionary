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
// View
class View: public Screen
{   
private:
    const std::vector<std::string> options = {
        "View your search history",
        "View your favorite words",
        "View definitions of a given word",
        "View possible keywords of a given definition",
        "Back"
    };
public:
    View(Dict* dict) : Screen(dict) {}
    Screen* render();
};
// View search history
class ViewHistoryScreen: public Screen{
    Screen* render();
};
// View favorite words
#endif // SCREENS_HPP
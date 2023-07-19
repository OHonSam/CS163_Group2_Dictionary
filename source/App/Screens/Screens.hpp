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
    bool isEnd;
    Dict* dict;

    int inputOption(
        int maxOption,
        const std::string& mess="Your choice: "
    );

    std::string inputEngString(
        const std::string& mess="Enter English word:"
    );

public:
    Screen(Dict* dict) : dict(dict), isEnd(false) {}
    virtual Screen* render() = 0;
    bool getIsEnd() const { return isEnd; }
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

#endif // SCREENS_HPP
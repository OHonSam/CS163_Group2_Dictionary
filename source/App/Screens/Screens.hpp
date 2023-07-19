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

    int inputOption(int maxOption);
    std::string inputEngString();

public:
    Screen(Dict* dict) : dict(dict), isEnd(false) {}
    virtual void render() = 0;
    bool getIsEnd() const { return isEnd; }
};
//

// Home
class Home: public Screen
{
public:
    Home(Dict* dict) : Screen(dict) {}
    void render();
};
//

#endif // SCREENS_HPP
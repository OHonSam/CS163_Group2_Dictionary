#ifndef SCREENS_HPP
#define SCREENS_HPP

#include <Dict.hpp>

class Screen
{
protected:
    bool isEnd;
    Dict* dict;

public:
    Screen(Dict* dict)
    {
        this->dict = dict;
        isEnd = false;
    }

    virtual void render() = 0;
};

#endif // SCREENS_HPP
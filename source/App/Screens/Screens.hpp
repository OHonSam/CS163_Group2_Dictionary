#ifndef SCREENS_HPP
#define SCREENS_HPP

#include <Dict.hpp>

// Screen
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
    bool getIsEnd() const { return isEnd; }
};
//

#endif // SCREENS_HPP
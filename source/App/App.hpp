#ifndef APP_HPP
#define APP_HPP

#include <Screens.hpp>
#include <iostream>

// App class

class App
{
private:
    Dict dict;
	Screen* CurrentScreen;

public:
	App();

	void run();
};

#endif
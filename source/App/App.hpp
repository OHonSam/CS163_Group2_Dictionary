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
	App()
	{
		// CurrentScreen = new Home();
	}
};

// void SetNextScreen(App* app, Screen* NextScreen); 
// void Render(App* app, Screen* s);

// void Run();
// void EndApp(State* state);

#endif
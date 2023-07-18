#ifndef APP_H
#define APP_H

#include "TST.hpp"

class App;

class State
{
public:
	int userChoice;
	bool EndApp;
	std::string word;

	State() : word{}, userChoice{-1}, EndApp{false} {};
};
class Screen
{
public:
	virtual void Render(App *app) = 0;
};

class FirstScreen : public Screen
{
	void Render(App *app) override;
};


//--------------------------------Parent: FirstScreen-------------------------------------

class FavListChoiceScreen : public Screen
{
	void Render(App *app) override;
};
// class SearchScreen : public Screen
// {
// 	void Render(App *app) override;
// };
class ViewHistoryScreen : public Screen
{
	void Render(App *app) override;
};
//--------------------------------Parent: FirstScreen-------end-------------------------------

//--------------------------------Parent: ViewHistoryScreen--------------------------------------


//--------------------------------Parent: ViewHistoryScreen------end-----------------------------



//--------------------------------Parent: FavListChoiceScreen--------------------------------------

class Type2RemoveWordFavListScreen : public Screen
{
	void Render(App *app) override;
};

class Type2InsertWordFavListScreen : public Screen
{
	void Render(App *app) override;
};

class searchPrefixFavList : public Screen
{
	void Render(App *app) override;
};

//--------------------------------Parent: FavListChoiceScreen--------end------------------------------




//--------------------------------untitled--------------------------------------
class RemoveWordFavListScreen : public Screen
{
	void Render(App *app) override;
};

class InsertWordFavListScreen : public Screen
{
	void Render(App *app) override;
};
//--------------------------------untitled-----------end---------------------------


class App
{
public:
	State state;
	Screen *CurrentScreen;

	App()
	{
		CurrentScreen = new FirstScreen();
	}
};

void SetNextScreen(App *app, Screen *NextScreen);

void ClearScreen();
bool CheckString(std::string str, int &i);
void Render(App *app, Screen *s);

void Run();
void EndApp(App *app);

#endif
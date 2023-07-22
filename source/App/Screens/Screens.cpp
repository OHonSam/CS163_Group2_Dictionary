#include "Screens.hpp"

// Screen
bool Screen::checkStrOption(const std::string &str, int &choice)
{
	int length = str.size();
	if (length > 10 || length == 0)
		return false;

	for (int j = 0; j < length; ++j)
		if (str[j] < '0' || str[j] > '9')
			return false;

	if (length == 10 && str > std::to_string(INT_MAX))
		return false;

	choice = stoi(str);
	return true;
}

bool Screen::checkStrEng(std::string str)
{
	int length = str.size();
	if (length > 100 || length == 0)
		return false;

	for (char &c : str)
		if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';

	for (int j = 0; j < length; ++j)
		if (str[j] < 'a' || str[j] > 'z')
			return false;

	return true;
}

void Screen::clearScr()
{
#if defined _WIN32
	system("cls");
	// clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	// std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
	system("clear");
#endif
}

int Screen::inputOption(int maxOption, const std::string &mess)
{
	int option = maxOption;

	std::cout << mess;
	std::string str;
	std::getline(std::cin, str, '\n');
	while (!checkStrOption(str, option) || option < 1 || option > maxOption)
	{
		std::cout << "Invalid input. Please try again: ";
		std::getline(std::cin, str, '\n');
	}

	return option;
}

std::string Screen::inputEngString(const std::string &mess)
{
	std::string str;
	std::cout << mess;
	std::getline(std::cin, str, '\n');
	while (!checkStrEng(str))
	{
		std::cout << "Invalid input. Please try again: ";
		std::getline(std::cin, str, '\n');
	}

	return str;
}
//

// Home
Screen *Home::render()
{
	clearScr();

	std::cout << "Welcome to Dictionary!" << std::endl;
	int siz = options.size();
	for (int i = 0; i < siz; ++i)
		std::cout << std::to_string(i) << ". " << options[i] << std::endl;

	Screen *nextScreen = this; //"this"->own object
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		break;
	case 2:
		nextScreen = new EditScreen(dict);
	case 3:
		nextScreen = new ViewScreen(dict);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7: // Exit
		nextScreen = nullptr;
		break;
	}

	return nextScreen;
}
//-------------------------Parent: Home-------------------------------

Screen *ViewScreen::render()
{
	clearScr();
	for (int i = 0; i < options.size(); i++)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

	Screen *nextScreen = this; //"this"->own object
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewHistoryScreen(dict);
		break;
	case 2:
		break;
	case 3:
		// nextScreen=new Home(dict);
		break;
	case 4:
		break;
	case 5:
		nextScreen = new Home(dict);
		break;
	}
	return nextScreen;
}
Screen *EditScreen::render()
{
	clearScr();

	for (int i = 0; i < options.size(); i++)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

	Screen *nextScreen = this; //"this"->own object
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		//"Add a new word",
		break;
	case 2:
		//"Edit a word",
		break;
	case 3:
		//"Delete a word",
		break;
	case 4:
		//"Add a word to your favorite list",
		break;
	case 5:
		//"Remove a word from your favorite list",
		break;
	case 6:
		nextScreen = new Remove1WordHistoryScreen(dict);
		break;
	case 7:
		//"Delete all words in your search history",
		break;
	case 8:
		nextScreen = new Home(dict);
		break;
	}
	return nextScreen;
}

Screen *FavListChoiceScreen::render()
{
	clearScr();

	std::cout << "What would you like to do?\n"
			  << std::endl;
	int siz = options.size();
	for (int i = 0; i < siz; ++i)
		std::cout << std::to_string(i) << ". " << options[i] << std::endl;

	Screen *nextScreen = this;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		// SetNextScreen(app, new Type2InsertWordFavListScreen());
		break;
	case 2:
		// SetNextScreen(app, new Type2RemoveWordFavListScreen());
		break;
	case 3:
		// SetNextScreen(app, new SearchPrefixFavList());
		break;
	case 4:
		nextScreen = new Home(dict);
		break;
	}

	return nextScreen;
}
//-------------------------End Parent: Home---------------------------

//-------------------------Parent: ViewScreen-------------------------------
Screen *ViewHistoryScreen::render()
{
	clearScr();
	std::cout << "Your search history (20 most recent keywords):\n";
	std::vector<std::string> display = dict->getHistory();
	for (int i = 0; i < display.size(); ++i)
	{
		std::cout << display[i] << std::endl;
	}

	int cnt = 0;
	std::cout << ++cnt << ". Back" << std::endl;
	inputOption(cnt);
	return new ViewScreen(dict);
}

//-------------------------End Parent: ViewScreen-------------------------------

//-------------------------Parent: EditScreen-----------------------------------
Screen *Remove1WordHistoryScreen::render()
{
	clearScr();
	std::cout << "Enter the word you want to remove from your search history: ";
	std::string word;
	std::getline(std::cin, word);

	dict->removeHistory(word);

	std::cout << "The word has been successfully removed from your search history!\n";
	int cnt = 0;
	std::cout << ++cnt << ". Back" << std::endl;
	inputOption(cnt);
	return new EditScreen(dict);
}
Screen *DeleteAllHistoryScreen::render()
{
	clearScr();
	std::cout << "Are you sure that you want to delete your search history?\n";
	int cnt = 0;
	std::string buffer;
	std::cout << ++cnt << ". Yes\n";
	std::cout << ++cnt << ". No\n";
	int choice = inputOption(cnt);
	switch (choice)
	{
	case 1:
		if (dict->clearAllHistory("History.bin"))
			std::cout << "Your search history has been successfully deleted!\n";
		else
			std::cout << "Errors occurred in clearing time!\n";
		break;
	case 2:
		std::cout << "The deletion has been cancelled!\n";
		break;
	}

	cnt = 0;
	std::cout << ++cnt << ". Back" << std::endl;
	inputOption(cnt);
	return new EditScreen(dict);
}
//-------------------------End Parent: EditScreen-------------------------------

//----------------------Parent: FavListChoiceScreen-----------------------------
Screen *Type2RemoveWordFavListScreen::render()
{
	clearScr();

	std::cout << "What would you like to do?\n"
			  << std::endl;
	int siz = options.size();
	for (int i = 0; i < siz; ++i)
		std::cout << std::to_string(i) << ". " << options[i] << std::endl;

	Screen *nextScreen = this;
	int choice = inputOption(options.size());

	// dic
	// fix
	return new FavListChoiceScreen(dict);
}

// void Type2InsertWordFavListScreen::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state.userChoice << "\n";
// 	if (app->state.tst->treeExists())
// 	{
// 		app->state.tst->type2InsertWord();
// 	}
// 	else
// 	{
// 		app->state.tst->type2InsertWord();
// 		app->state.tst->save(FAV_LIST_SAVE_FILE);
// 	}

// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "\nEnter 0 to return to previous page\n";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// 	SetNextScreen(app, new FavListChoiceScreen());
// }

// void SearchPrefixFavList::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state.userChoice << "\n";
// 	app->state.tst->searchPrefix();
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "\nEnter 0 to return to previous page\n";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// 	SetNextScreen(app, new FavListChoiceScreen());
// }

// void InsertWordFavListScreen::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state.userChoice << "\n";
// 	app->state.tst->insert(app->state.word);
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "\nEnter 0 to return to previous page\n";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// 	// SetNextScreen(app, new FavListChoiceScreen());
// }

// void RemoveWordFavListScreen::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state.userChoice << "\n";
// 	app->state.tst->remove(app->state.word);
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "\nEnter 0 to return to previous page\n";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// 	// SetNextScreen(app, new FavListChoiceScreen());
// }

//----------------------End Parent: FavListChoiceScreen--------------------------------------

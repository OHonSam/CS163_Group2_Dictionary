#include "Screens.hpp"

// Screen
bool Screen::checkStrOption(const std::string &str, int& choice)
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

    for(char& c : str)
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';

    for (int j = 0; j < length; ++j)
        if (str[j] < 'a' || str[j] > 'z')
            return false;

    return true;
}

void Screen::clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif

}

int Screen::inputOption(int maxOption, const std::string &mess)
{
    int option=maxOption;

    std::cout<<"Your choice: ";
    std::string str; std::getline(std::cin, str, '\n');
    while (!checkStrOption(str, option) || option < 1 || option > maxOption)
    {
        std::cout<<"Invalid input. Please try again: ";
        std::getline(std::cin, str, '\n');
    }

    return option;
}

std::string Screen::inputEngString(const std::string& mess)
{
    std::string str;
    std::cout<<mess;
    std::getline(std::cin, str, '\n');
    while (!checkStrEng(str))
    {
        std::cout<<"Invalid input. Please try again: ";
        std::getline(std::cin, str, '\n');
    }

    return str;
}
//

// Home
Screen* Home::render()
{
    clear();

    std::cout<<"Welcome to Dictionary!"<<std::endl;
	int siz = options.size();
    for(int i=0; i<siz; ++i)
        std::cout<<std::to_string(i)<<". "<<options[i]<<std::endl;

    Screen* nextScreen=this;
    int choice=inputOption(options.size());
    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
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


void FavListChoiceScreen::Render(App *app)
{
	int choice = -1, minNumChoice = 1, maxNumChoice = 4, cnt = 0;
	std::string buffer;

	app->state.tst = new TST;

	if (app->state.tst->import(FAV_LIST_SAVE_FILE))
	{
		std::cout << "Your choice was: " << app->state.userChoice << "\n\n";
		std::cout << "What would you like to do?\n";
		// std::cout << ++cnt << ". Type in a word to insert it to your favorite list\n";
		// std::cout << ++cnt << ". Type in a word to remove it from your favorite list\n";
		// std::cout << ++cnt << ". Search prefix of words in your favorite list\n";
		// std::cout << ++cnt << ". Go back to previous page\n";

		std::getline(std::cin, buffer, '\n');

		while (!CheckString(buffer, choice) || choice < minNumChoice || choice > maxNumChoice)
		{
			std::cout << "The number you have entered does not correspond to any choice!\n";
			std::cout << "Please re-enter: ";
			std::getline(std::cin, buffer, '\n');
		}

		app->state.userChoice = choice;

		switch (choice)
		{
		case 1:
			SetNextScreen(app, new Type2InsertWordFavListScreen());
			break;
		case 2:
			SetNextScreen(app, new Type2RemoveWordFavListScreen());
			break;
		case 3:
			SetNextScreen(app, new SearchPrefixFavList());
			break;
		case 4:
			SetNextScreen(app, new FirstScreen());
			break;
		}
	}
	else
	{
		cnt = 0, maxNumChoice = 2;

		std::cout << "Your choice was: " << app->state.userChoice << "\n\n";
		std::cout << "What would you like to do?\n";
		std::cout << ++cnt << ". Type in a word to insert it to your favorite list\n";
		// std::cout << ++cnt << ". Type in a word to remove it from your favorite list\n";
		// std::cout << ++cnt << ". Search prefix of words in your favorite list\n";
		std::cout << ++cnt << ". Go back to previous page\n";

		std::getline(std::cin, buffer, '\n');

		while (!CheckString(buffer, choice) || choice < minNumChoice || choice > maxNumChoice)
		{
			std::cout << "The number you have entered does not correspond to any choice!\n";
			std::cout << "Please re-enter: ";
			std::getline(std::cin, buffer, '\n');
		}

		app->state.userChoice = choice;
		switch (choice)
		{
		case 1:
			SetNextScreen(app, new Type2InsertWordFavListScreen());
			break;
		case 2:
			SetNextScreen(app, new FirstScreen());
			break;
		}
	}
}

void Type2RemoveWordFavListScreen::Render(App *app)
{
	std::cout << "Your choice was: " << app->state.userChoice << "\n";

	if (app->state.tst->treeExists())
	{
		app->state.tst->type2RemoveWord();
	}
	else
	{
		std::cout << "No tree has been created so there's nothing to remove\n";
	}
	int choice = -1;
	std::string buffer;

	std::cout << "\nEnter 0 to return to previous page\n";
	std::getline(std::cin, buffer, '\n');

	while (!CheckString(buffer, choice) || choice != 0)
	{
		std::cout << "The number you have entered does not correspond to any choice!\n";
		std::cout << "Please re-enter: ";
		std::getline(std::cin, buffer, '\n');
	}

	SetNextScreen(app, new FavListChoiceScreen());
}

void Type2InsertWordFavListScreen::Render(App *app)
{
	std::cout << "Your choice was: " << app->state.userChoice << "\n";
	if (app->state.tst->treeExists())
	{
		app->state.tst->type2InsertWord();
	}
	else
	{
		app->state.tst->type2InsertWord();
		app->state.tst->save(FAV_LIST_SAVE_FILE);
	}

	int choice = -1;
	std::string buffer;

	std::cout << "\nEnter 0 to return to previous page\n";
	std::getline(std::cin, buffer, '\n');

	while (!CheckString(buffer, choice) || choice != 0)
	{
		std::cout << "The number you have entered does not correspond to any choice!\n";
		std::cout << "Please re-enter: ";
		std::getline(std::cin, buffer, '\n');
	}
	SetNextScreen(app, new FavListChoiceScreen());
}

void SearchPrefixFavList::Render(App *app)
{
	std::cout << "Your choice was: " << app->state.userChoice << "\n";
	app->state.tst->searchPrefix();
	int choice = -1;
	std::string buffer;

	std::cout << "\nEnter 0 to return to previous page\n";
	std::getline(std::cin, buffer, '\n');

	while (!CheckString(buffer, choice) || choice != 0)
	{
		std::cout << "The number you have entered does not correspond to any choice!\n";
		std::cout << "Please re-enter: ";
		std::getline(std::cin, buffer, '\n');
	}
	SetNextScreen(app, new FavListChoiceScreen());
}

void InsertWordFavListScreen::Render(App *app)
{
	std::cout << "Your choice was: " << app->state.userChoice << "\n";
	app->state.tst->insert(app->state.word);
	int choice = -1;
	std::string buffer;

	std::cout << "\nEnter 0 to return to previous page\n";
	std::getline(std::cin, buffer, '\n');

	while (!CheckString(buffer, choice) || choice != 0)
	{
		std::cout << "The number you have entered does not correspond to any choice!\n";
		std::cout << "Please re-enter: ";
		std::getline(std::cin, buffer, '\n');
	}
	// SetNextScreen(app, new FavListChoiceScreen());
}

void RemoveWordFavListScreen::Render(App *app)
{
	std::cout << "Your choice was: " << app->state.userChoice << "\n";
	app->state.tst->remove(app->state.word);
	int choice = -1;
	std::string buffer;

	std::cout << "\nEnter 0 to return to previous page\n";
	std::getline(std::cin, buffer, '\n');

	while (!CheckString(buffer, choice) || choice != 0)
	{
		std::cout << "The number you have entered does not correspond to any choice!\n";
		std::cout << "Please re-enter: ";
		std::getline(std::cin, buffer, '\n');
	}
	// SetNextScreen(app, new FavListChoiceScreen());
}

//

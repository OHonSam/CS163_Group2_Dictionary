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

int Screen::inputOption(int maxOption, const std::string& mess)
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
    std::cout<<"Welcome to Dictionary!"<<std::endl;
    for(int i=0; i<options.size(); i++)
        std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;

    Screen* nextScreen=new Home(dict);
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
            isEnd=true;
            break;
    }

    return nextScreen;
}
//

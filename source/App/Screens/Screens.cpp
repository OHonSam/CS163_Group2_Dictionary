#include "Screens.hpp"

bool Screen::checkString(const std::string &str, int& choice)
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

int Screen::inputOption(int maxOption)
{
    int option=maxOption;

    std::cout<<"Your choice: ";
    std::string str; std::getline(std::cin, str, '\n');
    while (!checkString(str, option) || option < 1 || option > maxOption)
    {
        std::cout<<"Invalid input. Please try again: ";
        std::getline(std::cin, str, '\n');
    }

    return option;
}

void Home::render()
{
    std::cout<<"Home screen"<<std::endl;
    isEnd = true;
}

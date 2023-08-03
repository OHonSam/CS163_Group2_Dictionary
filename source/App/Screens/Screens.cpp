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

bool Screen::checkStrEng(std::string& str)
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

bool Screen::checkStrViet(std::string& str)
{
	int length = str.size();
	if (length > 100 || length == 0)
		return false;

	for (char &c : str)
		if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';

	for (int j = 0; j < length; ++j)
		if (!((str[j] >= 'a' && str[j] <= 'z') || str[j] == ' '))
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
std::string Screen::inputVietString(const std::string &mess)
{
	std::string str;
	std::cout << mess;
	std::getline(std::cin, str, '\n');
	while (!checkStrViet(str))
	{
		std::cout << "Invalid input. Please try again: ";
		std::getline(std::cin, str, '\n');
	}

	return str;
}
//

// HomeScreen
Screen *HomeScreen::render()
{
	clearScr();

	std::cout << "Welcome to Dictionary!" << std::endl;
	int siz = options.size();
	for (int i = 0; i < siz; ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
    Screen* nextScreen=this;//"this"->own object
    int choice=inputOption(options.size());
    switch(choice)
    {
        case 1: // Search
            nextScreen=new SearchScreen(dict);
            break;
        case 2: // View
            nextScreen=new ViewScreen(dict);
            break;
        case 3: // Edit
            nextScreen=new EditScreen(dict);
            break;
        case 4: // Daily word
			nextScreen=new DailyWordScreen(dict);
            break;
        case 5: // Multi choices quiz
			nextScreen=new MultiChoicesScreen(dict);
            break;
        case 6: // Reset to default
            break;
        case 7: // Switch datasets
			nextScreen=new SwitchDataSetScreen(dict);
            break;
		default:
			nextScreen=nullptr;
			break;
    }

	return nextScreen;
}

//-------------------------Parent: HomeScreen-------------------------------

//missing the switch case data set
Screen* SearchScreen::render(){
    clearScr();

    for(int i=0;i<options.size();++i)
        std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
    
    Screen* nextScreen=this;//"this"->own object
    int choice=inputOption(options.size());
    switch(choice)
    {
        case 1:
            nextScreen=new SearchForDefScreen(dict);
            break;
        case 2:
            //nextScreen=new SearchForWordScreen(dict);
            break;
        case 3:
            nextScreen=new HomeScreen(dict);
            break;
    }
    return nextScreen;
}

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
		nextScreen = new ViewFavListScreen(dict);
		break;
	case 3:
		nextScreen = new SearchPrefixFavList(dict);
		break;
	case 4:
		nextScreen = new HomeScreen(dict);
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
		nextScreen = new AddWordScreen(dict);
		break;
	case 2:
		nextScreen = new EditWordScreen(dict);
		break;
	case 3:
		nextScreen = new DeleteWordScreen(dict);
		break;
	case 4:
		nextScreen = new Add1WordFavListScreen(dict);
		break;
	case 5:
		nextScreen = new Remove1WordFavListScreen(dict);
		break;
	case 6:
		nextScreen = new ClearFavListScreen(dict);
		break;
	case 7:
		nextScreen = new Remove1WordHistoryScreen(dict);
		break;
	case 8:
		nextScreen = new DeleteAllHistoryScreen(dict);
		break;
	case 9:
		nextScreen = new HomeScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *DailyWordScreen::render()
{
	clearScr();
	Word *w = dict->getDailyWord();
	std::cout << "Today's word is: " << w->word;
	std::cout << "\nDefinition(s): \n";

	for (int type = 0; type < POS::Count; ++type)
	{
		if (w->def[type].empty())
			continue;
		std::cout << "\t" << POS::TypeString[type] << ": " << std::endl;
		for (int idx = 0; idx < w->def[type].size(); ++idx)
		{
			std::cout << "\t\t" << idx + 1 << ". " << w->def[type][idx] << std::endl;
		}
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	Screen *nextScreen = this; //"this"->own object
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new DailyWordScreen(dict);
		break;
	case 2:
		nextScreen = new HomeScreen(dict);
		break;
	}
	return nextScreen;
}
Screen *MultiChoicesScreen::render()
{
	clearScr();

	std::cout << ques << std::endl;
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

	Screen *nextScreen = this;
	int choice = inputOption(options.size());
	switch (choice)
	{
		case 1: // 1 word and 4 definitions
			nextScreen = new OneWord4DefScreen(dict);
			break;
		case 2: // 1 definition and 4 words
			nextScreen = new OneDef4WordScreen(dict);
			break;
		case 3:
			nextScreen = new HomeScreen(dict);
			break;
	}

	return nextScreen;
}
//one
Screen *SwitchDataSetScreen::render()
{
	clearScr();

	std::cout << "Which dataset would you like to use?\n" << std::endl;
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

	Screen *nextScreen = this;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		dict->switchDataSet(DataSet::EE);
		std::cout << "Switched to English - English dataset!" << std::endl;
		std::cout << "Press 1 to go back to the previous page." << std::endl;
		inputOption(1);
		return new HomeScreen(dict);
	case 2:
		dict->switchDataSet(DataSet::EV);
		std::cout << "Switched to English - Vietnamese dataset!" << std::endl;
		std::cout << "Press 1 to go back to the previous page." << std::endl;
		inputOption(1);
		return new HomeScreen(dict);
	case 3:
		dict->switchDataSet(DataSet::Slang);
		std::cout << "Switched to Slang words dataset!" << std::endl;
		std::cout << "Press 1 to go back to the previous page." << std::endl;
		inputOption(1);
		break;
	case 4:
		nextScreen = new HomeScreen(dict);
		break;
	}

	return nextScreen;
}

//-------------------------End Parent: HomeScreen---------------------------

//-------------------------Parent: SearchScreen-----------------------------------
Screen *SearchForDefScreen::render()
{
	clearScr();

	Screen *nextScreen = this;
    
	//std::cout << "Enter the word you want to search for: ";
	std::string word;
	switch(dict->getCurDataSet())
	{
		case DataSet::VE:
			word=inputVietString("Enter the word you want to search for: ");
			break;
		default:
			word=inputEngString("Enter the word you want to search for: ");
			break;
	}
	std::vector<std::string> prefixes = dict->searchPrefix(word);
	if (displayPrefix(prefixes))
	{
		std::cout << "\nOptions: \n";
		// <<"1. Search for definition(s) of the exact word\n"
		// <<"2. Search for definition(s) of all words with the same prefix\n"
		// <<"3. Back\n";
		for (int i = 0; i < options.size(); ++i)
			std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
		int choice = inputOption(options.size());
		switch (choice)
		{
		case 1:
			nextScreen = new DisplayExactModeScreen(dict, word);
			break;
		case 2:
			nextScreen = new Display1PrefixModeScreen(dict, prefixes);
			break;
		case 3:
			nextScreen = new DisplayPrefixesModeScreen(dict, prefixes);
			break;
		case 4:
			nextScreen = new SearchScreen(dict);
			break;
		}
	}
	else
	{
		std::cout << "No result found!\n";
		std::cout << "\nOptions: \n";
		int cnt = 0;
		std::cout << ++cnt << ". "
				  << "Back\n";
		int choice = inputOption(cnt);
		switch (choice)
		{
		case 1:
			nextScreen = new SearchScreen(dict);
			break;
		}
	}
	return nextScreen;
}
bool SearchForDefScreen::displayPrefix(std::vector<std::string> &prefixes)
{
	// std::vector<std::string> prefixes=dict->searchPrefix(word);
	if (prefixes.empty())
	{
		// std::cout<<"No result found!\n";
		return false;
	}
	else
	{
		std::vector<Word *> defsForPrefixes;
		int n = prefixes.size();
		std::cout << "Here is/are keyword(s) with the same prefix that you may be looking for: \n";
		for (int i = 0; i < n; ++i)
		{
			std::cout << i + 1 << ". " << prefixes[i] << std::endl;
		}
	}
	return true;
}
//-------------------------End Parent: SearchScreen-------------------------------

//-------------------------Parent: SearchForDefScreen-------------------------------
Screen *DisplayExactModeScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	Word *w = dict->searchForDef(word);
	if (w == nullptr)
		std::cout << "No result found!\n";
	else
	{
		std::cout << "The keyword that you are looking for is: " << w->word << std::endl;
		dict->removeHistory(word);
		dict->addHistory(word);
		for (int type = 0; type < POS::Count; ++type)
		{
			if (w->def[type].empty())
				continue;
			std::cout << "\t" << POS::TypeString[type] << ": " << std::endl;
			for (int idx = 0; idx < w->def[type].size(); ++idx)
			{
				std::cout << "\t\t" << idx + 1 << ". " << w->def[type][idx] << std::endl;
			}
		}
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		clearScr();
		nextScreen = new EditSearchWordScreen(dict, word);
		break;
	case 2:
		clearScr();
		nextScreen = new DeleteSearchWordScreen(dict, word);
		break;
	case 3:
		nextScreen = new AddGivenWordFavListScreen(dict, word);
		break;
	case 4:
		nextScreen = new SearchScreen(dict);
		break;
	}
	return nextScreen;
}
Screen *Display1PrefixModeScreen::render()
{
	clearScr();
	Screen *nextScreen = this;

	std::string word;
	std::cout << "Enter the prefix you want to search for: ";
	std::getline(std::cin, word);
	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the prefix you want to search for: ";
		std::getline(std::cin, word);
	}

	bool found = false;
	for (int i = 0; i < prefixes.size(); ++i)
	{
		if (word == prefixes[i])
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		std::cout << "No result found!\n";
		std::cout << "\nOptions: \n";
		std::cout << "1. Back\n";
		int choice = inputOption(1);
		switch (choice)
		{
		case 1:
			nextScreen = new SearchScreen(dict);
		}
	}
	else
	{
		Word *w = dict->searchForDef(word);
		// std::cout<<"The keyword that you are looking for is: "<<w->word<<std::endl;
		dict->removeHistory(word);
		dict->addHistory(word);
		for (int type = 0; type < POS::Count; ++type)
		{
			if (w->def[type].empty())
				continue;
			std::cout << "\t" << POS::TypeString[type] << ": " << std::endl;
			for (int idx = 0; idx < w->def[type].size(); ++idx)
			{
				std::cout << "\t\t" << idx + 1 << ". " << w->def[type][idx] << std::endl;
			}
		}
		std::cout << "\nOptions: \n";
		for (int i = 0; i < options.size(); ++i)
			std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
		int choice = inputOption(options.size());
		switch (choice)
		{
		case 1:
			clearScr();
			nextScreen = new EditSearchWordScreen(dict, word);
			break;
		case 2:
			clearScr();
			nextScreen = new DeleteSearchWordScreen(dict, word);
			break;
		case 3:
			nextScreen = new AddGivenWordFavListScreen(dict, word);
			break;
		case 4:
			nextScreen = new SearchScreen(dict);
			break;
		}
	}
	return nextScreen;

}
Screen *DisplayPrefixesModeScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	// std::vector<std::string> prefixes=dict->searchPrefix(word);
	if (prefixes.empty())
		std::cout << "No result found!\n";
	else
	{
		std::vector<Word *> defsForPrefixes;
		int n = prefixes.size();
		for (int i = 0; i < n; ++i)
		{
			defsForPrefixes.push_back(dict->searchForDef(prefixes[i]));
			dict->removeHistory(prefixes[i]);
			dict->addHistory(prefixes[i]);
		}
		std::cout << "The keyword(s) with the same prefix that you are looking for is/are: \n";
		for (int i = 0; i < n; ++i)
		{
			std::cout << i + 1 << ". " << prefixes[i] << std::endl;
			for (int type = 0; type < POS::Count; ++type)
			{
				if (defsForPrefixes[i]->def[type].empty())
				{
					continue;
				}
				std::cout << "\t" << POS::TypeString[type] << ": " << std::endl;
				for (int idx = 0; idx < defsForPrefixes[i]->def[type].size(); ++idx)
				{
					std::cout << "\t\t"
							  << "-" << defsForPrefixes[i]->def[type][idx] << std::endl;
				}
			}
		}
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new SearchForDefScreen(dict);
	}
	return nextScreen;
}

//-------------------------End Parent: SearchForDefScreen---------------------------

//-------------------------Parent: ViewScreen-------------------------------
Screen *ViewHistoryScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Your search history (20 most recent keywords):\n";
	std::vector<std::string> display = dict->getHistory();
	for (int i = 0; i < display.size(); ++i)
	{
		std::cout << i + 1 << ". " << display[i] << std::endl;
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new Search1WordHistoryScreen(dict);
		break;
	case 2:
		nextScreen = new Remove1WordHistoryScreen(dict);
		break;
	case 3:
		nextScreen = new DeleteAllHistoryScreen(dict);
		break;
	case 4:
		nextScreen = new ViewScreen(dict);
		break;
	}
	return nextScreen;
}
Screen *ViewFavListScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Your favourite list:\n";
	std::vector<std::string> display = dict->getFav();
	for (int i = 0; i < display.size(); ++i)
	{
		std::cout << i + 1 << ". " << display[i] << std::endl;
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new Search1WordFavListScreen(dict);
		break;
	case 2:
		nextScreen = new Remove1WordFavListScreen(dict);
		break;
	case 3:
		nextScreen = new ClearFavListScreen(dict);
		break;
	case 4:
		nextScreen = new ViewScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *SearchPrefixFavList::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::string prefix;
	std::getline(std::cin, prefix);

	std::cout << "Enter the prefix of word(s) you want to view: ";

	while (!dict->lowerStrEng(prefix))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the prefix of word(s) you want to view: ";
		std::getline(std::cin, prefix);
	}

	if (dict->isInFavList(prefix))
	{
		std::cout << "No result found!\n";
	}
	else
	{
		int cnt = 0;
		std::vector<std::string> display = dict->searchPrefixFavlist(prefix);
		std::cout << "The words that start with <" << prefix << "> are: \n";

		for (auto i : display)
		{
			std::cout << ++cnt << ". " << i << '\n';
		}

		std::cout << "\nThere are " << cnt << " words that start with <" << prefix << ">\n";
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewScreen(dict);
		break;
	}
	return nextScreen;
}
//-------------------------End Parent: ViewScreen-------------------------------

//-------------------------Parent: ViewHistoryScreen-------------------------------
Screen *Search1WordHistoryScreen::render()
{
	Screen *nextScreen = this;
	std::cout << "Enter the word from history you want to search for: ";
	std::string word;
	std::getline(std::cin, word);

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to search for: ";
		std::getline(std::cin, word);
	}

	if (!dict->isInHistory(word))
	{
		std::cout << "No result found!\n";
	}
	else
	{
		Word *w = dict->searchForDef(word);
		std::cout << "The keyword that you are looking for is: " << w->word << std::endl;
		dict->removeHistory(word);
		dict->addHistory(word);
		for (int type = 0; type < POS::Count; ++type)
		{
			if (w->def[type].empty())
				continue;
			std::cout << "\t" << POS::TypeString[type] << ": " << std::endl;
			for (int idx = 0; idx < w->def[type].size(); ++idx)
			{
				std::cout << "\t\t" << idx + 1 << ". " << w->def[type][idx] << std::endl;
			}
		}
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewHistoryScreen(dict);
		break;
	}
	return nextScreen;
}
//-------------------------End Parent: ViewHistoryScreen-------------------------------


//-------------------------Parent: ViewFavListScreen--------------------------------
Screen *Search1WordFavListScreen::render()
{
	Screen *nextScreen = this;
	std::cout << "Enter the word from favourite list you want to search for: ";
	std::string word;
	std::getline(std::cin, word);

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to search for: ";
		std::getline(std::cin, word);
	}

	if (!dict->isInFavList(word))
	{
		std::cout << "No result found!\n";
	}
	else
	{
		Word *w = dict->searchForDef(word);
		std::cout << "The keyword that you are looking for is: " << w->word << std::endl;
		for (int type = 0; type < POS::Count; ++type)
		{
			if (w->def[type].empty())
				continue;
			std::cout << "\t" << POS::TypeString[type] << ": " << std::endl;
			for (int idx = 0; idx < w->def[type].size(); ++idx)
			{
				std::cout << "\t\t" << idx + 1 << ". " << w->def[type][idx] << std::endl;
			}
		}
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewFavListScreen(dict);
		break;
	}
	return nextScreen;
}
//-------------------------End Parent: ViewFavListScreen---------------------------


//-------------------------Parent: EditScreen-----------------------------------
Screen *AddWordScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	Word *w = new Word;
	std::cout << "Enter the new word you want to add: ";
	std::getline(std::cin, w->word, '\n');

	while (!dict->lowerStrEng(w->word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the new word you want to add: ";
		std::getline(std::cin, w->word, '\n');
	}

	if (dict->isInDict(w->word))
	{
		std::cout << "This word is already in the dictionary!\n";
	}
	else
	{
		std::cout << "Parts of speech: \n";
		for (int i = 0; i < POS::Count; ++i)
		{
			std::cout << i + 1 << ". " << POS::TypeString[i] << std::endl;
		}
		std::string buffer;
		std::cout << "Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
		std::getline(std::cin, buffer, '\n');

		std::unordered_set<int> pos; // to avoid duplicate
		std::stringstream ss(buffer);
		std::string temp;
		int choice;
		while (ss >> temp)
		{
			if (!dict->isValidPOS(temp, choice))
			{ // check the input if it is a valid number (1<=num<=9) or a random string or out of bound
				std::cout << "Invalid input. Please try again!\n";
				std::cout << "Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
				std::getline(std::cin, buffer, '\n');
				ss.clear();
				pos.clear();
				ss.str(buffer);
			}
			else
			{
				pos.insert(choice);
			}
		}
		for (std::unordered_set<int>::iterator itr = pos.begin(); itr != pos.end(); ++itr)
		{
			std::cout << "Enter the word's definition as " << POS::TypeString[*itr - 1] << ": ";
			std::getline(std::cin, buffer, '\n');
			w->def[*itr - 1].push_back(buffer);
		}

		dict->addWord(w);
		std::cout << "The new word has been added to the dictionary!\n";
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}
Screen *EditWordScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Enter the word you want to edit: ";
	std::string word;
	std::getline(std::cin, word, '\n');

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to edit: ";
		std::getline(std::cin, word, '\n');
	}
	// check the existence of the word you want to edit in the dictionary
	if (!dict->isInDict(word))
	{
		std::cout << "This word is not in the dictionary!\n";
	}
	else
	{
		nextScreen = new EditSearchWordScreen(dict, word);
	}
	return nextScreen;
}
Screen *EditSearchWordScreen::render()
{
	// clearScr();
	Screen *nextScreen = this;

	Word *w = new Word;
	std::cout << "Enter the new word: ";
	std::getline(std::cin, w->word, '\n');

	while (!dict->lowerStrEng(w->word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the new word you want to add: ";
		std::getline(std::cin, w->word, '\n');
	}
	dict->removeWord(word);
	// Check if the new word you want to override the old one is already in the dictionary or not-> if not then continue
	if (dict->isInDict(w->word))
	{
		std::cout << "This word is already in the dictionary!\n";
	}
	else
	{
		std::cout << "Parts of speech: \n";
		for (int i = 0; i < POS::Count; ++i)
		{
			std::cout << i + 1 << ". " << POS::TypeString[i] << std::endl;
		}
		std::string buffer;
		std::cout << "Enter all parts of speech you want to add/edit definition to(ex: 1 2 ... 9): ";
		std::getline(std::cin, buffer, '\n');

		std::unordered_set<int> pos; // to avoid duplicate
		std::stringstream ss(buffer);
		std::string temp;
		int choice;
		while (ss >> temp)
		{
			if (!dict->isValidPOS(temp, choice))
			{ // check the input if it is a valid number (1<=num<=9) or a random string or out of bound
				std::cout << "Invalid input. Please try again!\n";
				std::cout << "Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
				std::getline(std::cin, buffer, '\n');
				ss.clear();
				pos.clear();
				ss.str(buffer);
			}
			else
			{
				pos.insert(choice);
			}
		}
		for (std::unordered_set<int>::iterator itr = pos.begin(); itr != pos.end(); ++itr)
		{
			std::cout << "Enter the word's definition as " << POS::TypeString[*itr - 1] << ": ";
			std::getline(std::cin, buffer, '\n');
			w->def[*itr - 1].push_back(buffer);
		}

		dict->addWord(w);
		std::cout << "The word has been successfully edited!\n";
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new SearchScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}
Screen *DeleteWordScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Enter the word you want to delete: ";
	std::string word;
	std::getline(std::cin, word, '\n');

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to delete: ";
		std::getline(std::cin, word, '\n');
	}
	// check the existence of the word you want to delete in the dictionary
	if (!dict->isInDict(word))
	{
		std::cout << "This word is not in the dictionary!\n";
	}
	else
	{
		nextScreen = new DeleteSearchWordScreen(dict, word);
	}
	return nextScreen;
}
Screen *DeleteSearchWordScreen::render()
{
	// clearScr();
	Screen *nextScreen = this;
	int cnt = 0;
	std::cout << "Are you sure you want to delete this word?\n";
	std::cout << ++cnt << ". Yes\n";
	std::cout << ++cnt << ". No\n";
	int choice = inputOption(cnt);
	switch (choice)
	{
	case 1:
		dict->removeWord(word);
		std::cout << "The word has been successfully deleted!\n";
		break;
	case 2:
		std::cout << "The deletion has been cancelled!\n";
		break;
	}
	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new SearchScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}
Screen *Remove1WordHistoryScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Enter the word you want to remove from your search history: ";
	std::string word;
	std::getline(std::cin, word);

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to search for: ";
		std::getline(std::cin, word);
	}
	dict->removeHistory(word);

	std::cout << "The word has been successfully removed from your search history!\n";
	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewHistoryScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *DeleteAllHistoryScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Are you sure that you want to delete your search history?\n";
	int cnt = 0;
	std::string buffer;
	std::cout << ++cnt << ". Yes\n";
	std::cout << ++cnt << ". No\n";
	int choice = inputOption(cnt);
	switch (choice)
	{
	case 1:
		if (dict->clearAllHistory())
			std::cout << "Your search history has been successfully deleted!\n";
		else
			std::cout << "Errors occurred in clearing time!\n";
		break;
	case 2:
		std::cout << "The deletion has been cancelled!\n";
		break;
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewHistoryScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *ClearFavListScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Are you sure that you want to clear your favourite list?\n";
	int cnt = 0;
	std::string buffer;
	std::cout << ++cnt << ". Yes\n";
	std::cout << ++cnt << ". No\n";
	int choice = inputOption(cnt);
	switch (choice)
	{
	case 1:
		if (dict->clearFavList())
			std::cout << "Your favourite list has been successfully deleted!\n";
		else
			std::cout << "Errors occurred while clearing!\n";
		break;
	case 2:
		std::cout << "The deletion has been cancelled!\n";
		break;
	}

	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewFavListScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *Remove1WordFavListScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Enter the word you want to remove from your favourite list: ";
	std::string word;
	std::getline(std::cin, word);

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to search for: ";
		std::getline(std::cin, word);
	}
	dict->removeFav(word);

	std::cout << "The word has been successfully removed from your favourite list!\n";
	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewFavListScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *Add1WordFavListScreen::render()
{
	clearScr();
	Screen *nextScreen = this;
	std::cout << "Enter the word you want to add to your favourite list: ";
	std::string word;
	std::getline(std::cin, word);

	while (!dict->lowerStrEng(word))
	{
		std::cout << "Invalid input. Please try again!\n";
		std::cout << "Enter the word you want to search for: ";
		std::getline(std::cin, word);
	}
	dict->addFav(word);

	std::cout << "The word has been successfully add to your favourite list!\n";
	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new ViewFavListScreen(dict);
		break;
	case 2:
		nextScreen = new EditScreen(dict);
		break;
	}
	return nextScreen;
}

Screen *AddGivenWordFavListScreen::render()
{
	Screen *nextScreen = this;
	dict->addFav(word);

	std::cout << "The word has been successfully add to your favourite list!\n";
	std::cout << "\nOptions: \n";
	for (int i = 0; i < options.size(); ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;
	int choice = inputOption(options.size());
	switch (choice)
	{
	case 1:
		nextScreen = new DisplayExactModeScreen(dict, word);
		break;
	case 2:
		nextScreen = new Display1PrefixModeScreen(dict, prefixes);
		break;
	}
	return nextScreen;
}

//-------------------------End Parent: EditScreen-------------------------------
//-------------------------Parent: MultipleChoices--------------------------------

Screen *OneWord4DefScreen::render()
{
	clearScr();

	const int N=4;

	std::vector<Word*> v=dict->getMultiChoices(N);

	std::vector<std::pair<std::string,int>> options;
	for(int i=0; i<N; i++) options.push_back({v[i]->getRandDef(),i});
	std::shuffle(options.begin(),options.end(),std::mt19937(std::random_device()()));

	std::cout << "Choose the correct definition for the word: " << v[0]->word << std::endl;
	for (int i = 0; i < N; ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i].first << std::endl << std::endl;
	std::cout << std::to_string(N + 1) << ". " << "Back" << std::endl;

	while(1)
	{
		int choice = inputOption(N + 1);
		if(choice==N+1) return new MultiChoicesScreen(dict);

		if(options[choice-1].second==0){
			std::cout<<"Correct!"<<std::endl;
			std::cout<<"Press 1 to go back to the previous page."<<std::endl;
			inputOption(1);
			return new MultiChoicesScreen(dict);
		}
		else
			std::cout<<"Incorrect! Please try again."<<std::endl;
	}
}
Screen *OneDef4WordScreen::render()
{
    clearScr();

	const int N=4;

	std::vector<Word*> v=dict->getMultiChoices(N);

	std::vector<std::pair<std::string,int>> options;
	for(int i=0; i<N; i++) options.push_back({v[i]->word,i});
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(options.begin(),options.end(),std::default_random_engine(seed));

	std::cout << "Choose the correct definition for the word: " << v[0]->getRandDef() << std::endl;
	for (int i = 0; i < N; ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i].first << std::endl << std::endl;
	std::cout << std::to_string(N + 1) << ". " << "Back" << std::endl;

	while(1)
	{
		int choice = inputOption(N + 1);
		if(choice==N+1) return new MultiChoicesScreen(dict);

		if(options[choice-1].second==0){
			std::cout<<"Correct!"<<std::endl;
			std::cout<<"Press 1 to go back to the previous page."<<std::endl;
			inputOption(1);
			return new MultiChoicesScreen(dict);
		}
		else
			std::cout<<"Incorrect! Please try again."<<std::endl;
	}
}


//-------------------------End Parent: MultipleChoices---------------------------
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
            break;
        case 5: // Multi choices quiz
			nextScreen=new MultiChoicesScreen(dict);
            break;
        case 6: // Reset to default
            break;
        case 7: // Switch datasets
            break;
		default:
			nextScreen=nullptr;
			break;
    }

	return nextScreen;
}
//-------------------------Parent: HomeScreen-------------------------------
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
//-------------------------End Parent: HomeScreen-------------------------------

Screen *ViewScreen::render()
{
	clearScr();
	for (int i = 0; i < options.size(); i++)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

    Screen* nextScreen=this;//"this"->own object
    int choice=inputOption(options.size());
    switch(choice){
        case 1:
            nextScreen=new ViewHistoryScreen(dict);
            break;  
        case 2:
            break;
        case 3:
            //View favorite list
            break;
        case 4:
            break;
        case 5: 
            nextScreen=new HomeScreen(dict);
            break;
    }
    return nextScreen;
}
Screen *EditScreen::render()
{
	clearScr();

	for (int i = 0; i < options.size(); i++)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

    Screen* nextScreen=this;//"this"->own object
    int choice=inputOption(options.size());
    switch(choice){
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
            nextScreen=new Remove1WordHistoryScreen(dict); 
            break;
        case 7:
            nextScreen=new DeleteAllHistoryScreen(dict);
            break;
        case 8:
            nextScreen=new HomeScreen(dict);
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
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl;

	Screen *nextScreen = this;
	int choice = inputOption(options.size());
	// fix Linh
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
			break;
		case 3:
			nextScreen = new HomeScreen(dict);
			break;
	}

	return nextScreen;
}

//-------------------------End Parent: HomeScreen---------------------------

//-------------------------Parent: SearchScreen-----------------------------------
Screen* SearchForDefScreen::render(){
    clearScr();
    std::cout<<"Enter the word you want to search for: ";
    std::string word;
    std::getline(std::cin,word);
    while(!dict->lowerStrEng(word))
    {
        std::cout<<"Invalid input. Please try again!\n";
        std::cout<<"Enter the word you want to search for: ";
        std::string word;
        std::getline(std::cin,word);
    }
    std::cout<<"Options: \n"
        <<"1. Search for the exact word\n"
        <<"2. Search for the words that has the same prefix\n"
        <<"3. Back\n";
    int choice=inputOption(3);
    switch(choice){
        case 1:
            SearchForDefScreen::displayExactMode(word);
            break;
        case 2:
            SearchForDefScreen::displayPrefixMode(word);
            break;
        case 3:
            return new SearchScreen(dict);
    }
    int cnt=0;
    std::cout<<++cnt<<". Back"<<std::endl;
    inputOption(cnt);
    return new SearchScreen(dict);
    
}
void SearchForDefScreen::displayPrefixMode(const std::string& word)
{
    std::vector<std::string> prefixes=dict->searchPrefix(word);
    if(prefixes.empty())
        std::cout<<"No result found!\n";
    else{
        std::vector<Word*> defsForPrefixes;
        int n=prefixes.size();
        for(int i=0;i<n;++i){
            defsForPrefixes.push_back(dict->searchDef(prefixes[i]));
            dict->addHistory(prefixes[i]);
        }
        std::cout<<"The keyword(s) that you are looking for is/are: \n";
        for(int i=0;i<n;++i){
            std::cout<<i+1<<". "<<prefixes[i]<<std::endl;
            for(int type=0;type<POS::Count;++type){
                //std::cout<<type<<std::endl;
                if(defsForPrefixes[i]->def[type].empty()) {
                    //std::cout<<"No definition for this type"<<std::endl;
                    continue;
                }
                std::cout<<"\t"<<POS::TypeString[type]<<": "<<std::endl;
                for(int idx=0;idx<defsForPrefixes[i]->def[type].size();++idx){
                    std::cout<<"\t\t"<<"-"<<defsForPrefixes[i]->def[type][idx]<<std::endl;
                }
            }
        }
    }
    
}
void SearchForDefScreen::displayExactMode(const std::string& word)
{
    Word* w=dict->searchDef(word);
    if(w==nullptr)
        std::cout<<"No result found!\n";
    else{
        std::cout<<"The keyword that you are looking for is: "<<w->word<<std::endl;
        dict->addHistory(word);
        for(int type=0;type<POS::Count;++type){
            if(w->def[type].empty()) 
                continue;
            std::cout<<"\t"<<POS::TypeString[type]<<": "<<std::endl;
            for(int idx=0;idx<w->def[type].size();++idx){
                std::cout<<"\t\t"<<idx+1<<". "<<w->def[type][idx]<<std::endl;
            }
        }
    }
}
//-------------------------End Parent: SearchScreen-------------------------------

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

	std::cout << "Enter the word you want to remove from your favourite list: ";
	std::string word;
	std::getline(std::cin, word);

	dict->uppercase2Lowercase(word);
	dict->removeFav(word);

	std::cout << "The word has been successfully removed from your favourite list!\n";
	int cnt = 0;
	std::cout << ++cnt << ". Back" << std::endl;
	inputOption(cnt);
	return new FavListChoiceScreen(dict);
}

Screen *Type2InsertWordFavListScreen::render()
{
	clearScr();

	std::cout << "Enter the word you want to remove from your favourite list: ";
	std::string word;
	std::getline(std::cin, word);

	dict->uppercase2Lowercase(word);
	dict->addFav(word);

	std::cout << "The word has been successfully removed from your favourite list!\n";
	int cnt = 0;
	std::cout << ++cnt << ". Back" << std::endl;
	inputOption(cnt);
	return new FavListChoiceScreen(dict);
}

Screen *SearchPrefixFavList::render()
{
	std::string prefix;
	int cnt = 0;

	clearScr();

	std::cout << "Please type in the word you want to search: ";

	std::getline(std::cin, prefix, '\n');

	dict->uppercase2Lowercase(prefix);

	std::vector<std::string> display = dict->searchPrefixFavlist(prefix);

	std::cout << "The words that start with <" << prefix << "> are: \n";

	for (auto i : display)
	{
		std::cout << ++cnt << ". " << i << '\n';
	}

	std::cout << "\nThere are " << cnt << " words that start with <" << prefix << ">\n";

	cnt = 0;
	std::cout << ++cnt << ". Back" << std::endl;
	inputOption(cnt);
	return new FavListChoiceScreen(dict);
}
//----------------------End Parent: FavListChoiceScreen--------------------------------------

Screen *OneWord4DefScreen::render()
{
	clearScr();

	const int N=4;

	std::string ques;
	std::vector<std::string> options;
	dict->getMultileChoices(ques, options, N, true);

	std::cout << "Choose the correct definition for the word: " << ques << std::endl;
	for (int i = 0; i < N; ++i)
		std::cout << std::to_string(i + 1) << ". " << options[i] << std::endl << std::endl;
	std::cout << std::to_string(N + 1) << ". " << "Back" << std::endl;

	Word* w=dict->searchDef(ques);

	while(1)
	{
		int choice = inputOption(N + 1);
		if(choice==N+1) return new MultiChoicesScreen(dict);

		if(w->checkDef(options[choice-1])){
			std::cout<<"Correct!"<<std::endl;
			std::cout<<"Press 1 to go back to the previous page."<<std::endl;
			inputOption(1);
			return new MultiChoicesScreen(dict);
		}
		else
			std::cout<<"Incorrect! Please try again."<<std::endl;
	}
}

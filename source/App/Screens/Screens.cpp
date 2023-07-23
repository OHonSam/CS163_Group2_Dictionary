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

void Screen::clearScr()
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

    std::cout<<mess;
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
    clearScr();

    std::cout<<"Welcome to Dictionary!"<<std::endl;
    for(int i=0; i<options.size(); i++)
        std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;

    Screen* nextScreen=this;//"this"->own object
    int choice=inputOption(options.size());
    switch(choice)
    {
        case 1:
            nextScreen=new SearchScreen(dict);
            break;
        case 2:
            nextScreen=new EditScreen(dict);
            break;
        case 3:
            nextScreen=new ViewScreen(dict);
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
            nextScreen=new Home(dict);
            break;
    }
    return nextScreen;
}
Screen* ViewScreen::render(){
    clearScr();

    for(int i=0; i<options.size(); i++)
        std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;

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
            nextScreen=new Home(dict);
            break;
    }
    return nextScreen;
}
Screen* EditScreen::render(){
    clearScr();

    for(int i=0; i<options.size(); i++)
        std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;

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
            nextScreen=new Home(dict);
            break;
    }
    return nextScreen;
}
//-------------------------End Parent: Home---------------------------

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
Screen*  ViewHistoryScreen::render(){
    clearScr();
	std::cout<< "Your search history (20 most recent keywords):\n";
	std::vector<std::string> display= dict->getHistory();
	for(int i=0;i<display.size();++i){
        std::cout<<display[i]<<std::endl;
    }

    int cnt=0;
    std::cout<<++cnt<<". Back"<<std::endl;
    inputOption(cnt);
    return new ViewScreen(dict);
}

//-------------------------End Parent: ViewScreen-------------------------------

//-------------------------Parent: EditScreen-----------------------------------
Screen* Remove1WordHistoryScreen::render(){
    clearScr();
    std::cout<<"Enter the word you want to remove from your search history: ";
    std::string word;
    std::getline(std::cin,word);

    dict->removeHistory(word);

    std::cout<<"The word has been successfully removed from your search history!\n";
    int cnt=0;
    std::cout<<++cnt<<". Back"<<std::endl;
    inputOption(cnt);
    return new EditScreen(dict);
}
Screen* DeleteAllHistoryScreen::render(){
    clearScr();
    std::cout<<"Are you sure that you want to delete your search history?\n";
	int cnt = 0;
	std::string buffer;
	std::cout<<++cnt<<". Yes\n";
	std::cout<<++cnt<<". No\n";
    int choice=inputOption(cnt);
    	switch(choice){
		case 1:
			if(dict->clearAllHistory("History.bin"))
				std::cout<<"Your search history has been successfully deleted!\n";
			else
				std::cout<<"Errors occurred in clearing time!\n";
			break;
		case 2:
			std::cout<<"The deletion has been cancelled!\n";
			break;
	}

    cnt=0;
    std::cout<<++cnt<<". Back"<<std::endl;
    inputOption(cnt);
    return new EditScreen(dict);
}
//-------------------------End Parent: EditScreen-------------------------------

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
		std::cout << std::to_string(i+1) << ". " << options[i] << std::endl;

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
			//nextScreen=new DailyWordScreen(dict);
            break;
        case 5:
            break;
        case 6:
            break;
		case7:
			break;
        case 8: // Exit
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
//-------------------------End Parent: Home-------------------------------

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
			//view favorite list
            break;
        case 3: 
            nextScreen=new Home(dict);
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
            nextScreen=new AddWordScreen(dict);
            break;  
        case 2:
            nextScreen=new EditWordScreen(dict);
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
		nextScreen = new Home(dict);
		break;
	}

	return nextScreen;
}
//-------------------------End Parent: Home---------------------------

//-------------------------Parent: SearchScreen-----------------------------------
Screen* SearchForDefScreen::render(){
    clearScr();

	Screen* nextScreen = this;

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

	if(displayPrefix(word)){
		std::cout<<"\nOptions: \n";
			// <<"1. Search for definition(s) of the exact word\n"
			// <<"2. Search for definition(s) of all words with the same prefix\n"
			// <<"3. Back\n";
		for(int i=0;i<options.size();++i)
			std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
		int choice=inputOption(options.size());
		switch(choice){
			case 1:
				//SearchForDefScreen::displayExactMode(word);
				nextScreen=new DisplayExactModeScreen(dict,word);
				break;
			case 2:
				nextScreen=new DisplayPrefixModeScreen(dict,word);
				break;
			case 3:
				//return new SearchScreen(dict);
				nextScreen=new SearchScreen(dict);
				break;
		}
	}

    // int cnt=0;
    // std::cout<<std::endl<<++cnt<<". Back"<<std::endl;
    // inputOption(cnt);
    // return new SearchScreen(dict);
    return nextScreen;
}
bool SearchForDefScreen::displayPrefix(const std::string& word)
{
    std::vector<std::string> prefixes=dict->searchPrefix(word);
    if(prefixes.empty()){
        std::cout<<"No result found!\n";
		return false;
	}
    else{
        std::vector<Word*> defsForPrefixes;
        int n=prefixes.size();
        for(int i=0;i<n;++i){
            defsForPrefixes.push_back(dict->searchForDef(prefixes[i]));
        }
        std::cout<<"Here is/are keyword(s) with the same prefix that you may be looking for: \n";
        for(int i=0;i<n;++i){
            std::cout<<i+1<<". "<<prefixes[i]<<std::endl;
        }
    }
    return true;
}
//-------------------------End Parent: SearchScreen-------------------------------

//-------------------------Parent: SearchForDefScreen-------------------------------
Screen* DisplayExactModeScreen::render(){
	clearScr();
	Screen* nextScreen=this;
    Word* w=dict->searchForDef(word);
    if(w==nullptr)
        std::cout<<"No result found!\n";
    else{
        std::cout<<"The keyword that you are looking for is: "<<w->word<<std::endl;
		dict->removeHistory(word);
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

	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			clearScr();
			nextScreen= new EditSearchWordScreen(dict,word);
			break;
		case 2:
			clearScr();
			nextScreen=new DeleteSearchWordScreen(dict,word);
			break;
		case 3:
			nextScreen= new Type2InsertWordFavListScreen(dict);
			break;
		case 4:
			nextScreen=new SearchScreen(dict);
			break;
	}
	return nextScreen;
}
Screen* DisplayPrefixModeScreen::render(){
	clearScr();
	Screen* nextScreen=this;
	std::vector<std::string> prefixes=dict->searchPrefix(word);
	if(prefixes.empty())
		std::cout<<"No result found!\n";
	else{
		std::vector<Word*> defsForPrefixes;
		int n=prefixes.size();
		for(int i=0;i<n;++i){
			defsForPrefixes.push_back(dict->searchForDef(prefixes[i]));
			dict->removeHistory(prefixes[i]);
			dict->addHistory(prefixes[i]);
		}
		std::cout<<"The keyword(s) with the same prefix that you are looking for is/are: \n";
		for(int i=0;i<n;++i){
			std::cout<<i+1<<". "<<prefixes[i]<<std::endl;
			for(int type=0;type<POS::Count;++type){
				if(defsForPrefixes[i]->def[type].empty()) {
					continue;
				}
				std::cout<<"\t"<<POS::TypeString[type]<<": "<<std::endl;
				for(int idx=0;idx<defsForPrefixes[i]->def[type].size();++idx){
					std::cout<<"\t\t"<<"-"<<defsForPrefixes[i]->def[type][idx]<<std::endl;
				}
			}
		}
	}

	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new SearchForDefScreen(dict);
	}
	return nextScreen;
}

//-------------------------End Parent: SearchForDefScreen---------------------------

//-------------------------Parent: ViewScreen-------------------------------
Screen *ViewHistoryScreen::render()
{
	clearScr();
	Screen* nextScreen=this;
	std::cout << "Your search history (20 most recent keywords):\n";
	std::vector<std::string> display = dict->getHistory();
	for (int i = 0; i < display.size(); ++i)
	{
		std::cout <<i+1<<". "<< display[i] << std::endl;
	}

	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen= new Search1WordHistoryScreen(dict);
			break;
		case 2:
			nextScreen=new Remove1WordHistoryScreen(dict);
			break;
		case 3:
			nextScreen=new DeleteAllHistoryScreen(dict);
			break;
		case 4:
			nextScreen=new ViewScreen(dict);
			break;
	}
	return nextScreen;
}
Screen * Search1WordHistoryScreen::render(){
	Screen* nextScreen=this;
	std::cout<<"Enter the word from history you want to search for: ";
	std::string word;
	std::getline(std::cin,word);

    while(!dict->lowerStrEng(word))
    {
        std::cout<<"Invalid input. Please try again!\n";
        std::cout<<"Enter the word you want to search for: ";
        std::string word;
        std::getline(std::cin,word);
    }
	
	if(!dict->isInHistory(word)){
		std::cout<<"No result found!\n";
	}
	else{
		Word* w=dict->searchForDef(word);
		std::cout<<"The keyword that you are looking for is: "<<w->word<<std::endl;
		dict->removeHistory(word);
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

	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new ViewHistoryScreen(dict);
			break;
	}
	return nextScreen;
} 

//-------------------------End Parent: ViewScreen-------------------------------

//-------------------------Parent: EditScreen-----------------------------------
Screen *AddWordScreen::render(){
	clearScr();
	Screen* nextScreen=this;
	Word* w=new Word;
	std::cout<<"Enter the new word you want to add: ";
	std::getline(std::cin,w->word,'\n');

	while(!dict->lowerStrEng(w->word))
	{
		std::cout<<"Invalid input. Please try again!\n";
		std::cout<<"Enter the new word you want to add: ";
		std::getline(std::cin,w->word,'\n');
	}

	if(dict->isInDict(w->word)){
		std::cout<<"This word is already in the dictionary!\n";
	}
	else{
		std::cout<<"Parts of speech: \n";
		for(int i=0;i<POS::Count;++i){
			std::cout<<i+1<<". "<<POS::TypeString[i]<<std::endl;
		}
		std::string buffer;
		std::cout<<"Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
		std::getline(std::cin,buffer,'\n');
		
		std::unordered_set<int> pos;// to avoid duplicate
		std::stringstream ss(buffer);
		std::string temp;
		int choice;
		while(ss>>temp){
			if(!dict->isValidPOS(temp,choice)){//check the input if it is a valid number (1<=num<=9) or a random string or out of bound
				std::cout<<"Invalid input. Please try again!\n";
				std::cout<<"Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
				std::getline(std::cin,buffer,'\n');
				ss.clear();
				pos.clear();
				ss.str(buffer);
			}
			else{
				pos.insert(choice);
			}
		}
		for(std::unordered_set<int>::iterator itr=pos.begin();itr!=pos.end();++itr){
			std::cout<<"Enter the word's definition as "<<POS::TypeString[*itr-1]<<": ";
			std::getline(std::cin,buffer,'\n');
			w->def[*itr-1].push_back(buffer);
		}


		// for(int i=0;i<POS::Count;++i){
		// 	if(!(ss>>pos[i])|| pos[i]<1||pos[i]>POS::Count){
		// 		std::cout<<"Invalid input. Please try again!\n";
		// 		std::cout<<"Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
		// 		std::getline(std::cin,buffer,'\n');
		// 		ss.clear();
		// 		ss.str(buffer);
		// 		i=-1;
		// 	}
		// }
		// for(int i=0;i<POS::Count;++i){
		// 	if(pos[i]==0) 
		// 		continue;
		// 	std::cout<<"Enter the word's definition as "<<POS::TypeString[pos[i]-1]<<": ";
		// 	std::getline(std::cin,buffer,'\n');
		// 	w->def[pos[i]-1].push_back(buffer);
		// }

		dict->addWord(w);
		std::cout<<"The new word has been added to the dictionary!\n";
	}


	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new EditScreen(dict);
			break;
	}
	return nextScreen;
}
Screen* EditWordScreen::render(){
	clearScr();
	Screen* nextScreen=this;
	std::cout<<"Enter the word you want to edit: ";
	std::string word;
	std::getline(std::cin,word,'\n');

	while(!dict->lowerStrEng(word))
	{
		std::cout<<"Invalid input. Please try again!\n";
		std::cout<<"Enter the word you want to edit: ";
		std::getline(std::cin,word,'\n');
	}
	//check the existence of the word you want to edit in the dictionary
	if(!dict->isInDict(word)){
		std::cout<<"This word is not in the dictionary!\n";
	}
	else{
		nextScreen=new EditSearchWordScreen(dict,word);
	}
	return nextScreen;
}
Screen* EditSearchWordScreen::render(){
	//clearScr();
	Screen* nextScreen=this;

	Word* w=new Word;
	std::cout<<"Enter the new word: ";
	std::getline(std::cin,w->word,'\n');

	while(!dict->lowerStrEng(w->word))
	{
		std::cout<<"Invalid input. Please try again!\n";
		std::cout<<"Enter the new word you want to add: ";
		std::getline(std::cin,w->word,'\n');
	}
	dict->removeWord(word);
	//Check if the new word you want to override the old one is already in the dictionary or not-> if not then continue
	if(dict->isInDict(w->word)){
		std::cout<<"This word is already in the dictionary!\n";
	}
	else{
		std::cout<<"Parts of speech: \n";
		for(int i=0;i<POS::Count;++i){
			std::cout<<i+1<<". "<<POS::TypeString[i]<<std::endl;
		}
		std::string buffer;
		std::cout<<"Enter all parts of speech you want to add/edit definition to(ex: 1 2 ... 9): ";
		std::getline(std::cin,buffer,'\n');
		
		std::unordered_set<int> pos;// to avoid duplicate
		std::stringstream ss(buffer);
		std::string temp;
		int choice;
		while(ss>>temp){
			if(!dict->isValidPOS(temp,choice)){//check the input if it is a valid number (1<=num<=9) or a random string or out of bound
				std::cout<<"Invalid input. Please try again!\n";
				std::cout<<"Enter all parts of speech you want to add definition to(ex: 1 2 ... 9): ";
				std::getline(std::cin,buffer,'\n');
				ss.clear();
				pos.clear();
				ss.str(buffer);
			}
			else{
				pos.insert(choice);
			}
		}
		for(std::unordered_set<int>::iterator itr=pos.begin();itr!=pos.end();++itr){
			std::cout<<"Enter the word's definition as "<<POS::TypeString[*itr-1]<<": ";
			std::getline(std::cin,buffer,'\n');
			w->def[*itr-1].push_back(buffer);
		}

		dict->addWord(w);
		std::cout<<"The word has been successfully edited!\n";
	}


	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new SearchScreen(dict);
			break;
	}
	return nextScreen;
}
Screen* DeleteWordScreen::render(){
	clearScr();
	Screen* nextScreen=this;
	std::cout<<"Enter the word you want to delete: ";
	std::string word;
	std::getline(std::cin,word,'\n');

	while(!dict->lowerStrEng(word))
	{
		std::cout<<"Invalid input. Please try again!\n";
		std::cout<<"Enter the word you want to delete: ";
		std::getline(std::cin,word,'\n');
	}
	//check the existence of the word you want to delete in the dictionary
	if(!dict->isInDict(word)){
		std::cout<<"This word is not in the dictionary!\n";
	}
	else{
		nextScreen=new DeleteSearchWordScreen(dict,word);
	}
	return nextScreen;
}
Screen* DeleteSearchWordScreen::render(){
	//clearScr();
	Screen* nextScreen=this;
	int cnt=0;
	std::cout<<"Are you sure you want to delete this word?\n";
	std::cout<<++cnt<<". Yes\n";
	std::cout<<++cnt<<". No\n";
	int choice=inputOption(cnt);
	switch(choice){
		case 1:
			dict->removeWord(word);
			std::cout<<"The word has been successfully deleted!\n";
			break;
		case 2:
			std::cout <<"The deletion has been cancelled!\n";
			break;
	}
	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new SearchScreen(dict);
			break;
		case 2:
			nextScreen= new EditScreen(dict);
			break;
	}
	return nextScreen;
}
Screen *Remove1WordHistoryScreen::render()
{
	clearScr();
	Screen* nextScreen=this;
	std::cout << "Enter the word you want to remove from your search history: ";
	std::string word;
	std::getline(std::cin, word);

	while(!dict->lowerStrEng(word))
    {
        std::cout<<"Invalid input. Please try again!\n";
        std::cout<<"Enter the word you want to search for: ";
        std::string word;
        std::getline(std::cin,word);
    }
	dict->removeHistory(word);

	std::cout << "The word has been successfully removed from your search history!\n";
	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	int choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new ViewHistoryScreen(dict);
			break;
		case 2:
			nextScreen=new EditScreen(dict);
			break;
	}
	return nextScreen;
}

Screen *DeleteAllHistoryScreen::render()
{
	clearScr();
	Screen* nextScreen=this;
	std::cout << "Are you sure that you want to delete your search history?\n";
	int cnt = 0;
	std::string buffer;
	std::cout << ++cnt << ". Yes\n";
	std::cout << ++cnt << ". No\n";
	int choice = inputOption(cnt);
	switch (choice)
	{
	case 1:
		if (dict->clearAllHistory(MAIN::HISTORY))
			std::cout << "Your search history has been successfully deleted!\n";
		else
			std::cout << "Errors occurred in clearing time!\n";
		break;
	case 2:
		std::cout << "The deletion has been cancelled!\n";
		break;
	}

	std::cout<<"\nOptions: \n";
	for(int i=0;i<options.size();++i)
		std::cout<<std::to_string(i+1)<<". "<<options[i]<<std::endl;
	choice=inputOption(options.size());
	switch(choice){
		case 1:
			nextScreen=new ViewHistoryScreen(dict);
			break;
		case 2:
			nextScreen=new EditScreen(dict);
			break;
	}
	return nextScreen;
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

	std::cout << "Enter the word you want to insert into your favourite list: ";
	std::string word;
	std::getline(std::cin, word);

	dict->uppercase2Lowercase(word);
	dict->addFav(word);

	std::cout << "The word has been successfully inserted into your favourite list!\n";
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

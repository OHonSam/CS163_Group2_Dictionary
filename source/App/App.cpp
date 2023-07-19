#include "App.h"

void EndApp(App *app)
{
	app->state->EndApp = true;
	delete app->CurrentScreen;
	app->CurrentScreen = nullptr;
	delete app->state->tst;
	app->state->tst = nullptr;
	delete app->state;
	app->state = nullptr;

}

void SetNextScreen(App *app, Screen *NextScreen)
{
	delete app->CurrentScreen;
	app->CurrentScreen = NextScreen;
}

void Render(App *app, Screen *s)
{
	s->Render(app);
}

void ClearScreen()
{
#ifdef BUILD_UNIX
	system("clear");
#else
	system("cls");
#endif

	// std::cout << "\033[2J\033[1;1H";

	// std::cout << string( 100, '\n' );
}

bool CheckString(std::string str, int &i)
{
	bool ok = true;
	int length = str.size();
	if (length > 10 || length == 0)
		return false;
	for (int j = 0; j < length; ++j)
	{
		if (str[j] < '0' || str[j] > '9')
			return false;
	}
	if (length == 10)
	{
		if (str > "2147483647")
			return false;
	}
	i = stoi(str);
	return true;
}

void Run()
{
	App *app = new App();
	do
	{
		ClearScreen();
		Render(app, app->CurrentScreen);
	} while (!app->state->EndApp);
	delete app;
}

void FirstScreen::Render(App *app)
{
	int choice = -1, minNumChoice = 1, maxNumChoice = 5, cnt = 0;
	std::string buffer;

	std::cout << "GROUP 2 DICTIONARY\n\n";

	std::cout << "What would you like to do?\n";

	std::cout << ++cnt << ". Interact with your dictionary dataset\n";
	std::cout << ++cnt << ". Interact with your search history\n";
	std::cout << ++cnt << ". Interact with your favourite list\n";
	std::cout << ++cnt << ". Reset the dictionary to its original state\n";
	std::cout << ++cnt << ". Exit\n";

	std::cout << "Your choice: ";

	std::getline(std::cin, buffer, '\n');

	while (!CheckString(buffer, choice) || choice < minNumChoice || choice > maxNumChoice)
	{
		std::cout << "The number you have entered does not correspond to any choice!\n";
		std::cout << "Please re-enter: ";
		std::getline(std::cin, buffer, '\n');
	}

	app->state->userChoice = choice;

	switch (choice)
	{
	case 1:
		// SetNextScreen(app, new LoginScreen());
		break;
	case 2:
		// SetNextScreen(app, new LoginScreen());
		break;
	case 3:
		SetNextScreen(app, new FavListChoiceScreen());
		break;
	case 4:
		// SetNextScreen(app, new FavListChoiceScreen());
		break;
	case 5:
		EndApp(app);
		break;
	}
}

void FavListChoiceScreen::Render(App *app)
{
	int choice = -1, minNumChoice = 1, maxNumChoice = 4, cnt = 0;
	std::string buffer;

	app->state->tst = new TST();

	if (app->state->tst->import(FAV_LIST_SAVE_FILE))
	{
		std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
		std::cout << "What would you like to do?\n";
		std::cout << ++cnt << ". Type in a word to insert it to your favorite list\n";
		std::cout << ++cnt << ". Type in a word to remove it from your favorite list\n";
		std::cout << ++cnt << ". Search prefix of words in your favorite list\n";
		std::cout << ++cnt << ". Go back to previous page\n";

		std::getline(std::cin, buffer, '\n');

		while (!CheckString(buffer, choice) || choice < minNumChoice || choice > maxNumChoice)
		{
			std::cout << "The number you have entered does not correspond to any choice!\n";
			std::cout << "Please re-enter: ";
			std::getline(std::cin, buffer, '\n');
		}

		app->state->userChoice = choice;
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

		std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
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

		app->state->userChoice = choice;
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
	std::cout << "Your choice was: " << app->state->userChoice << "\n";

	if (app->state->tst->treeExists())
	{
		app->state->tst->type2RemoveWord();
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
	std::cout << "Your choice was: " << app->state->userChoice << "\n";
	app->state->tst->type2InsertWord();
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
	std::cout << "Your choice was: " << app->state->userChoice << "\n";
	app->state->tst->searchPrefix();
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
	std::cout << "Your choice was: " << app->state->userChoice << "\n";
	app->state->tst->insert(app->state->word);
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
	std::cout << "Your choice was: " << app->state->userChoice << "\n";
	app->state->tst->remove(app->state->word);
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

// void CreateClassScreen::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.CreateClass(app->state->Schoolyear);
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
// 	SetNextScreen(app, new ClassChoice());
// }

// void LoginScreen::Render(App *app)
// {
// 	ClearScreen();
// 	User *u;
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "Are you a staff or a student?\n";
// 	std::cout << "1. Staff\n";
// 	std::cout << "2. Student\n";
// 	std::cout << "Your choice: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 1 || choice > 2)
// 	{
// 		std::cout << "Your input does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	u = new User();

// 	switch (choice)
// 	{
// 	case 1:
// 		u->Staff = true;
// 		SetNextScreen(app, new StaffChoiceScreen());
// 		break;
// 	case 2:
// 		u->Staff = false;
// 		SetNextScreen(app, new StudentChoiceScreen());
// 		break;
// 	}
// 	app->state->userChoice = choice;

// 	ClearScreen();
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	u->InputUsername();
// 	u->InputPassword();
// 	while (!u->CheckUser())
// 	{
// 		ClearScreen();
// 		std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 		std::cout << "Wrong username or password! Please re-enter\n";

// 		u->InputUsername();
// 		u->InputPassword();
// 	}
// 	app->state->user = u;
// 	std::cout << "Logged in successfully!\n";

// 	int i = -1;
// 	std::cout << "Enter 0 to continue\n";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, i) || i != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// }

// void StaffChoiceScreen::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;
// 	app->state->Schoolyear = "";
// 	app->state->Semester = -1;

// 	std::cout << "Hello, " << app->state->user->Username << " "
// 			  << "\n0. Logout\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Create a school year\n";
// 	std::cout << "2. Choose an existing schoolyear\n";
// 	// std::cout << "2. Semester\n";
// 	// std::cout << "3. Course\n";
// 	// std::cout << "4. Class\n";
// 	std::cout << "3. Change password\n";

// 	std::cout << "Your choice: ";

// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 3)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new CreateSchoolYearScreen());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ChooseSY());
// 		break;
// 	// case 3:
// 	// 	SetNextScreen(app, new CourseChoice());
// 	// 	break;
// 	// case 4:
// 	// 	SetNextScreen(app, new ClassChoice());
// 	// 	break;
// 	case 3:
// 		SetNextScreen(app, new ChangePass());
// 		break;
// 	}
// } // needs fixing

// void SemesterChoice::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Create a semester\n";
// 	std::cout << "2. Choose an existing semester to work on\n";
// 	std::cout << "3. Go back to previous page\n";

// 	std::cout << "Your choice: ";

// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 3)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new CreateSemesterScreen());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ChooseSem());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new StaffChoiceScreen());
// 		break;
// 	}
// }

// void ChooseSem::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	std::cout << "The current schoolyear is: " << app->state->Schoolyear << "\n\n";

// 	Semester s;
// 	s.ChooseSemester(app->state->Schoolyear);

// 	if (s.userChoice == -1)
// 	{
// 		std::cout << "\nEnter 0 to return to previous page\n";
// 		SetNextScreen(app, new SemesterChoice());
// 	}
// 	else
// 	{
// 		std::cout << "\nEnter 0 to move to next page\n";
// 		app->state->Semester = s.userChoice;
// 		SetNextScreen(app, new CourseChoice());
// 	}

// 	int choice = -1;
// 	std::string buffer;
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// }

// void CreateSemesterScreen::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Semester s;
// 	s.CreateSemester(app->state->Schoolyear);
// 	if (s.userChoice == -1)
// 	{
// 		std::cout << "\nEnter 0 to return to previous\n";
// 		SetNextScreen(app, new SemesterChoice());
// 	}
// 	else
// 	{
// 		app->state->Semester = s.userChoice;
// 		std::cout << "\nEnter 0 to move to next page\n";
// 		SetNextScreen(app, new CourseChoice());
// 	}

// 	int choice = -1;
// 	std::string buffer;
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// }

// void CreateSYScr::Render(App *app)
// {
// 	std::cout << app->state->user->Username << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
// 	SchoolYear sy;
// 	sy.createSchoolYear();

// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "Enter 0 to return\n";

// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// 	SetNextScreen(app, new SYChoice());
// }

// void StudentChoiceScreen::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "Hello, " << app->state->user->Username << " "
// 			  << "0. Logout\n\n";

// 	std::cout << "This is student choice screen\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. View all your courses\n";
// 	std::cout << "2. View your scores\n";
// 	std::cout << "3. Profile (change password)\n";

// 	std::cout << "Your choice: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 3)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new ViewCoursesStudent());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ViewScoreStudent());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ChangePass());
// 		break;
// 	}
// }

// void ClassChoice::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "The current schoolyear is: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Create a class\n";
// 	std::cout << "2. View all classes\n";
// 	std::cout << "3. Modify a class\n";
// 	std::cout << "4. Import students into an existing class\n";
// 	std::cout << "5. View all students in a class\n";
// 	std::cout << "6. Remove a student by his/her student ID\n";
// 	std::cout << "7. Search a student by ID then update his/her information\n";
// 	std::cout << "8. Go back to previous page\n";

// 	std::cout << "Your choice: ";

// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 8)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;

// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new CreateClassScreen());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ViewAllClass());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ModifyClassScreen());
// 		break;
// 	case 4:
// 		SetNextScreen(app, new ImportToClass());
// 		break;
// 	case 5:
// 		SetNextScreen(app, new ViewStudentClass());
// 		break;
// 	case 6:
// 		SetNextScreen(app, new RemoveAStudent());
// 		break;
// 	case 7:
// 		SetNextScreen(app, new UpdateStudentInfo());
// 		break;
// 	case 8:
// 		SetNextScreen(app, new SYChoice());
// 		break;
// 	}
// }

// void ImportToClass::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.ImportCSVfile(app->state->Schoolyear);
// 	if (!cl.HeadStudent)
// 	{
// 		std::cout << "Nothing to import!\n";
// 	}
// 	else
// 	{
// 		cl.CreateClassTXTfile();
// 		cl.DeleteCSVdata();
// 	}

// 	SetNextScreen(app, new ClassChoice());
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << "Enter 0 to return\n";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice != 0)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}
// }

// void CourseChoice::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "Your current semester is: " << app->state->Semester << " of year: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Create course\n";
// 	std::cout << "2. View all courses in this semester\n";
// 	std::cout << "3. Modify a course\n";
// 	std::cout << "4. Import students into an existing course\n";
// 	std::cout << "5. View all students in a course\n";
// 	std::cout << "6. Work on the scores\n";
// 	std::cout << "7. Export a course to .csv file\n";
// 	std::cout << "8. Go back to previous page\n";

// 	std::cout << "Your choice: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 8)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new CreateCourseScreen());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ViewCoursesStaff());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ModifyCourseScreen());
// 		break;
// 	case 4:
// 		SetNextScreen(app, new ImportToCourse());
// 		break;
// 	case 5:
// 		SetNextScreen(app, new ViewStudentCourse());
// 		break;
// 	case 6:
// 		SetNextScreen(app, new ScoreChoice());
// 		break;
// 	case 7:
// 		SetNextScreen(app, new ExportCourse());
// 		break;
// 	case 8:
// 		SetNextScreen(app, new SemesterChoice());
// 		break;
// 	}
// }

// void CreateCourseScreen::Render(App *app)
// {
// 	std::cout << "Your current semester is: " << app->state->Semester << " of year: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
// 	Course c(app->state->Schoolyear, app->state->Semester);
// 	c.CreateCourse();

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

// 	SetNextScreen(app, new CourseChoice());
// }

// void ModifyClassScreen::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "The current schoolyear is: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Delete a class\n";
// 	std::cout << "2. Manage students in class\n";
// 	std::cout << "3. Go back to previous page\n";

// 	std::cout << "Your choice is: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 3)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new DelAClass());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ManageStudentsInClass());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ClassChoice());
// 		break;
// 	}
// }

// void ManageStudentsInClass::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "The current schoolyear is: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Add a student manually to a class\n";
// 	std::cout << "2. Search for a student\n";
// 	std::cout << "3. Go back to previous page\n";

// 	std::cout << "Your choice is: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 3)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new AddStudentToClass());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new SearchStudentInClass());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ModifyClassScreen());
// 	}
// }

// void SearchStudentInClass::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.searchStudentID(app->state->Schoolyear);
// 	cl.DeleteCSVdata();
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

// 	SetNextScreen(app, new ManageStudentsInClass());
// }

// void AddStudentToClass::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.addFromConsole(app->state->Schoolyear);

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

// 	SetNextScreen(app, new ManageStudentsInClass());
// }

// void ViewAllClass::Render(App *app)
// {
// 	ClassLL classLL;
// 	classLL.viewClass(app->state->Schoolyear);

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

// 	SetNextScreen(app, new ClassChoice());
// }

// void DelAClass::Render(App *app)
// {
// 	Class cl;
// 	cl.DeleteAClass(app->state->Schoolyear);

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

// 	SetNextScreen(app, new ModifyClassScreen());
// }

// void ViewStudentClass::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.viewStudentAClass(app->state->Schoolyear);

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

// 	SetNextScreen(app, new ClassChoice());
// }

// void ImportToCourse::Render(App *app)
// {
// 	bool imported = true;
// 	std::cout << "Your current semester is: " << app->state->Semester << " of year: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	Course c(app->state->Schoolyear, app->state->Semester);
// 	c.ImportCSVFile();
// 	c.ExportTXTFile();
// 	if (!c.HeadStudent)
// 	{
// 		std::cout << "Nothing to import!\n";
// 		imported = false;
// 	}
// 	c.DeleteCSVdata();

// 	if (imported)
// 		std::cout << "Imported successfully!\n";

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

// 	SetNextScreen(app, new CourseChoice());
// }

// void ViewCoursesStaff::Render(App *app)
// {
// 	std::cout << "Your current semester is: " << app->state->Semester << " of year: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
// 	Course c(app->state->Schoolyear, app->state->Semester);
// 	c.ViewCourseStaff();

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

// 	SetNextScreen(app, new CourseChoice());
// }

// void ViewStudentCourse::Render(App *app)
// {
// 	std::cout << "Your current semester is: " << app->state->Semester << " of year: " << app->state->Schoolyear << "\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";
// 	Course c(app->state->Schoolyear, app->state->Semester);
// 	c.ViewStudentACourse();

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

// 	SetNextScreen(app, new CourseChoice());
// }

// void ModifyCourseScreen::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Delete a course\n";
// 	std::cout << "2. Update a course information\n";
// 	std::cout << "3. Manage students in course\n";
// 	std::cout << "4. Go back to previous page\n";

// 	std::cout << "Your choice is: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 4)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new DelACourse());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new UpdateCourse());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ManageStudentsInCourse());
// 		break;
// 	case 4:
// 		SetNextScreen(app, new CourseChoice());
// 		break;
// 	}
// }

// void DelACourse::Render(App *app)
// {
// 	Course c;
// 	c.DeleteACourse();

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

// 	SetNextScreen(app, new ModifyCourseScreen());
// }

// void UpdateCourse::Render(App *app)
// {
// 	Course c;
// 	c.UpdateACourse();

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

// 	SetNextScreen(app, new ModifyCourseScreen());
// }

// void ChangePass::Render(App *app)
// {
// 	app->state->user->ChangePassword();

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
// 	if (app->state->user->Staff)
// 		SetNextScreen(app, new StaffChoiceScreen());
// 	else
// 		SetNextScreen(app, new StudentChoiceScreen());
// }

// void ManageStudentsInCourse::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Add a student manually to a course\n";
// 	std::cout << "2. Delete a student from a course\n";
// 	std::cout << "3. Go back to previous page\n";

// 	std::cout << "Your choice is: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 3)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new AddStudentToCourse());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new RemoveStudentCourse());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ModifyCourseScreen());
// 	}
// }

// void RemoveStudentCourse::Render(App *app)
// {
// 	Course c;
// 	c.RemoveAStudent();

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

// 	SetNextScreen(app, new ManageStudentsInCourse());
// }

// void AddStudentToCourse::Render(App *app)
// {
// 	Course c;
// 	c.AddStudentFromConsole();

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

// 	SetNextScreen(app, new ManageStudentsInCourse());
// }

// void ViewCoursesStudent::Render(App *app)
// {
// 	Course c;
// 	c.ViewCourseStudent(app->state->user->Username);

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

// 	SetNextScreen(app, new StudentChoiceScreen());
// }

// void ScoreChoice::Render(App *app)
// {
// 	int choice = -1;
// 	std::string buffer;

// 	std::cout << app->state->user->Username << " "
// 			  << "0. Logout\n";
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n\n";

// 	std::cout << "What would you like to do?\n";
// 	std::cout << "1. Import a score CSV file for a course\n";
// 	std::cout << "2. View scoreboard of a course\n";
// 	std::cout << "3. Update a student's result\n";
// 	std::cout << "4. View score board of a class\n";
// 	std::cout << "5. Go back to previous page\n";

// 	std::cout << "Your choice is: ";
// 	std::getline(std::cin, buffer, '\n');

// 	while (!CheckString(buffer, choice) || choice < 0 || choice > 5)
// 	{
// 		std::cout << "The number you have entered does not correspond to any choice!\n";
// 		std::cout << "Please re-enter: ";
// 		std::getline(std::cin, buffer, '\n');
// 	}

// 	app->state->userChoice = choice;
// 	switch (choice)
// 	{
// 	case 0:
// 		SetNextScreen(app, new FirstScreen());
// 		break;
// 	case 1:
// 		SetNextScreen(app, new ImportScore());
// 		break;
// 	case 2:
// 		SetNextScreen(app, new ViewScoreCourseStaff());
// 		break;
// 	case 3:
// 		SetNextScreen(app, new ChangeAScore());
// 		break;
// 	case 4:
// 		EndApp(app);
// 		break;
// 	case 5:
// 		SetNextScreen(app, new CourseChoice());
// 		break;
// 	}
// }

// void ImportScore::Render(App *app)
// {
// 	ScoreLL sll;
// 	sll.ImportCSVFile(app->state->Schoolyear, app->state->Semester);

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

// 	SetNextScreen(app, new ScoreChoice());
// }

// void RemoveAStudent::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.removeAStudent();
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
// 	SetNextScreen(app, new ClassChoice());
// }

// void UpdateStudentInfo::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	Class cl;
// 	cl.updateStudentInfo();
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
// 	SetNextScreen(app, new ClassChoice());
// }

// void ExportCourse::Render(App *app)
// {
// 	Course c(app->state->Schoolyear, app->state->Semester);
// 	c.ExportCSVFile();

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

// 	SetNextScreen(app, new CourseChoice());
// }

// void ViewScoreCourseStaff::Render(App *app)
// {
// 	ScoreLL sll;
// 	sll.ViewCourseScoreStaff(app->state->Schoolyear, app->state->Semester);

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

// 	SetNextScreen(app, new ScoreChoice());
// }

// void ChangeAScore::Render(App *app)
// {
// 	ScoreLL sll;
// 	sll.UpdateResult(app->state->Schoolyear, app->state->Semester);

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

// 	SetNextScreen(app, new ScoreChoice());
// }

// void ViewScoreStudent::Render(App *app)
// {
// 	ScoreLL sll;
// 	sll.ViewScoreCourseStudent(app->state->user->Username);

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

// 	SetNextScreen(app, new StudentChoiceScreen());
// }

// void CreateSchoolYearScreen::Render(App *app)
// {
// 	std::cout << "Your choice was: " << app->state->userChoice << "\n";
// 	SchoolYear sy;
// 	sy.createSchoolYear();
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
// 	SetNextScreen(app, new SYChoice());
// }
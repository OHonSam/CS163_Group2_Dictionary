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

	TST* tst;

	State() : word{}, userChoice{-1}, EndApp{false}, tst(nullptr) {};
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

//--------------------------------Parent: FirstScreen-------end-------------------------------

//--------------------------------Parent: FavListChoiceScreen--------------------------------------

class Type2RemoveWordFavListScreen : public Screen
{
	void Render(App *app) override;
};

class Type2InsertWordFavListScreen : public Screen
{
	void Render(App *app) override;
};

class SearchPrefixFavList : public Screen
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

// class CreateSYScr : public Screen
// {
// 	void Render(App* app);
// };

// class SemesterChoice : public Screen
// {
// 	void Render(App* app);
// };

// class ChooseSem : public Screen
// {
// 	void Render(App* app);
// };

// class CreateSemesterScreen : public Screen
// {
// 	void Render(App* app);
// };

// class ClassChoice : public Screen
// {
// 	void Render(App* app);
// };

// class CreateClassScreen : public Screen
// {
// 	void Render(App* app);
// };

// class ImportToClass : public Screen
// {
// 	void Render(App* app);
// };

// class CourseChoice : public Screen
// {
// 	void Render(App* app);
// };

// class CreateCourseScreen : public Screen
// {
// 	void Render(App* app);
// };

// class ModifyClassScreen : public Screen
// {
// 	void Render(App* app);
// };

// class ManageStudentsInClass : public Screen
// {
// 	void Render(App* app);
// };

// class SearchStudentInClass : public Screen
// {
// 	void Render(App* app);
// };

// class AddStudentToClass : public Screen
// {
// 	void Render(App* app);
// };

// class ViewAllClass : public Screen
// {
// 	void Render(App* app);
// };

// class DelAClass : public Screen
// {
// 	void Render(App* app);
// };

// class ViewStudentClass : public Screen
// {
// 	void Render(App* app);
// };

// class ImportToCourse : public Screen
// {
// 	void Render(App* app);
// };

// class ViewCoursesStaff : public Screen
// {
// 	void Render(App* app);
// };

// class ViewStudentCourse : public Screen
// {
// 	void Render(App* app);
// };

// class ModifyCourseScreen : public Screen
// {
// 	void Render(App* app);
// };

// class DelACourse : public Screen
// {
// 	void Render(App* app);
// };

// class UpdateCourse : public Screen
// {
// 	void Render(App* app);
// };

// class ChangePass : public Screen
// {
// 	void Render(App* app);
// };

// class ManageStudentsInCourse : public Screen
// {
// 	void Render(App* app);
// };

// class RemoveStudentCourse : public Screen
// {
// 	void Render(App* app);
// };

// class AddStudentToCourse : public Screen
// {
// 	void Render(App* app);
// };

// class ViewCoursesStudent : public Screen
// {
// 	void Render(App* app);
// };

// class ScoreChoice : public Screen
// {
// 	void Render(App* app);
// };

// class ImportScore : public Screen
// {
// 	void Render(App* app);
// };

// class RemoveAStudent : public Screen
// {
// 	void Render(App* app);
// };

// class UpdateStudentInfo : public Screen
// {
// 	void Render(App* app);
// };

// class ExportCourse : public Screen
// {
// 	void Render(App* app);
// };

// class ViewScoreCourseStaff : public Screen
// {
// 	void Render(App* app);
// };

// class ChangeAScore : public Screen
// {
// 	void Render(App* app);
// };

// class ViewScoreStudent : public Screen
// {
// 	void Render(App* app);
// };

class App
{
public:
	State* state;
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
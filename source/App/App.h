#ifndef APP_H
#define APP_H

#include "source\Libraries.hpp"
#include "source\DataStructure\Word\Word.hpp"
#include "source\DataStructure\TST\TST.hpp"

class App;

class App
{
public:
	State state;
	Screen* CurrentScreen;

	App()
	{
		CurrentScreen = new FirstScreen();
	}
};

void SetNextScreen(App* app, Screen* NextScreen); 
void Render(App* app, Screen* s);

void Run();
void EndApp(State* state);

void ClearScreen();
bool CheckString(std::string str, int& i);

class State
{
public:
	int userChoice;
	bool EndApp;
	std::string word;

	State() : word{}, userChoice{-1}, EndApp{false} {};
};

class Screen
{
public:
	virtual void Render(App* app) = 0;
};

class FirstScreen : public Screen
{
	void Render(App* app);
};

class FavListChoiceScreen : public Screen
{
	void Render(App* app) override;
};

class Type2RemoveWordFavListScreen : public Screen
{
	void Render(App* app);
};

class Type2InsertWordFavListScreen : public Screen
{
	void Render(App* app);
};

class searchPrefixFavList : public Screen
{
	void Render(App* app);
};

class RemoveWordFavListScreen : public Screen
{
	void Render(App* app);
};

class InsertWordFavListScreen : public Screen
{
	void Render(App* app);
};

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

// #endif
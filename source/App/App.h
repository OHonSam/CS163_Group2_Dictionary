#ifndef APP_H
#define APP_H

#include "source\DataStructure\TST\TST.hpp"

#include "GlobalFunc.h"
#include "Class.h"
#include "SchoolYear.h"
#include "Course.h"
#include "Semester.h"
#include "Score.h"

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

bool CheckString(std::string str, int& i);
class State
{
public:
	int userChoice;
	bool EndApp;

	State() : user{nullptr}, userChoice{-1}, EndApp{false} {};
};

class Screen
{
public:
	virtual void Render(App* app);
};


class FirstScreen : public Screen
{
	void Render(App* app);
};

class favListChoiceScreen : public Screen
{
	void Render(App* app) override;
};

class removeWordFavListScreen : public Screen
{
	void Render(App* app);
};

// class StaffChoiceScreen : public Screen
// {
// 	void Render(App* app);
// };

// class CreateSchoolYearScreen : public Screen
// {
// 	void Render(App* app);
// };

// class SYChoice : public Screen
// {
// 	void Render(App* app);
// };

// class ChooseSY : public Screen
// {
// 	void Render(App* app);
// };

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
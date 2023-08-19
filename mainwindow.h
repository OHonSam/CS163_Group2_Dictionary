#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "homescreen.h"
#include "historyscreen.h"
#include "searchscreen.h"
#include "favlistscreen.h"
#include "editscreen.h"
#include "addnewword.h"
#include "quiz.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
        Dict* dict,
        QWidget *parent = nullptr
    );
    ~MainWindow();

signals:
    void giveWord(const std::string& input);

public slots:
    void switchScreen(Screen::Type id);

private:
    const int DEF_WIDTH=1072;
    const int DEF_HEIGHT=729;

    Ui::MainWindow *ui;
    Dict* dict;

    HomeScreen homeScreen;
    HistoryScreen historyScreen;
    SearchScreen searchScreen;
    FavListScreen favListScreen;
    EditScreen editScreen;
    AddNewWord addScreen;
    Quiz quizScreen;

    Screen::Type preScreen, curScreen;
};
#endif // MAINWINDOW_H

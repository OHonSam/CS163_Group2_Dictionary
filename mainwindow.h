#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <homescreen.h>
#include <historyscreen.h>
#include<searchfordef.h>
#include<searchforkey.h>
#include <Dict.hpp>
#include<editchoice.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Screens{
enum Type{
    Dummy,
    Home,
    History,
    SearchForDef,
    Count
};
}

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
    void switchToHistoryScreen();
    void switchToHomeScreen();
    void switchToSearchForDefScreen(const std::string& word);

private:
    const int DEF_WIDTH=1072;
    const int DEF_HEIGHT=729;

    Ui::MainWindow *ui;
    Dict* dict;

    HomeScreen homeScreen;
    HistoryScreen historyScreen;
    SearchForDef searchForDefScreen;
};
#endif // MAINWINDOW_H

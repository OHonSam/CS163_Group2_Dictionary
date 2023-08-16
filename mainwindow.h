#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <homescreen.h>
#include <historyscreen.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Screens{
enum Type{
    Dummy,
    Home,
    History,
    Fav,
    Search,
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

public slots:
    void switchToHistoryScreen();

private:
    const int DEF_WIDTH=1072;
    const int DEF_HEIGHT=729;

    Ui::MainWindow *ui;
    Dict* dict;

    HomeScreen homeScreen;
    HistoryScreen historyScreen;
};
#endif // MAINWINDOW_H

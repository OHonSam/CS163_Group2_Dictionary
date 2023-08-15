#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <historyscreen.h>
#include<searchfordef.h>
#include<searchforkey.h>
#include <Dict.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Dict dict;
};
#endif // MAINWINDOW_H

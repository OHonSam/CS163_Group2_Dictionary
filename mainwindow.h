#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <historyscreen.h>
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

private slots:
    void on_comboBox_dictVersion_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Dict dict;
};
#endif // MAINWINDOW_H
